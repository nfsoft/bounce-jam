namespace BounceEditor
{
    partial class ObjectListForm
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
            this.components = new System.ComponentModel.Container();
            this.RootContextMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.newBodyToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.staticList = new System.Windows.Forms.TreeView();
            this.BodyContextMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.newPolygonToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.removeBodyToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.PolygonContextMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.addPointToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.removePolygonToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.PointContextMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.removePointToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabStatic = new System.Windows.Forms.TabPage();
            this.tabDynamic = new System.Windows.Forms.TabPage();
            this.dynamicList = new System.Windows.Forms.ListBox();
            this.DynamicListContextMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.addDynamicObjectToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.removeDynamicObjectToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.RotationBar = new System.Windows.Forms.HScrollBar();
            this.RootContextMenu.SuspendLayout();
            this.BodyContextMenu.SuspendLayout();
            this.PolygonContextMenu.SuspendLayout();
            this.PointContextMenu.SuspendLayout();
            this.tabControl1.SuspendLayout();
            this.tabStatic.SuspendLayout();
            this.tabDynamic.SuspendLayout();
            this.DynamicListContextMenu.SuspendLayout();
            this.SuspendLayout();
            // 
            // RootContextMenu
            // 
            this.RootContextMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newBodyToolStripMenuItem});
            this.RootContextMenu.Name = "RootContextMenu";
            this.RootContextMenu.Size = new System.Drawing.Size(129, 26);
            // 
            // newBodyToolStripMenuItem
            // 
            this.newBodyToolStripMenuItem.Name = "newBodyToolStripMenuItem";
            this.newBodyToolStripMenuItem.Size = new System.Drawing.Size(128, 22);
            this.newBodyToolStripMenuItem.Text = "New Body";
            this.newBodyToolStripMenuItem.Click += new System.EventHandler(this.newBodyToolStripMenuItem_Click);
            // 
            // staticList
            // 
            this.staticList.ContextMenuStrip = this.RootContextMenu;
            this.staticList.Location = new System.Drawing.Point(0, 0);
            this.staticList.Name = "staticList";
            this.staticList.Size = new System.Drawing.Size(253, 500);
            this.staticList.TabIndex = 0;
            this.staticList.NodeMouseClick += new System.Windows.Forms.TreeNodeMouseClickEventHandler(this.staticList_NodeMouseClick);
            // 
            // BodyContextMenu
            // 
            this.BodyContextMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newPolygonToolStripMenuItem,
            this.removeBodyToolStripMenuItem});
            this.BodyContextMenu.Name = "BodyContextMenu";
            this.BodyContextMenu.Size = new System.Drawing.Size(148, 48);
            // 
            // newPolygonToolStripMenuItem
            // 
            this.newPolygonToolStripMenuItem.Name = "newPolygonToolStripMenuItem";
            this.newPolygonToolStripMenuItem.Size = new System.Drawing.Size(147, 22);
            this.newPolygonToolStripMenuItem.Text = "New Polygon";
            this.newPolygonToolStripMenuItem.Click += new System.EventHandler(this.newPolygonToolStripMenuItem_Click);
            // 
            // removeBodyToolStripMenuItem
            // 
            this.removeBodyToolStripMenuItem.Name = "removeBodyToolStripMenuItem";
            this.removeBodyToolStripMenuItem.Size = new System.Drawing.Size(147, 22);
            this.removeBodyToolStripMenuItem.Text = "Remove Body";
            this.removeBodyToolStripMenuItem.Click += new System.EventHandler(this.removeBodyToolStripMenuItem_Click);
            // 
            // PolygonContextMenu
            // 
            this.PolygonContextMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.addPointToolStripMenuItem,
            this.removePolygonToolStripMenuItem});
            this.PolygonContextMenu.Name = "PolygonContextMenu";
            this.PolygonContextMenu.Size = new System.Drawing.Size(162, 48);
            // 
            // addPointToolStripMenuItem
            // 
            this.addPointToolStripMenuItem.Name = "addPointToolStripMenuItem";
            this.addPointToolStripMenuItem.Size = new System.Drawing.Size(161, 22);
            this.addPointToolStripMenuItem.Text = "Add Point";
            this.addPointToolStripMenuItem.Click += new System.EventHandler(this.addPointToolStripMenuItem_Click);
            // 
            // removePolygonToolStripMenuItem
            // 
            this.removePolygonToolStripMenuItem.Name = "removePolygonToolStripMenuItem";
            this.removePolygonToolStripMenuItem.Size = new System.Drawing.Size(161, 22);
            this.removePolygonToolStripMenuItem.Text = "RemovePolygon";
            this.removePolygonToolStripMenuItem.Click += new System.EventHandler(this.removePolygonToolStripMenuItem_Click);
            // 
            // PointContextMenu
            // 
            this.PointContextMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.removePointToolStripMenuItem});
            this.PointContextMenu.Name = "PointContextMenu";
            this.PointContextMenu.Size = new System.Drawing.Size(149, 26);
            // 
            // removePointToolStripMenuItem
            // 
            this.removePointToolStripMenuItem.Name = "removePointToolStripMenuItem";
            this.removePointToolStripMenuItem.Size = new System.Drawing.Size(148, 22);
            this.removePointToolStripMenuItem.Text = "Remove Point";
            this.removePointToolStripMenuItem.Click += new System.EventHandler(this.removePointToolStripMenuItem_Click);
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabStatic);
            this.tabControl1.Controls.Add(this.tabDynamic);
            this.tabControl1.Location = new System.Drawing.Point(1, 2);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(261, 532);
            this.tabControl1.TabIndex = 6;
            this.tabControl1.SelectedIndexChanged += new System.EventHandler(this.tabControl1_SelectedIndexChanged);
            // 
            // tabStatic
            // 
            this.tabStatic.Controls.Add(this.staticList);
            this.tabStatic.Location = new System.Drawing.Point(4, 22);
            this.tabStatic.Name = "tabStatic";
            this.tabStatic.Padding = new System.Windows.Forms.Padding(3);
            this.tabStatic.Size = new System.Drawing.Size(253, 506);
            this.tabStatic.TabIndex = 0;
            this.tabStatic.Text = "Static";
            this.tabStatic.UseVisualStyleBackColor = true;
            // 
            // tabDynamic
            // 
            this.tabDynamic.Controls.Add(this.dynamicList);
            this.tabDynamic.Location = new System.Drawing.Point(4, 22);
            this.tabDynamic.Name = "tabDynamic";
            this.tabDynamic.Padding = new System.Windows.Forms.Padding(3);
            this.tabDynamic.Size = new System.Drawing.Size(253, 506);
            this.tabDynamic.TabIndex = 1;
            this.tabDynamic.Text = "Dynamic";
            this.tabDynamic.UseVisualStyleBackColor = true;
            // 
            // dynamicList
            // 
            this.dynamicList.ContextMenuStrip = this.DynamicListContextMenu;
            this.dynamicList.FormattingEnabled = true;
            this.dynamicList.Location = new System.Drawing.Point(0, 0);
            this.dynamicList.Name = "dynamicList";
            this.dynamicList.Size = new System.Drawing.Size(253, 498);
            this.dynamicList.TabIndex = 0;
            this.dynamicList.SelectedIndexChanged += new System.EventHandler(this.dynamicList_SelectedIndexChanged);
            // 
            // DynamicListContextMenu
            // 
            this.DynamicListContextMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.addDynamicObjectToolStripMenuItem,
            this.removeDynamicObjectToolStripMenuItem});
            this.DynamicListContextMenu.Name = "DynamicListContextMenu";
            this.DynamicListContextMenu.Size = new System.Drawing.Size(206, 48);
            // 
            // addDynamicObjectToolStripMenuItem
            // 
            this.addDynamicObjectToolStripMenuItem.Name = "addDynamicObjectToolStripMenuItem";
            this.addDynamicObjectToolStripMenuItem.Size = new System.Drawing.Size(205, 22);
            this.addDynamicObjectToolStripMenuItem.Text = "Add Dynamic Object";
            this.addDynamicObjectToolStripMenuItem.Click += new System.EventHandler(this.addDynamicObjectToolStripMenuItem_Click);
            // 
            // removeDynamicObjectToolStripMenuItem
            // 
            this.removeDynamicObjectToolStripMenuItem.Name = "removeDynamicObjectToolStripMenuItem";
            this.removeDynamicObjectToolStripMenuItem.Size = new System.Drawing.Size(205, 22);
            this.removeDynamicObjectToolStripMenuItem.Text = "Remove Dynamic Object";
            this.removeDynamicObjectToolStripMenuItem.Click += new System.EventHandler(this.removeDynamicObjectToolStripMenuItem_Click);
            // 
            // RotationBar
            // 
            this.RotationBar.Enabled = false;
            this.RotationBar.Location = new System.Drawing.Point(110, 0);
            this.RotationBar.Maximum = 360;
            this.RotationBar.Name = "RotationBar";
            this.RotationBar.Size = new System.Drawing.Size(141, 21);
            this.RotationBar.TabIndex = 7;
            this.RotationBar.Visible = false;
            this.RotationBar.ValueChanged += new System.EventHandler(this.RotationBar_ValueChanged);
            // 
            // ObjectListForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(260, 527);
            this.ControlBox = false;
            this.Controls.Add(this.RotationBar);
            this.Controls.Add(this.tabControl1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "ObjectListForm";
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
            this.Text = "Objects";
            this.Load += new System.EventHandler(this.ObjectListForm_Load);
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.ObjectListForm_Paint);
            this.RootContextMenu.ResumeLayout(false);
            this.BodyContextMenu.ResumeLayout(false);
            this.PolygonContextMenu.ResumeLayout(false);
            this.PointContextMenu.ResumeLayout(false);
            this.tabControl1.ResumeLayout(false);
            this.tabStatic.ResumeLayout(false);
            this.tabDynamic.ResumeLayout(false);
            this.DynamicListContextMenu.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TreeView staticList;
        private System.Windows.Forms.ContextMenuStrip RootContextMenu;
        private System.Windows.Forms.ToolStripMenuItem newBodyToolStripMenuItem;
        private System.Windows.Forms.ContextMenuStrip BodyContextMenu;
        private System.Windows.Forms.ToolStripMenuItem newPolygonToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem removeBodyToolStripMenuItem;
        private System.Windows.Forms.ContextMenuStrip PolygonContextMenu;
        private System.Windows.Forms.ToolStripMenuItem removePolygonToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem addPointToolStripMenuItem;
        public System.Windows.Forms.ContextMenuStrip PointContextMenu;
        private System.Windows.Forms.ToolStripMenuItem removePointToolStripMenuItem;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabStatic;
        private System.Windows.Forms.TabPage tabDynamic;
        private System.Windows.Forms.ListBox dynamicList;
        private System.Windows.Forms.ContextMenuStrip DynamicListContextMenu;
        private System.Windows.Forms.ToolStripMenuItem addDynamicObjectToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem removeDynamicObjectToolStripMenuItem;
        private System.Windows.Forms.HScrollBar RotationBar;
    }
}