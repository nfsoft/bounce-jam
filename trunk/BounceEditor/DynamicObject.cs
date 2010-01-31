using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.IO;

namespace BounceEditor
{
    public class DynamicObject
    {
        public PointF size;
        public string filename;
        public Image image;

        public DynamicObject(string filename)
        {
            this.filename = filename;

            StreamReader file = new StreamReader(filename);

            while (!file.EndOfStream)
            {
                string what = file.ReadLine();

                if (what.StartsWith("size "))
                {
                    string[] split = what.Split(' ');
                    size.X = Convert.ToSingle(split[1]);
                    size.Y = Convert.ToSingle(split[2]);
                } else if (what.StartsWith("texture "))
                {
                    string[] split = what.Split(' ');
                    image = Image.FromFile(split[1]);
                    image.RotateFlip(RotateFlipType.RotateNoneFlipY);
                }
            }

            file.Close();
        }
    }
}
