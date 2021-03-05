using System;
using System.Timers;

namespace _OS_Sandbox {
    class Program {

        Timer Timer = new Timer(3000f);

        static void Main() {
            Program Obj = new Program();
            Obj.Start();
            Console.ReadKey();
        }

        void Start() {
            this.Timer.Start();
            this.Timer.Elapsed += Timer_Elapsed;
        }

        private void Timer_Elapsed(object sender, ElapsedEventArgs e) {
            Console.WriteLine("LOL");
        }

    }
}
