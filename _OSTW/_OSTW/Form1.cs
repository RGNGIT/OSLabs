using System;
using System.Threading;
using System.Windows.Forms;

namespace _OSTW {
    public partial class Form1 : Form {

        struct ThreadInfo {
            public int Times;
            public int InfoTimes;
            public int Time;
            public bool Ready;
            public bool Done;
            public bool Exec;
        }

        ThreadInfo[] TI = new ThreadInfo[5];

        public Form1() {

            InitializeComponent();

        }

        bool TDone() {
            int bSum = 0;
            for(int i = 0; i < 5; i++) {
                bSum += Convert.ToInt32(TI[i].Done);
            }
            if(bSum == 5) {
                return true;
            } else{
                return false;
            }
        }

        void BarParameterizer(int CurrentThread) {
            progressBar.Maximum = TI[CurrentThread].InfoTimes;
            progressBar.Value = TI[CurrentThread].InfoTimes - TI[CurrentThread].Times;
            per.Text = Convert.ToString(Math.Round(((float)TI[CurrentThread].InfoTimes - (float)TI[CurrentThread].Times) / (float)TI[CurrentThread].InfoTimes * 100)) + "%";
        }

        void Task(object obj) {
            if(!TI[(int)obj].Done) {
                TI[(int)obj].Times--;
                TI[(int)obj].Exec = true;
                TI[(int)obj].Time += 2000;
                if (TI[(int)obj].Times <= 0) {
                    TI[(int)obj].Done = true;
                    TI[(int)obj].Exec = false;
                    TI[(int)obj].Ready = false;
                }
                Thread.Sleep(2000);
            }
            return;
        }

        private void Start_Click(object sender, EventArgs e) {

            Start.Text = "В процессе...";

            for(int i = 0; i < 5; i++) {
                TI[i].Done = false; TI[i].Exec = false; TI[i].Ready = true;
                TI[i].Time = 0;
                TI[i].Times = Convert.ToInt32(Controls["textBox" + (6 + i)].Text); TI[i].InfoTimes = TI[i].Times;
                Controls["textBox" + (i + 1)].Text = "Готов";
            }

            while (true) {
                for(int i = 0; i < 5; i++) {
                    Thread Thread = new Thread(new ParameterizedThreadStart(Task));
                    Thread.Start(i); Thread.Join(); BarParameterizer(i);
                    for (int j = 4; j >= 0; j--) {
                        if (TI[j].Ready) { Controls["textBox" + (j + 1)].Text = "Готов"; }
                    }
                    if (TI[i].Exec) { Controls["textBox" + (i + 1)].Text = "Выполняется"; }
                    if (TI[i].Done) { Controls["textBox" + (i + 1)].Text = $"Завершен. Проходов: {TI[i].InfoTimes} Время: {TI[i].Time}ms"; }
                }
                if(TDone()) {
                    Start.Text = "Работа завершена!";
                    break; 
                }
            }
        }
    }
}
