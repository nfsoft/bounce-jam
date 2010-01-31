using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace BounceEditor
{
    public partial class ObjectChooser : Form
    {
        public ObjectChooser()
        {
            InitializeComponent();

            DirectoryInfo dir = new DirectoryInfo(".");

            prototypesList.LargeImageList = new ImageList();
            prototypesList.LargeImageList.ImageSize = new Size(96, 96);
            prototypesList.LargeImageList.ColorDepth = ColorDepth.Depth32Bit;

            FileInfo[] files = dir.GetFiles("*.obj");
            foreach (FileInfo f in files)
            {
                DynamicObject dynobj = new DynamicObject(f.Name);
                prototypesList.LargeImageList.Images.Add(dynobj.image);
                ListViewItem lvi = new ListViewItem(f.Name, prototypesList.LargeImageList.Images.Count - 1);
                lvi.Tag = dynobj;
                prototypesList.Items.Add(lvi);
            }
        }

        public void Unselect()
        {
            prototypesList.SelectedItems.Clear();
            btnOK.Enabled = false;
        }

        public DynamicObject GetByName(string name)
        {
            foreach (ListViewItem lvi in prototypesList.Items)
            {
                if (lvi.Text == name) return (DynamicObject)lvi.Tag;
            }
            throw new Exception("Unknown object");
        }

        public DynamicObject GetSelected()
        {
            return prototypesList.SelectedItems.Count == 0 ? null : (DynamicObject)prototypesList.SelectedItems[0].Tag;
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            Unselect();
            Hide();
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            Hide();
        }

        private void prototypesList_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (prototypesList.SelectedItems.Count == 1)
                btnOK.Enabled = true;
            else
                btnOK.Enabled = false;
        }

    }
}
