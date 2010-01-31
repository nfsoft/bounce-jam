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
    public partial class ObjectListForm : Form
    {
        private MainForm mainForm;
        private ObjectChooser objectChooser;

        public ObjectListForm(MainForm mf)
        {
            mainForm = mf;
            InitializeComponent();

            //dynamicList.Items.Add(new DynamicPlacement());

            objectChooser = new ObjectChooser();

        }

        public bool isInDynamicMode()
        {
            return (tabControl1.SelectedIndex == 1);
        }

        public TreeView getStaticList()
        {
            return staticList;
        }

        public ListBox getDynamicList()
        {
            return dynamicList;
        }

        public TreeNode addBody(Body body)
        {
            TreeNode tmp = new TreeNode("Body");
            tmp.Tag = body;
            tmp.ContextMenuStrip = BodyContextMenu;
            staticList.Nodes.Add(tmp);
            return tmp;
        }
        public TreeNode addPolygon(TreeNode body, Polygon polygon)
        {
            TreeNode tmp = new TreeNode("Polygon");
            tmp.Tag = polygon;
            tmp.ContextMenuStrip = PolygonContextMenu;
            body.Nodes.Add(tmp);
            body.Expand();
            return tmp;
        }
        public void addPoint(TreeNode polygon, PointF point)
        {
            TreeNode tmp = new TreeNode("Point");
            tmp.Tag = point;
            tmp.ContextMenuStrip = PointContextMenu;
            polygon.Nodes.Add(tmp);
            polygon.Expand();
        }

        private void staticList_NodeMouseClick(object sender, TreeNodeMouseClickEventArgs e)
        {
            staticList.SelectedNode = e.Node;
            mainForm.Refresh();
        }

        #region CONTEXT_MENUS
        private void newBodyToolStripMenuItem_Click(object sender, EventArgs e)
        {
            addBody(new Body());
        }

        private void removeBodyToolStripMenuItem_Click(object sender, EventArgs e)
        {
            staticList.Nodes.Remove(staticList.SelectedNode);
        }

        private void newPolygonToolStripMenuItem_Click(object sender, EventArgs e)
        {
            addPolygon(staticList.SelectedNode, new Polygon());
        }

        private void removePolygonToolStripMenuItem_Click(object sender, EventArgs e)
        {
            staticList.Nodes.Remove(staticList.SelectedNode);
        }

        private void addPointToolStripMenuItem_Click(object sender, EventArgs e)
        {
            addPoint(staticList.SelectedNode,new Point());
        }

        private void removePointToolStripMenuItem_Click(object sender, EventArgs e)
        {
            staticList.Nodes.Remove(staticList.SelectedNode);
        }
        #endregion

        public string loadStaticData(StreamReader src)
        {
            string ln = src.ReadLine();
            while (ln == "body")
            {
                TreeNode bodyNode = addBody(new Body());
                //ln = src.ReadLine();
                //if (!ln.StartsWith("position ")) throw new Exception("Error parsing input, 'position ' expected.");
                //string[] pos = 
                ln = src.ReadLine();
                while (ln!=null && ln.StartsWith("polygon ") || ln == "circle")
                {
                    //if (ln.Length==0 && src.EndOfStream)
                    if (ln.StartsWith("polygon "))
                    {
                        TreeNode polygonNode = addPolygon(bodyNode, new Polygon());
                        int count = Convert.ToInt32(ln.Split(' ')[1]);
                        for (int i = 0; i < count; ++i)
                        {
                            ln = src.ReadLine();
                            string[] loc = ln.Split(' ');
                            addPoint(polygonNode, new PointF(Convert.ToSingle(loc[0]), Convert.ToSingle(loc[1])));
                        }
                    }
                    ln = src.ReadLine();
                }
            }
            return ln;
        }

        public void saveStaticData(StreamWriter dst)
        {
            dst.WriteLine("static");
            foreach (TreeNode body in staticList.Nodes)
            {
                dst.WriteLine("body");
                foreach (TreeNode polygon in body.Nodes)
                {
                    if (polygon.Text == "Polygon" && polygon.Nodes.Count > 2)
                    {
                        dst.WriteLine("polygon " + polygon.Nodes.Count);
                        foreach (TreeNode point in polygon.Nodes)
                        {
                            dst.WriteLine(((PointF)point.Tag).X.ToString() + " " + ((PointF)point.Tag).Y.ToString());
                        }
                    }
                }
            }
        }

        public void loadDynamicData(StreamReader src)
        {
            string ln = src.ReadLine();
            while (ln!=null && ln.StartsWith("dp "))
            {
                string[] dp = ln.Split(' ');
                DynamicPlacement dynp = new DynamicPlacement(objectChooser.GetByName(dp[1]));
                dynp.position.X = Convert.ToSingle(dp[2]);
                dynp.position.Y = Convert.ToSingle(dp[3]);
                dynp.rotation = Convert.ToSingle(dp[4]);
                dynamicList.Items.Add(dynp);
                ln = src.ReadLine();
            }
            mainForm.Refresh();
            Refresh();
        }

        public void saveDynamicData(StreamWriter dst)
        {
            dst.WriteLine("dynamic");
            foreach (DynamicPlacement dp in dynamicList.Items)
            {
                dst.WriteLine("dp " + dp.dynamicObject.filename + " " + dp.position.X + " " + dp.position.Y + " " + dp.rotation);
            }
        }

        private void dynamicList_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (dynamicList.SelectedItem == null)
                RotationBar.Enabled = false;
            else
            {
                RotationBar.Value = (int)((DynamicPlacement)dynamicList.SelectedItem).rotation;
                RotationBar.Enabled = true;
            }
            mainForm.Refresh();
        }

        private void addDynamicObjectToolStripMenuItem_Click(object sender, EventArgs e)
        {
            objectChooser.ShowDialog(this);
            if (objectChooser.GetSelected() == null) return;
            DynamicPlacement dp = new DynamicPlacement(objectChooser.GetSelected());
            dynamicList.Items.Add(dp);
            dynamicList.SelectedItem = dp;
            mainForm.Refresh();
        }

        private void removeDynamicObjectToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (dynamicList.SelectedItem == null) return;
            dynamicList.Items.Remove(dynamicList.SelectedItem);
            mainForm.Refresh();
            Refresh();
        }

        private void ObjectListForm_Load(object sender, EventArgs e)
        {
            this.Location = new Point(mainForm.Location.X + mainForm.Width + 20, mainForm.Location.Y);
        }

        private void tabControl1_SelectedIndexChanged(object sender, EventArgs e)
        {
            RotationBar.Visible = isInDynamicMode();
            mainForm.Refresh();
        }

        private void ObjectListForm_Paint(object sender, PaintEventArgs e)
        {
            dynamicList.DisplayMember = "_";
            dynamicList.DisplayMember = "";
        }

        private void RotationBar_ValueChanged(object sender, EventArgs e)
        {
            ((DynamicPlacement)dynamicList.SelectedItem).rotation = RotationBar.Value;
            mainForm.Refresh();
            Refresh();
        }
    }
}
