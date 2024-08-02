#include <thread>
#include <iostream>

#include "library/library.h"

using namespace std;

int main(){
    cout << thread::hardware_concurrency() << endl << endl;

    BurgersEquation Beq = BurgersEquation(0.03, 19, 10, 2);

    thread t1([&]{Beq.getSolution(0, 1, 10);});
    thread t2([&]{Beq.getSolution(1, 10, 19);});

    t1.join();
    t2.join();

    Beq.printTimePoint(10);
}