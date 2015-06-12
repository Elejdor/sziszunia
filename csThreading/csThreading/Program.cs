using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using System.Threading;

namespace csThreading
{
    class Program
    {
        Stopwatch stopwatch = new Stopwatch();

        void Run()
        {
            CullingSystem culling = new CullingSystem();
            culling.PropagateTestData();

            for (int i = 0; i < 100; i++) //stabilize
            {
                
            }

            stopwatch.Start();
            for (int i = 0; i < 100; i++)
            {
                //culling.CalculateVisibility();
                culling.CheckIntersection(0, 999);
            }

            stopwatch.Stop();
            DisplayResult();
            stopwatch.Reset();

            stopwatch.Start();
            for (int i = 0; i < 100; i++)
            {
                culling.CalculateVisibility();
                //culling.CheckIntersection(0, 999);
            }

            stopwatch.Stop();
            DisplayResult();
            stopwatch.Reset();


        }
                

        void DisplayResult()
        {
            Console.WriteLine((double)stopwatch.Elapsed.TotalMilliseconds/100);
        }

        static void Main(string[] args)
        {
            Program prog = new Program();
            prog.Run();
            Console.ReadKey();
        }
    }
}
