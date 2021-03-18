#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void cpu_waster(int ktory)
{
  //  cout << ktory<<"\n";
    for (int i = 0; i < 1000; i++) {
        cout << i << "\n";
    }
}



int main()
{
    // I have 8 logical processors 
    unsigned int n = std::thread::hardware_concurrency();
 //   cout << n << " concurrent threads are supported.\n";
 
   
    thread  *threadMy;
    threadMy = new thread[n];

    for (int i = 0; i < n; i++) {
        threadMy[i] = thread(cpu_waster,i);

    }
    for (int i = 0; i < n; i++)
    {
        threadMy[i].join();
    }
   



    return 0;
}



