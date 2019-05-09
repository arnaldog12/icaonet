using System;
using System.Collections.Generic;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Windows.Forms;

namespace MrkReview
{
    public partial class MRKEditor : Form
    {
        string folderPathImgs = "";
        string folderPathMRKs = "";
        List<GTPair> listAll = new List<GTPair>();
        List<GTPair> listFilteredReqs;
        REQUIREMENT_VALUE[] reqValues = { REQUIREMENT_VALUE.NON_COMPLIANT, REQUIREMENT_VALUE.COMPLIANT, REQUIREMENT_VALUE.DUMMY };
        REQUIREMENT_VALUE[] nextReqValue = { REQUIREMENT_VALUE.COMPLIANT, REQUIREMENT_VALUE.DUMMY, REQUIREMENT_VALUE.NON_COMPLIANT };

        Dictionary<REQUIREMENT_VALUE, Color> reqValueToColor = new Dictionary<REQUIREMENT_VALUE, Color>
        {
            [REQUIREMENT_VALUE.NON_COMPLIANT] = Color.Red,
            [REQUIREMENT_VALUE.DUMMY] = Color.Gray,
            [REQUIREMENT_VALUE.COMPLIANT] = Color.Green
        };

        public MRKEditor()
        {
            InitializeComponent();
            this.InitListView();
        }

        private void LoadMRKFiles(string[] imageFiles)
        {
            this.listAll.Clear();
            foreach (string file in imageFiles)
            {
                string mrkPath = file.Replace("images", "ground_truth");
                mrkPath = mrkPath.Replace(Path.GetExtension(mrkPath), ".mrk");
                this.listAll.Add(new GTPair(file, new MRKFile(mrkPath)));
            }
        }

        private void InitListView()
        {
            foreach (Requirement req in (new PhotographicRequirements()))
                this.listViewReqs.Items.Add(new ListViewItem(req.Description));
        }

        private List<GTPair> FilterGTPairsByRequirementAndValue()
        {
            int selectedValueIndex = this.comboBoxValues.SelectedIndex;
            int selectedReqIndex = this.comboBoxReq.SelectedIndex;
            if (selectedValueIndex < 0 || selectedReqIndex < 0) return this.listAll;

            REQUIREMENT_VALUE reqValue = reqValues[selectedValueIndex];

            return this.listAll.Where(req =>
                req.FileMrk.PhotoReqs.GetRequirements()[selectedReqIndex].Value == reqValue).ToList<GTPair>();
        }

        private void UpdateListViewRequirements(MRKFile mrkFile)
        {
            int i = 0;
            foreach (Requirement req in mrkFile.PhotoReqs)
                this.listViewReqs.Items[i++].BackColor = reqValueToColor[req.Value];
        }

        private void UpdateListBoxImages(List<GTPair> filteredList)
        {
            this.listBoxImgs.Items.Clear();
            filteredList.ForEach(delegate (GTPair pair) { this.listBoxImgs.Items.Add(Path.GetFileName(pair.FileImage)); });
            this.labelCountImages.Text = String.Format("{0} images", filteredList.Count);
        }

        private void SaveFileAndGoToNextImage(REQUIREMENT_VALUE newValue)
        {
            int selectedImage = this.listBoxImgs.SelectedIndex;
            int selectedRequirement = this.comboBoxReq.SelectedIndex;
            if (selectedImage < 0 || selectedRequirement < 0) return;

            MRKFile mrkFile = this.listFilteredReqs[selectedImage].FileMrk;
            mrkFile.PhotoReqs.GetRequirements()[selectedRequirement].Value = newValue;
            mrkFile.Save();

            selectedImage = Math.Max(0, selectedImage + 1);
            this.listBoxImgs.SelectedIndex = Math.Min(selectedImage, this.listFilteredReqs.Count - 1);
        }

        // ------------------------ EVENTS METHODS ------------------------

