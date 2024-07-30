#include <thread>
#include <iostream>

#include "library/library.h"

using namespace std;

int main(){
    cout << thread::hardware_concurrency() << endl << endl;

    CriticalData c1, c2;

    thread t1([&]{deadLock(c1, c2);});
    thread t2([&]{deadLock(c2, c1);});

    t1.join();
    t2.join();

    cout << endl;
}