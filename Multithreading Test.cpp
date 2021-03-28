//https://www.srcmake.com/home/multithreading

#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

// Just chill. Kill some time.
void KillTime(int loopcount)
{
    while (loopcount > 0)
    {
        loopcount -= 1;
    }
}

// Call KillTime 3 times. (Sequentially.)
void NormalWay(int loopcount)
{
    KillTime(loopcount);
    KillTime(loopcount);
    KillTime(loopcount);
}

// Do KillTime the multithreaded way.
void MultithreadedWay(int loopcount)
{
    // "Execute the function KillTime (and pass it parameter "loopcount") on a thread object that we name t1."
    thread t1(KillTime, loopcount);
    thread t2(KillTime, loopcount);
    thread t3(KillTime, loopcount);

    // "Before our main thread continues running, wait for t1 to finish executing."
    t1.join();
    t2.join();
    t3.join();
}

int main()
{
    cout << "Program started." << endl;
    int loopcount = 1234567890;

    /* FIRST WAY - Just do each KillTime the normal (sequential) way. */
    auto start = chrono::steady_clock::now();
    NormalWay(loopcount);
    auto end = chrono::steady_clock::now();
    cout << "Time for normal way is: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << endl;

    /* MULTITHREADED WAY - call each KillTime on a new thread (so they can run simultaneously).*/
    start = chrono::steady_clock::now();
    MultithreadedWay(loopcount);
    end = chrono::steady_clock::now();
    cout << "Time for multithreaded way is: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << endl;

    cout << "Program ended." << endl;
    return 0;
}