        private void buttonOpenDir_Click(object sender, EventArgs e)
        {
            fileDialog.Filter = "Image Files (*.png, *.jpg, *.jpeg)|*.png;*.jpg;*.jpeg";
            fileDialog.Multiselect = true;

            if (fileDialog.ShowDialog() != DialogResult.OK) return;

            this.folderPathImgs = Directory.GetParent(fileDialog.FileName).FullName;
            this.folderPathMRKs = this.folderPathImgs.Replace("images", "ground_truth");

            if (!Directory.Exists(this.folderPathMRKs))
            {
                DirectoryInfo parentDir = Directory.GetParent(this.folderPathImgs);
                MessageBox.Show("This program expects a 'ground_truth' folder at the same path of 'images' folder." +
                    "Please, paste the 'ground truth' folder at: " + parentDir.Name);
                return;
            }

            LoadMRKFiles(fileDialog.FileNames);

            this.checkBoxAll.Checked = true;
            this.checkBoxAll.Enabled = true;
            this.listBoxImgs.Enabled = true;

            this.listFilteredReqs = this.listAll;
            this.UpdateListBoxImages(this.listFilteredReqs);
        }

        private void listBoxImgs_SelectedIndexChanged(object sender, EventArgs e)
        {
            int selectedIndex = this.listBoxImgs.SelectedIndex;
            if (selectedIndex < 0) return;

            string imagePath = this.listFilteredReqs[selectedIndex].FileImage;
            this.picBox.Image = new Bitmap(imagePath);
            this.UpdateListViewRequirements(this.listFilteredReqs[selectedIndex].FileMrk);
        }

        private void comboBoxValues_SelectedIndexChanged(object sender, EventArgs e)
        {
            int selectedValue = this.comboBoxValues.SelectedIndex;
            int selectedReq = this.comboBoxReq.SelectedIndex;
            if (selectedValue < 0 || selectedReq < 0) return;

            this.listFilteredReqs = this.FilterGTPairsByRequirementAndValue();
            this.UpdateListBoxImages(this.listFilteredReqs);
        }

        private void listViewReqs_MouseClick(object sender, MouseEventArgs e)
        {
            int selectedImage = this.listBoxImgs.SelectedIndex;
            int selectedRequirement = this.listViewReqs.SelectedIndices[0];
            if (selectedImage < 0 || selectedRequirement < 0) return;

            MRKFile mrkFile = this.listFilteredReqs[selectedImage].FileMrk;
            Requirement selectedReq = mrkFile.PhotoReqs.GetRequirements()[selectedRequirement];
            selectedReq.Value = nextReqValue[(int) selectedReq.Value + 1];

            mrkFile.Save();
            this.UpdateListViewRequirements(this.listFilteredReqs[selectedImage].FileMrk);

            this.buttonOpenDir.Focus();
        }

        private void checkBoxAll_CheckedChanged(object sender, EventArgs e)
        {
            bool isChecked = this.checkBoxAll.Checked;
            this.listFilteredReqs = isChecked ? this.listAll : this.FilterGTPairsByRequirementAndValue();

            this.comboBoxReq.Enabled = !isChecked;
            this.comboBoxValues.Enabled = !isChecked;
            this.buttonReject.Enabled = !isChecked;
            this.buttonDummy.Enabled = !isChecked;
            this.buttonAcc.Enabled = !isChecked;
            this.UpdateListBoxImages(this.listFilteredReqs);
        }

        private void buttonReject_Click(object sender, EventArgs e)
        {
            this.SaveFileAndGoToNextImage(REQUIREMENT_VALUE.NON_COMPLIANT);
        }

        private void buttonDummy_Click(object sender, EventArgs e)
        {
            this.SaveFileAndGoToNextImage(REQUIREMENT_VALUE.DUMMY);
        }

        private void buttonAcc_Click(object sender, EventArgs e)
        {
            this.SaveFileAndGoToNextImage(REQUIREMENT_VALUE.COMPLIANT);
        }
    }
}
