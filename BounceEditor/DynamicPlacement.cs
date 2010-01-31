using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Drawing.Drawing2D;

namespace BounceEditor
{
    public class DynamicPlacement
    {
        public PointF position = new PointF(5,5);
        public float rotation = 10;
        public DynamicObject dynamicObject;
        //public Graphics rotated;

        public DynamicPlacement(DynamicObject dynamicObject)
        {
            this.dynamicObject = dynamicObject;
        }

        public void Draw(Graphics where, bool selected)
        {
            //where.ScaleTransform(1, -1);

            where.TranslateTransform(position.X * MainForm.SCALE, position.Y * MainForm.SCALE);

            where.RotateTransform(rotation);

            where.DrawImage(dynamicObject.image, 0, 0, dynamicObject.size.X*MainForm.SCALE, dynamicObject.size.Y*MainForm.SCALE);
            if (selected) where.DrawRectangle(new Pen(Color.Red), 0, 0, dynamicObject.size.X * MainForm.SCALE, dynamicObject.size.Y * MainForm.SCALE);

            where.RotateTransform(-rotation);
            where.TranslateTransform(-position.X * MainForm.SCALE, -position.Y * MainForm.SCALE);

            //where.ScaleTransform(1, -1);
        }
        public override string ToString()
        {
            return dynamicObject.filename + " " + position.ToString() + ", " + rotation + "°";
        }
    }
}
