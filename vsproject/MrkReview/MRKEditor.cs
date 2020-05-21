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
        Panel[] listPanelsOfFilters;
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
            this.InitListOfPanels();
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

        private void InitListOfPanels()
        {
            this.listPanelsOfFilters = new Panel[23] { this.panelBlurred, this.panelLookingAway, this.panelInkMarkedCreased, this.panelUnnaturalSkinTone, this.panelTooDarkLight, this.panelWashedOut, this.panelPixelation, this.panelHairAcrossEyes, this.panelEyesClosed, this.panelVariedBackground, this.panelRollPitchYaw, this.panelFlashReflectionOnSkin, this.panelRedEyes, this.panelShadowsBehindHead, this.panelShadowsAcrossFace, this.panelDarkTintedLenses, this.panelFlashReflectionOnLenses, this.panelFramesTooHeavy, this.panelFrameCoveringEyes, this.panelHatcap, this.panelVeilOverFace, this.panelMouthOpen, this.panelPresenceOfOtherFaces };
        }

        private void FilterGTPairsByRequirementsAndValues()
        {
            this.listFilteredReqs = this.listAll;
            PhotographicRequirements reqs = new PhotographicRequirements();

            for (int panelIndex = 0; panelIndex < this.listPanelsOfFilters.Count(); panelIndex++)
            {
                Panel panel = (Panel)this.listPanelsOfFilters[panelIndex];

                for (int radioButtonIndex = 0; radioButtonIndex < 4; radioButtonIndex++)
                {
                    RadioButton rb = (RadioButton) panel.Controls[radioButtonIndex];
                    if (!rb.Checked) continue;
                    if (radioButtonIndex == 0) break;

                    REQUIREMENT_VALUE reqValue = reqValues[radioButtonIndex - 1];
                    this.listFilteredReqs = this.listFilteredReqs.Where(req => req.FileMrk.PhotoReqs.GetRequirements()[panelIndex].Value == reqValue).ToList<GTPair>();
                }

                if (this.listFilteredReqs.Count == 0) break;
            }
            this.UpdateListBoxImages(this.listFilteredReqs);
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
            if (selectedImage < 0) return;

            MRKFile mrkFile = this.listFilteredReqs[selectedImage].FileMrk;
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

            this.listBoxImgs.Enabled = true;
            this.buttonAcc.Enabled = true;
            this.buttonReject.Enabled = true;
            this.buttonDummy.Enabled = true;

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
            this.listViewReqs.SelectedItems.Clear();
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

        private void buttonResetFilters_Click(object sender, EventArgs e)
        {
            foreach (Panel panel in this.listPanelsOfFilters)
            {
                RadioButton rb = (RadioButton)panel.Controls[0];
                rb.Checked = true;
            }
            this.FilterGTPairsByRequirementsAndValues();
        }

        private void buttonFilterReqs_Click(object sender, EventArgs e)
        {
            this.FilterGTPairsByRequirementsAndValues();
        }

        private void listBoxImgs_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Control && (e.KeyCode == Keys.C))
                Clipboard.SetText(this.listBoxImgs.SelectedItem.ToString() + "\n");

            if (e.Control && (e.KeyCode == Keys.A))
            {
                string allImages = "";
                foreach (string item in this.listBoxImgs.Items)
                    allImages += (item + "\n");
                Clipboard.SetText(allImages);
            }
        }
    }
}
