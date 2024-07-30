#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>

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