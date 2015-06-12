using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Xna.Framework;
using System.Threading;

namespace csThreading
{
    class CullingSystem
    {
        
        List<List<BoundingBox>> boundingBoxes;

        List<BoundingBox> cullingAreas;

        public ManualResetEvent event1 = new ManualResetEvent(false);
        public bool Cancel = false;
        public int finnished = 0;

        Thread[] threads;
        BoundingFrustum frustum;



        struct Synchronization
        {
            public CountdownEvent finnished;
            public CountdownEvent ready;
            public ManualResetEvent startCulling;
            public ManualResetEvent safeToLeave;

        }

        Int64 tests = 0;

        Synchronization sync = new Synchronization();

        public void PropagateTestData()
        {
            
            int noThreads = 8;
            int noBounding = 10000;

            mins = new int[noThreads];
            maxes = new int[noThreads];

            int perThread = CalcMinMax(noThreads, noBounding);
            int boundingsRemaining = noBounding;

            boundingBoxes = new List<List<BoundingBox>>();
            cullingAreas = new List<BoundingBox>();

            sync.finnished = new CountdownEvent(noThreads);
            sync.ready = new CountdownEvent(noThreads);
            sync.startCulling = new ManualResetEvent(false);
            sync.safeToLeave = new ManualResetEvent(false);
            
            for (int t = 0; t < noThreads; t++)
            {
                boundingBoxes.Add(new List<BoundingBox>());
                boundingsRemaining -= perThread;
                for (int i = 0; i < perThread; i++)
                {
                    boundingBoxes[t].Add(new BoundingBox(new Vector3(0, 0, 0), new Vector3(1, 1, 1)));
                }
            }

            for (int i = 0; i < boundingsRemaining; i++)
            {
                --boundingsRemaining;
                boundingBoxes[noThreads - 1].Add(new BoundingBox(new Vector3(0, 0, 0), new Vector3(1, 1, 1)));
            }

            for (int i = 0; i < 100; i++)
            {
                cullingAreas.Add(new BoundingBox(new Vector3(0, 0, 0), new Vector3(1, 1, 1)));
            }
            
            threads = new Thread[noThreads];
                        
            for (int i = 0; i < noThreads; i++)
            {
                int j = i;
                threads[i] = new Thread(() => CheckIntersectionAsync(mins[j], maxes[j], j));

            }
            //threads[0] = new Thread(() => CheckIntersectionAsync(mins[0], maxes[0], 0));
            //threads[1] = new Thread(() => CheckIntersectionAsync(mins[1], maxes[1], 1));
            //threads[2] = new Thread(() => CheckIntersectionAsync(mins[2], maxes[2], 2));
            //threads[3] = new Thread(() => CheckIntersectionAsync(mins[3], maxes[3], 3));
            //threads[4] = new Thread(() => CheckIntersectionAsync(mins[4], maxes[4], 4));
            //threads[5] = new Thread(() => CheckIntersectionAsync(mins[5], maxes[5], 5));
            //threads[6] = new Thread(() => CheckIntersectionAsync(mins[6], maxes[6], 6));
            //threads[7] = new Thread(() => CheckIntersectionAsync(mins[7], maxes[7], 7));
            
            for (int i = 0; i < noThreads; i++)
            {
                threads[i].Start();
            }
        }

        int[] maxes;
        int[] mins;

        int CalcMinMax(int chunks, int n)
        {
            int perChunk = (n - (n % chunks)) / chunks;
            for (int i = 0; i < chunks; i++)
            {
                maxes[i] = perChunk + i * perChunk - 1;
                mins[i] = i * perChunk;
                n -= perChunk;
            }

            if (n != 0)
                maxes[chunks - 1] += n;

            return perChunk;
        }

        void CalcMin(int chunk)
        {

        }

        public void CalculateVisibility()
        {
            sync.safeToLeave.Reset();
            sync.startCulling.Set();
            sync.finnished.Wait();
            sync.finnished.Reset();
            sync.startCulling.Reset();
            sync.safeToLeave.Set();
        }

        public void CheckIntersectionAsync(int startIndex, int endIndex, int thread)
        {
            while (!Cancel)
            {
                sync.startCulling.WaitOne();
                int localTests = 0;
                foreach (BoundingBox occluder in boundingBoxes[thread])
	            {
		            foreach (BoundingBox item in cullingAreas)
                    {
                        item.Intersects(occluder);
                        ++localTests;
                    }
	            }
                
                tests += localTests;
                sync.finnished.Signal();
                sync.safeToLeave.WaitOne();
            }

        }

        public void CheckIntersection(int startIndex, int endIndex)
        {
            foreach (List<BoundingBox> occlusionList in boundingBoxes)
            {
                foreach (BoundingBox occluder in occlusionList)
                {
                    foreach (BoundingBox item in cullingAreas)
                    {
                        item.Intersects(occluder);
                    }
                }
            }
            
        }
    }
}
