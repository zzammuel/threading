#include <thread>
#include <iostream>
#include <barrier>
#include <vector>

#include "library/library.h"

using namespace std;

int main(int argc, char *argv[]){
    cout << "Number of arguments pass: " << argc << endl << endl;

    if (argc!=4){ return 0; }

    const int NX = atoi(argv[1]);
    const int NT = atoi(argv[2]);
    const int nthreads = atoi(argv[3]);

    cout << NX << ", " << NT << ", " << nthreads << endl;

    BurgersEquation Beq = BurgersEquation(0.03, NX, NT);
    barrier sync_point(nthreads);
    auto glambda = [&](auto lb, auto rb){Beq.getSolution(lb, rb, sync_point);};

    vector<thread> threads;

    int lb, rb;
    for(int i=0; i<nthreads; i++){
        lb = NX / nthreads * i + 1;
        rb = NX / nthreads * (i + 1) + 1;
        
        threads.emplace_back(glambda, lb, rb);
    }

    for(auto& t : threads){
        t.join();
    }

    Beq.saveResults();
}