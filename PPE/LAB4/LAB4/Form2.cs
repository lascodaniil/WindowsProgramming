using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace LAB4
{
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();
            for(int i = 1; i <=5; i++)
            {
                if(Form1.arr_quick[i] == 0)
                {
                    Form1.arr_quick[i] = 1;
                }
            }




            this.chart1.Series["Rezultate"].Points.AddXY(1,Form1.arr_quick[1]);
            this.chart1.Series["Prognoze"].Points.AddXY(1, 55);

            this.chart1.Series["Rezultate"].Points.AddXY(2, Form1.arr_quick[2]);
            this.chart1.Series["Prognoze"].Points.AddXY(2, 45);

            this.chart1.Series["Rezultate"].Points.AddXY(3, Form1.arr_quick[3]);
            this.chart1.Series["Prognoze"].Points.AddXY(3,  40);

            this.chart1.Series["Rezultate"].Points.AddXY(4, Form1.arr_quick[4]);
            this.chart1.Series["Prognoze"].Points.AddXY(4, 35);

            this.chart1.Series["Rezultate"].Points.AddXY(5, Form1.arr_quick[5]);
            this.chart1.Series["Prognoze"].Points.AddXY(5,30);


            chart1.Show();
        }

        private void chart1_Click(object sender, EventArgs e)
        {
            
        }

        private void label1_Click(object sender, EventArgs e)
        {
            label1.Text = "t, s";
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }
    }
}
