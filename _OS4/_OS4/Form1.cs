using System;
using System.IO;
using System.Diagnostics;
using System.Windows.Forms;

namespace _OS4 {

    public partial class Form1 : Form {

        long[,] Pool = new long[25, 2];
        string[] ToFile = new string[40];
        int Timer = 21, Iter = 0;

        public Form1() {
            InitializeComponent();
            dataGridView0.Columns.Add("num", "Номер"); dataGridView1.Columns.Add("num", "Номер");
            dataGridView0.Columns.Add("range", "Диапазон"); dataGridView1.Columns.Add("range", "Диапазон");
            dataGridView0.Columns.Add("address", "Индекс страницы"); dataGridView1.Columns.Add("address", "Индекс страницы");
            dataGridView2.Columns.Add("loginfo", "Лог");
            for (int i = 0; i < 24; i++) {
                Pool[i, 0] = 0x0 + i * 65535 + i;
                Pool[i, 1] = 0x0 + 65535 * (i + 1);
                dataGridView0.Rows.Add(i, $"{Pool[i, 0].ToString("X")}-{Pool[i, 1].ToString("X")}", null);
                if (i < 16) {
                    dataGridView1.Rows.Add(i, $"{Pool[i, 0].ToString("X")}-{Pool[i, 1].ToString("X")}", null);
                }
            }
            MemoryCalc(0x0, 0x0); TimeDec();
        }

        void MemoryCalc(long Pick1, long Pick2) {
            long Mem1 = 0, Mem2 = 0;
            for (int i = 0; i < 24; i++) {
                if(dataGridView0[2, i].Value == null) {
                    Mem1 += 0xFFFF;
                }
                if (i < 16) {
                    if (dataGridView1[2, i].Value == null) {
                        Mem2 += 0xFFFF;
                    }
                }
            }
            label1.Text = $"Физ. память: {Mem1}bytes. Ячейка в процессе: 0x{Pick1.ToString("X")}";
            label2.Text = $"Вирт. память: {Mem2}bytes. Ячейка в процессе: 0x{Pick2.ToString("X")}";
        }

        void FileForm() {
            File.WriteAllLines("_OS4LOG.txt", ToFile);
            Process.Start("_OS4LOG.txt"); timer1.Stop();
        }

        void Log(long[] Data) {
            ToFile[Iter] = $"Страничка {Data[2]} (Адрес: 0x{Data[0]}) перемещена в {Data[3]} (Адрес: 0x{Data[1]})";
            dataGridView2.Rows.Add(ToFile[Iter]);
        }

        void TimeDec() {
            Timer--;
            label3.Text = $"Оставшееся время симуляции: {Timer}c";
        }

        private void button1_Click(object sender, EventArgs e) {
            timer1.Start();
        }

        private void timer1_Tick(object sender, EventArgs e) {
            if (Timer > 0) {
                Random Rnd = new Random();
                long Pick1 = Rnd.Next(0x0, 0x17FFE8);
                long Pick2 = Rnd.Next(0x0, 0xFFFF0);
                int PickedLine1 = -1, PickedLine2 = -1;
                MemoryCalc(Pick1, Pick2);
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 24; j++) {
                        dataGridView0[i, j].Selected = false;
                        if (j < 16) {
                            dataGridView1[i, j].Selected = false;
                        }
                    }
                }
                for (int i = 0; i < 24; i++) {
                    if (Pick1 > Pool[i, 0] && Pick1 < Pool[i, 1]) {
                        PickedLine1 = i;
                    } if (i < 16) {
                        if (Pick2 > Pool[i, 0] && Pick2 < Pool[i, 1]) {
                            PickedLine2 = i;
                        }
                    }
                }
                for (int i = 0; i < 3; i++) {
                    dataGridView0[i, PickedLine1].Selected = true;
                    dataGridView1[i, PickedLine2].Selected = true;
                }
                dataGridView0[2, PickedLine1].Value = dataGridView1[0, PickedLine2].Value.ToString();
                dataGridView1[2, PickedLine2].Value = dataGridView0[0, PickedLine1].Value.ToString();
                long[] Data = { Pick1, Pick2, PickedLine1, PickedLine2 }; Log(Data); Iter++; TimeDec();
            } else {
                FileForm(); 
            }
        }

    }
}
