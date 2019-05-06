namespace MrkReview
{
    partial class MRKEditor
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MRKEditor));
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.checkBoxAll = new System.Windows.Forms.CheckBox();
            this.comboBoxValues = new System.Windows.Forms.ComboBox();
            this.comboBoxReq = new System.Windows.Forms.ComboBox();
            this.buttonDummy = new System.Windows.Forms.Button();
            this.buttonAcc = new System.Windows.Forms.Button();
            this.buttonReject = new System.Windows.Forms.Button();
            this.listBoxImgs = new System.Windows.Forms.ListBox();
            this.buttonOpenDir = new System.Windows.Forms.Button();
            this.panel1 = new System.Windows.Forms.Panel();
            this.panel2 = new System.Windows.Forms.Panel();
            this.picBox = new System.Windows.Forms.PictureBox();
            this.listViewReqs = new System.Windows.Forms.ListView();
            this.ColReqs = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.panelMain = new System.Windows.Forms.Panel();
            this.panel3 = new System.Windows.Forms.Panel();
            this.fileDialog = new System.Windows.Forms.OpenFileDialog();
            this.groupBox2.SuspendLayout();
            this.panel1.SuspendLayout();
            this.panel2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picBox)).BeginInit();
            this.panelMain.SuspendLayout();
            this.panel3.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox2
            // 
            this.groupBox2.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox2.Controls.Add(this.checkBoxAll);
            this.groupBox2.Controls.Add(this.comboBoxValues);
            this.groupBox2.Controls.Add(this.comboBoxReq);
            this.groupBox2.Location = new System.Drawing.Point(7, 54);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(195, 99);
            this.groupBox2.TabIndex = 16;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Filters";
            // 
            // checkBoxAll
            // 
            this.checkBoxAll.AutoSize = true;
            this.checkBoxAll.Checked = true;
            this.checkBoxAll.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxAll.Enabled = false;
            this.checkBoxAll.Location = new System.Drawing.Point(7, 19);
            this.checkBoxAll.Name = "checkBoxAll";
            this.checkBoxAll.Size = new System.Drawing.Size(37, 17);
            this.checkBoxAll.TabIndex = 16;
            this.checkBoxAll.Text = "All";
            this.checkBoxAll.UseVisualStyleBackColor = true;
            this.checkBoxAll.CheckedChanged += new System.EventHandler(this.checkBoxAll_CheckedChanged);
            // 
            // comboBoxValues
            // 
            this.comboBoxValues.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.comboBoxValues.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxValues.Enabled = false;
            this.comboBoxValues.FormattingEnabled = true;
            this.comboBoxValues.Items.AddRange(new object[] {
            "Non-compliant (=0)",
            "Compliant (=1)",
            "Dummy (=-1)"});
            this.comboBoxValues.Location = new System.Drawing.Point(7, 45);
            this.comboBoxValues.Name = "comboBoxValues";
            this.comboBoxValues.Size = new System.Drawing.Size(182, 21);
            this.comboBoxValues.TabIndex = 15;
            this.comboBoxValues.SelectedIndexChanged += new System.EventHandler(this.comboBoxValues_SelectedIndexChanged);
            // 
            // comboBoxReq
            // 
            this.comboBoxReq.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.comboBoxReq.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxReq.Enabled = false;
            this.comboBoxReq.FormattingEnabled = true;
            this.comboBoxReq.Items.AddRange(new object[] {
            "Blurred",
            "Looking Away",
            "Ink Marked/Creased",
            "Unnatural Skin Tone",
            "Too Dark/Light",
            "Washed Out",
            "Pixelation",
            "Hair Across Eyes",
            "Eyes Closed",
            "Varied Background",
            "Roll/Pitch/Yaw > 8°",
            "Flash Reflection on Skin",
            "Red Eyes",
            "Shadows Behind Head",
            "Shadows Across Face",
            "Dark Tinted Lenses",
            "Flash Reflection on Lenses",
            "Frames Too Heavy",
            "Frame Coverings Eyes",
            "Hat/Cap",
            "Veil Over Face",
            "Mouth Open",
            "Presence of Other Faces of Toys Too Close to Face"});
            this.comboBoxReq.Location = new System.Drawing.Point(6, 72);
            this.comboBoxReq.Name = "comboBoxReq";
            this.comboBoxReq.Size = new System.Drawing.Size(183, 21);
            this.comboBoxReq.TabIndex = 14;
            this.comboBoxReq.SelectedIndexChanged += new System.EventHandler(this.comboBoxValues_SelectedIndexChanged);
            // 
            // buttonDummy
            // 
            this.buttonDummy.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonDummy.BackColor = System.Drawing.SystemColors.ActiveBorder;
            this.buttonDummy.Enabled = false;
            this.buttonDummy.Font = new System.Drawing.Font("Verdana", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonDummy.Location = new System.Drawing.Point(73, 561);
            this.buttonDummy.Name = "buttonDummy";
            this.buttonDummy.Size = new System.Drawing.Size(63, 41);
            this.buttonDummy.TabIndex = 2;
            this.buttonDummy.Text = "DUM";
            this.buttonDummy.UseVisualStyleBackColor = false;
            this.buttonDummy.Click += new System.EventHandler(this.buttonDummy_Click);
            // 
            // buttonAcc
            // 
            this.buttonAcc.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonAcc.BackColor = System.Drawing.Color.ForestGreen;
            this.buttonAcc.Enabled = false;
            this.buttonAcc.Font = new System.Drawing.Font("Verdana", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonAcc.ForeColor = System.Drawing.SystemColors.ControlLightLight;
            this.buttonAcc.Location = new System.Drawing.Point(142, 561);
            this.buttonAcc.Name = "buttonAcc";
            this.buttonAcc.Size = new System.Drawing.Size(60, 41);
            this.buttonAcc.TabIndex = 13;
            this.buttonAcc.Text = "ACC";
            this.buttonAcc.UseVisualStyleBackColor = false;
            this.buttonAcc.Click += new System.EventHandler(this.buttonAcc_Click);
            // 
            // buttonReject
            // 
            this.buttonReject.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.buttonReject.BackColor = System.Drawing.Color.Red;
            this.buttonReject.Enabled = false;
            this.buttonReject.Font = new System.Drawing.Font("Verdana", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonReject.ForeColor = System.Drawing.SystemColors.ControlLightLight;
            this.buttonReject.Location = new System.Drawing.Point(7, 561);
            this.buttonReject.Name = "buttonReject";
            this.buttonReject.Size = new System.Drawing.Size(60, 41);
            this.buttonReject.TabIndex = 12;
            this.buttonReject.Text = "REJ";
            this.buttonReject.UseVisualStyleBackColor = false;
            this.buttonReject.Click += new System.EventHandler(this.buttonReject_Click);
            // 
            // listBoxImgs
            // 
            this.listBoxImgs.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.listBoxImgs.Enabled = false;
            this.listBoxImgs.FormattingEnabled = true;
            this.listBoxImgs.Location = new System.Drawing.Point(7, 156);
            this.listBoxImgs.Name = "listBoxImgs";
            this.listBoxImgs.Size = new System.Drawing.Size(195, 394);
            this.listBoxImgs.TabIndex = 11;
            this.listBoxImgs.SelectedIndexChanged += new System.EventHandler(this.listBoxImgs_SelectedIndexChanged);
            // 
            // buttonOpenDir
            // 
            this.buttonOpenDir.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonOpenDir.Image = ((System.Drawing.Image)(resources.GetObject("buttonOpenDir.Image")));
            this.buttonOpenDir.ImageAlign = System.Drawing.ContentAlignment.TopCenter;
            this.buttonOpenDir.Location = new System.Drawing.Point(7, 3);
            this.buttonOpenDir.Name = "buttonOpenDir";
            this.buttonOpenDir.Size = new System.Drawing.Size(195, 45);
            this.buttonOpenDir.TabIndex = 1;
            this.buttonOpenDir.Text = "Load Images";
            this.buttonOpenDir.TextAlign = System.Drawing.ContentAlignment.BottomCenter;
            this.buttonOpenDir.UseVisualStyleBackColor = true;
            this.buttonOpenDir.Click += new System.EventHandler(this.buttonOpenDir_Click);
            // 
            // panel1
            // 
            this.panel1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel1.Controls.Add(this.buttonOpenDir);
            this.panel1.Controls.Add(this.listBoxImgs);
            this.panel1.Controls.Add(this.buttonReject);
            this.panel1.Controls.Add(this.buttonAcc);
            this.panel1.Controls.Add(this.buttonDummy);
            this.panel1.Controls.Add(this.groupBox2);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Left;
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(210, 607);
            this.panel1.TabIndex = 11;
            // 
            // panel2
            // 
            this.panel2.AutoScroll = true;
            this.panel2.Controls.Add(this.picBox);
            this.panel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel2.Location = new System.Drawing.Point(0, 0);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(719, 607);
            this.panel2.TabIndex = 3;
            // 
            // picBox
            // 
            this.picBox.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.picBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.picBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.picBox.Location = new System.Drawing.Point(0, 0);
            this.picBox.Name = "picBox";
            this.picBox.Size = new System.Drawing.Size(719, 607);
            this.picBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.picBox.TabIndex = 1;
            this.picBox.TabStop = false;
            // 
            // listViewReqs
            // 
            this.listViewReqs.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.ColReqs});
            this.listViewReqs.Dock = System.Windows.Forms.DockStyle.Fill;
            this.listViewReqs.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.listViewReqs.FullRowSelect = true;
            this.listViewReqs.GridLines = true;
            this.listViewReqs.Location = new System.Drawing.Point(0, 0);
            this.listViewReqs.MultiSelect = false;
            this.listViewReqs.Name = "listViewReqs";
            this.listViewReqs.Size = new System.Drawing.Size(217, 607);
            this.listViewReqs.TabIndex = 2;
            this.listViewReqs.UseCompatibleStateImageBehavior = false;
            this.listViewReqs.View = System.Windows.Forms.View.Details;
            this.listViewReqs.MouseClick += new System.Windows.Forms.MouseEventHandler(this.listViewReqs_MouseClick);
            // 
            // ColReqs
            // 
            this.ColReqs.Text = "Requirements";
            this.ColReqs.Width = 200;
            // 
            // panelMain
            // 
            this.panelMain.Controls.Add(this.panel1);
            this.panelMain.Controls.Add(this.panel2);
            this.panelMain.Controls.Add(this.panel3);
            this.panelMain.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panelMain.Location = new System.Drawing.Point(0, 0);
            this.panelMain.Name = "panelMain";
            this.panelMain.Size = new System.Drawing.Size(936, 607);
            this.panelMain.TabIndex = 13;
            // 
            // panel3
            // 
            this.panel3.Controls.Add(this.listViewReqs);
            this.panel3.Dock = System.Windows.Forms.DockStyle.Right;
            this.panel3.Location = new System.Drawing.Point(719, 0);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(217, 607);
            this.panel3.TabIndex = 3;
            // 
            // fileDialog
            // 
            this.fileDialog.FileName = "openFileDialog1";
            // 
            // MRKEditor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Window;
            this.ClientSize = new System.Drawing.Size(936, 607);
            this.Controls.Add(this.panelMain);
            this.Name = "MRKEditor";
            this.Text = "MRK Editor";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.picBox)).EndInit();
            this.panelMain.ResumeLayout(false);
            this.panel3.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.ComboBox comboBoxReq;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Button buttonDummy;
        private System.Windows.Forms.Button buttonAcc;
        private System.Windows.Forms.Button buttonReject;
        private System.Windows.Forms.ListBox listBoxImgs;
        private System.Windows.Forms.Button buttonOpenDir;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.PictureBox picBox;
        private System.Windows.Forms.Panel panelMain;
        private System.Windows.Forms.ComboBox comboBoxValues;
        private System.Windows.Forms.OpenFileDialog fileDialog;
        private System.Windows.Forms.ListView listViewReqs;
        private System.Windows.Forms.ColumnHeader ColReqs;
        private System.Windows.Forms.CheckBox checkBoxAll;
        private System.Windows.Forms.Panel panel3;
    }
}