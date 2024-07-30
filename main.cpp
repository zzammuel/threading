#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>
#include <unistd.h>

using namespace std;

struct CriticalData
{
    mutex mut;
};


void deadLock(CriticalData& a, CriticalData& b){
    unique_lock<mutex> guard1(a.mut, defer_lock);
    cout << "Thread: " << this_thread::get_id() << " first mutex" << endl;

    this_thread::sleep_for(chrono::milliseconds(1));

    unique_lock<mutex> guard2(b.mut, defer_lock);
    cout << "Thread: " << this_thread::get_id() << " second mutex" << endl;

    cout << "   Thread: " << this_thread::get_id() << " get both mutex" << endl;
    lock(guard1, guard2);
}

void sleepOneSecond(){
    sleep(1);
}

int main(){
    cout << thread::hardware_concurrency() << endl << endl;

    CriticalData c1, c2;

    auto starttime = chrono::high_resolution_clock::now();

    thread t1(sleepOneSecond);
    thread t2(sleepOneSecond);

    t1.join();
    t2.join();

    auto endtime = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(endtime - starttime);

    cout << duration.count() << endl;
}