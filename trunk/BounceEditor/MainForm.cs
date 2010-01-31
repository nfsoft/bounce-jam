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
    public partial class MainForm : Form
    {
        private ObjectListForm objectListForm;
        private string filename = null;

        private PointF actorPosition = new PointF(2,2);
        private bool actorPlacingMode = false;

        public static float SCALE;

        public MainForm()
        {
            InitializeComponent();

            objectListForm = new ObjectListForm(this);
            objectListForm.Show(this);

            SCALE = (float)pictureBox1.Width/32.0f;
        }

        private void pictureBox1_Paint(object sender, PaintEventArgs e)
        {
            float x, y;
            try
            {
                x = Convert.ToSingle(txtX.Text);
                y = Convert.ToSingle(txtY.Text);
            }
            catch (FormatException)
            {
                return;
            }

            e.Graphics.TranslateTransform(-x * SCALE, pictureBox1.Height+y * SCALE);
            e.Graphics.ScaleTransform(1, -1);
            e.Graphics.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
            e.Graphics.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.HighQualityBicubic;
           // e.Graphics.DrawEllipse(new Pen(Color.Green), (actorPosition.X - 0.5f) * SCALE, pictureBox1.Height - ((actorPosition.Y + 0.5f) * SCALE), 1 * SCALE, 1 * SCALE);
            e.Graphics.FillEllipse(new SolidBrush(Color.Green), (actorPosition.X - 0.5f) * SCALE, (actorPosition.Y - 0.5f) * SCALE, SCALE, SCALE);
            e.Graphics.DrawEllipse(new Pen(actorPlacingMode ? Color.Red : Color.Black), (actorPosition.X - 0.5f) * SCALE, (actorPosition.Y - 0.5f) * SCALE, SCALE, SCALE);

            TreeView tv = objectListForm.getStaticList();
            foreach (TreeNode body in tv.Nodes)
            {
                Color clr = Color.Black;
                if (tv.SelectedNode == body && !objectListForm.isInDynamicMode()) clr = Color.DarkRed;
                foreach (TreeNode polygon in body.Nodes)
                {
                    if (polygon.Text == "Polygon")
                    {
                        List<PointF> points = new List<PointF>();
                        bool selected = polygon == tv.SelectedNode && !objectListForm.isInDynamicMode();
                        foreach (TreeNode point in polygon.Nodes)
                        {
                            PointF p = (PointF)point.Tag;
                            p.X *= SCALE;
                            p.Y *= SCALE;
                            //p.Y = pictureBox1.Height - (p.Y) * SCALE;
                            points.Add(p);
                            if (point == tv.SelectedNode && !objectListForm.isInDynamicMode())
                            {
                                e.Graphics.DrawRectangle(new Pen(Color.Red), p.X, p.Y, 5, 5);
                                selected = true;
                            }
                            else
                            {
                                e.Graphics.DrawRectangle(new Pen(Color.Black), p.X, p.Y, 2, 2);
                            }
                        }
                        if (points.Count >= 2)
                            e.Graphics.DrawPolygon(new Pen(selected ? Color.Red : clr), points.ToArray());
                    }
                    else if (polygon.Text == "Circle")
                    {
                        
                    }
                }
            }

            ListBox dynobjs = objectListForm.getDynamicList();
            foreach (Object o in dynobjs.Items)
            {
                ((DynamicPlacement)o).Draw(e.Graphics, objectListForm.isInDynamicMode() && dynobjs.SelectedItem == o);
            }
        }

        private void pictureBox1_MouseClick(object sender, MouseEventArgs e)
        {
            if (actorPlacingMode)
            {
                actorPosition.X = (e.X - Convert.ToInt32(txtX.Text)) / SCALE;
                actorPosition.Y = (pictureBox1.Height - e.Y - Convert.ToInt32(txtY.Text)) / SCALE;
                actorPlacingMode = false;
                Refresh();
                return;
            }
            else if (objectListForm.isInDynamicMode())
            {
                if (objectListForm.getDynamicList().SelectedItem == null) return;
                ((DynamicPlacement)objectListForm.getDynamicList().SelectedItem).position = new PointF(e.X / SCALE + Convert.ToSingle(txtX.Text), (pictureBox1.Height - e.Y) / SCALE + Convert.ToSingle(txtY.Text));
                objectListForm.Refresh();
            }
            else
            {
                if (objectListForm.getStaticList().SelectedNode == null) return;
                if (objectListForm.getStaticList().SelectedNode.Text == "Polygon")
                {
                    objectListForm.addPoint(objectListForm.getStaticList().SelectedNode, new PointF(e.X / SCALE + Convert.ToSingle(txtX.Text), (pictureBox1.Height - e.Y) / SCALE + Convert.ToSingle(txtY.Text)));
                }
            }
            objectListForm.Refresh();
            Refresh();
        }


        private void pictureBox1_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.Button != MouseButtons.Left) return;
            if (objectListForm.isInDynamicMode())
            {
                if (objectListForm.getDynamicList().SelectedItem == null) return;
                ((DynamicPlacement)objectListForm.getDynamicList().SelectedItem).position = new PointF(e.X / SCALE + Convert.ToSingle(txtX.Text), (pictureBox1.Height - e.Y) / SCALE + Convert.ToSingle(txtY.Text));
            }
            else
            {
                if (objectListForm.getStaticList().SelectedNode == null) return;
                if (objectListForm.getStaticList().SelectedNode.Text == "Point")
                    objectListForm.getStaticList().SelectedNode.Tag = new PointF(e.X / SCALE + Convert.ToSingle(txtX.Text), (pictureBox1.Height - e.Y) / SCALE + Convert.ToSingle(txtY.Text));
            }
            objectListForm.Refresh();
            Refresh();
        }

        private void MainForm_Paint(object sender, PaintEventArgs e)
        {
            pictureBox1.Update();
        }

        private void btnUp_Click(object sender, EventArgs e)
        {
            txtY.Text = (Convert.ToInt32(txtY.Text) + 1).ToString();
            Refresh();
        }

        private void btnDown_Click(object sender, EventArgs e)
        {
            txtY.Text = (Convert.ToInt32(txtY.Text) - 1).ToString();
            Refresh();
        }

        private void btnLeft_Click(object sender, EventArgs e)
        {
            txtX.Text = (Convert.ToInt32(txtX.Text) - 1).ToString();
            Refresh();
        }

        private void btnRight_Click(object sender, EventArgs e)
        {
            txtX.Text = (Convert.ToInt32(txtX.Text) + 1).ToString();
            Refresh();
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.DefaultExt = "lev";
            ofd.Filter = "Bounce levels (*.lev)|*.lev|All files|*.*";
            ofd.Multiselect = false;
            if (ofd.ShowDialog() != DialogResult.OK) return;

            objectListForm.Close();
            objectListForm = new ObjectListForm(this);
            objectListForm.Show();

            txtX.Text = txtY.Text = "0";

            filename = ofd.FileName;
            StreamReader file = new StreamReader(filename);

            string ln = file.ReadLine();

            if (!ln.StartsWith("actor ")) throw new Exception("Error parsing input, 'actor ' expected.");

            string[] actorpos = ln.Split(' ');
            actorPosition.X = Convert.ToSingle(actorpos[1]);
            actorPosition.Y = Convert.ToSingle(actorpos[2]);
            
            ln = file.ReadLine();
            if (ln != "static") throw new Exception("Error parsing input, 'static' expected.");

            if (objectListForm.loadStaticData(file) != "dynamic") { }// throw new Exception("Error parsing input, 'dynamic' expected.");

            objectListForm.loadDynamicData(file);

            file.Close();
            Refresh();
        }

        private void saveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog sfd = new SaveFileDialog();
            sfd.DefaultExt = "lev";
            sfd.Filter = "Bounce levels (*.lev)|*.lev|All files|*.*";
            if (sfd.ShowDialog() != DialogResult.OK) return;
            filename = sfd.FileName;
            saveToolStripMenuItem_Click(sender, e);
        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (filename == null)
            {
                saveAsToolStripMenuItem_Click(sender, e);
                return;
            }

            StreamWriter file = new StreamWriter(filename);

            file.WriteLine("actor " + actorPosition.X + " " + actorPosition.Y);

            objectListForm.saveStaticData(file);
            objectListForm.saveDynamicData(file);

            file.Close();
        }

        private void txtX_TextChanged(object sender, EventArgs e)
        {
            Refresh();
        }

        private void txtY_TextChanged(object sender, EventArgs e)
        {
            Refresh();
        }

        private void setActorPositionToolStripMenuItem_Click(object sender, EventArgs e)
        {
            actorPlacingMode = true;
            Refresh();
        }

        private void MainForm_VisibleChanged(object sender, EventArgs e)
        {
            objectListForm.BringToFront();
        }

        private void newToolStripMenuItem_Click(object sender, EventArgs e)
        {
            objectListForm.Close();
            objectListForm = new ObjectListForm(this);
            objectListForm.Show();

            txtX.Text = txtY.Text = "0";

            filename = null;
        }

        private void giveMeBackMyFuckingPanelToolStripMenuItem_Click(object sender, EventArgs e)
        {
            objectListForm.BringToFront();
            objectListForm.Show();
            objectListForm.Refresh();
        }

    }
}
