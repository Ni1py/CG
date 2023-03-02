using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Draftsman
{
    public partial class Draftsman : Form
    {
        public Draftsman()
        {
            InitializeComponent();
            SetSize();
        }

        private void Draftsman_Load(object sender, EventArgs e)
        {

        }

        private class ArrayPoints
        {
            private int index = 0;
            private Point[] points;

            public ArrayPoints(int size)
            {
                if (size <= 0)
                {
                    size = 2;
                }

                points = new Point[size];
            }

            public void SetPoint(int x, int y)
            {
                if (index >= points.Length)
                {
                    index = 0;
                }

                points[index] = new Point(x, y);
                index++;
            }

            public void ResetPoints()
            {
                index = 0;
            }

            public int GetCountPoints()
            {
                return index;
            }

            public Point[] GetPoints()
            {
                return points;
            }
        }

        private bool isMouseClamped = false;
        private ArrayPoints arrayPoints = new ArrayPoints(2);

        Bitmap map = new Bitmap(100, 100);
        Graphics graphics;

        private void SetSize()
        {
            Rectangle rectangle = Screen.PrimaryScreen.Bounds;
            map = new Bitmap(rectangle.Width, rectangle.Height);
            graphics = Graphics.FromImage(map);

            pen.StartCap = System.Drawing.Drawing2D.LineCap.Round;
            pen.EndCap = System.Drawing.Drawing2D.LineCap.Round;
        }

        Pen pen = new Pen(Color.Black, 3f);

        private void canvas_MouseDown(object sender, MouseEventArgs e)
        {
            isMouseClamped = true;
        }

        private void canvas_MouseUp(object sender, MouseEventArgs e)
        {
            isMouseClamped = false;
            arrayPoints.ResetPoints();
        }

        private void canvas_MouseMove(object sender, MouseEventArgs e)
        {
            if (!isMouseClamped)
            {
                return;
            }

            arrayPoints.SetPoint(e.X, e.Y);
            if (arrayPoints.GetCountPoints() >= 2)
            {
                graphics.DrawLines(pen, arrayPoints.GetPoints());
                canvas.Image = map;
                arrayPoints.SetPoint(e.X, e.Y);
            }
        }

        private void buttonColor_Click(object sender, EventArgs e)
        {
            if (colorDialog.ShowDialog() == DialogResult.OK)
            {
                pen.Color = colorDialog.Color;
                ((Button)sender).BackColor = colorDialog.Color;
            }
        }

        private void buttonClear_Click(object sender, EventArgs e)
        {
            graphics.Clear(canvas.BackColor);
            canvas.Image = map;
        }

        private void sizeBar_ValueChanged(object sender, EventArgs e)
        {
            pen.Width = sizeBar.Value;
        }

        private void buttonSave_Click(object sender, EventArgs e)
        {
            saveFileDialog.Filter = "JPEG(*.JPEG)|*.jpeg";

            if (saveFileDialog.ShowDialog() == DialogResult.OK)
            {
                if (canvas.Image != null)
                {
                    canvas.Image.Save(saveFileDialog.FileName);
                }
            }
        }

        private void buttonOpen_Click(object sender, EventArgs e)
        {
            openFileDialog.InitialDirectory = "C:\\";
            openFileDialog.Filter = "JPEG(*.JPEG)|*.jpeg";

            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                canvas.Image = Image.FromFile(openFileDialog.FileName);
                graphics.DrawImage(canvas.Image, new Point(0, 0));
            }
        }
    }
}
