using System;
using System.Windows.Forms;

namespace LAB4
{
    public partial class Form1 : Form
    {
        public string[] intrebari = {"Care este prima litera din alfabet?",
                "Citi ani are Chisinaul?","Ziua Independentei este? ", "Cite continente sunt?","" +
                "Care este capitala SUA?" };
        public string[,] variante = { {"A","B", "C" }, {"10","578", "20" }, {"10 aprilie ","1 august","27 august" },
                                      {"1","6","7" }, {"Washington","New York","Los Angeles" } };

        public static int[,] answers = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } };
        // 
        public static double [] arr_quick = new double[6];
        public static int quick = 60;
        public int i = 0, j = 0, score = 0,time_local=0;
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            timer1 = new System.Windows.Forms.Timer();
            timer1.Interval = 1000; // 1 secunda interval
            timer1.Tick += new EventHandler(timer1_Tick);
            timer1.Enabled = true;

            label1.Text = intrebari[i];
            if (radioButton1.Checked == true)
            {
                radioButton1.Checked = false;
            }

            radioButton1.Text = variante[0, 0];
            radioButton2.Text = variante[0, 1];
            radioButton3.Text = variante[0, 2];
            button1.Enabled = false;
            button2.Visible = false;
            button3.Visible = false;
            label3.Visible = false;

        }

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox1.Checked == true)
            {
                button1.Enabled = true;
            }
            else
            {
                button1.Enabled = false;
            }
        }

        private void radioButton2_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void radioButton3_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void label3_Click(object sender, EventArgs e)
        {
            
        }

        private void button3_Click(object sender, EventArgs e)
        {
            Form2 form = new Form2();
            form.Show();
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }
        
        private void timer1_Tick(object sender, EventArgs e)
        {
            if (quick == 0)
            {
                quick = 0;
            }
            quick--;
            label2.Text ="TIME : 00:" + quick.ToString();
            
        }

        private void button2_Click(object sender, EventArgs e)
        {
            using (System.IO.StreamWriter file = new System.IO.StreamWriter(@"C:\Users\Daniil Lasco\Desktop\PPE\out.txt"))
            {
                file.Write("======================");
                file.WriteLine();
                for (int i = 0; i < 5; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        file.Write(answers[i, j]);
                    }
                    file.WriteLine();
                }
                file.Write(i);
            }
            score = answers[0, 0] + answers[1, 1] + answers[2, 2] + answers[3, 2] + answers[4, 0];
            label1.Text = "SCORE : " + score.ToString() + "/5";
            label3.Visible = true;
            label3.Text = "TIME : 00:" + (60 - time_local).ToString();
            
        }
        

        private void button1_Click(object sender, EventArgs e)
        {

            if (quick == 0 || i > 3)
            {
                i++;
                radioButton1.Visible = false;
                radioButton2.Visible = false;
                radioButton3.Visible = false;
                checkBox1.Visible = false;
                button1.Visible = false;
                button2.Visible = true;
                label1.Text = " ";
                label2.Visible = false;
                time_local = quick;
                button3.Visible = true;

            }
            else
            {
                i++;
                label1.Text = intrebari[i];
                radioButton1.Text = variante[i, 0];
                radioButton2.Text = variante[i, 1];
                radioButton3.Text = variante[i, 2];

            }

            
            if (checkBox1.Checked == true)
            {
                checkBox1.Checked = false;
            }
            
            if(radioButton1.Checked == true)
            {
                if ((i-1) == 0) { 
                    answers[i-1, i-1] = 1;
                    arr_quick[1] =quick ;
                }
                if ((i - 1) == 4)
                {
                    answers[4, 0] = 1;
                    arr_quick[5] = quick;
                }
                
                radioButton1.Checked = false;
            }

            if (radioButton2.Checked == true)
            {
                if ((i - 1) == 1)
                {
                    answers[i - 1, i - 1] = 1;
                    arr_quick[2] = quick;
                }
                    
                radioButton2.Checked = false;
                
            }

            if (radioButton3.Checked == true)
            {
                if ((i - 1) == 2) {
                    answers[i - 1, i - 1] = 1;
                    arr_quick[3] = quick;
                }
                if ((i - 1) == 3)
                {
                    answers[3, 2] = 1;
                    arr_quick[4] = quick;
                }
                
                radioButton3.Checked = false;
            }
            
        }
    }
}
