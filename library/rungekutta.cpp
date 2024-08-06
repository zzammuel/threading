/*
du/dt + u * du/dx = eps d2u/dx2
u(x,0)  = sin(x)    0<x<pi
u(0,t)  = 0         0<t
u(pi,t) = 0         0<t

finite difference method:
(u(j, n+1)-u(j,n))/dt + u(j,n) * (u(j,n)-u(j-1,n))/dx = eps*(u(j+1,n)-2u(j,n)+u(j-1,n))/(dx)**2

u(n+1,j) = dt/dx * u(n,j-1)*u(n,j)
            - u(n,j)**2
            + (1 - 2*eps*dt/(dx)**2)*u(n,j)
            + eps*dt/(dx)**2 * u(n,j+1)
            + eps*dt/(dx)**2 * u(n,j-1)
*/

#include <vector>
#include <cmath>
#include <iostream>
#include <condition_variable>
#include <fstream>
#include <numbers>
#include <barrier>

#include "library.h"

using namespace std;

condition_variable condVar;
mutex writeMutex, coutMutex;

BurgersEquation::BurgersEquation(float nu, int nx, int nt){
    nu = nu;
    XCOUNT = nx;
    TCOUNT = nt;

    for (int t=0; t<TCOUNT+1;t++){
        grid.push_back(vector<double>(XCOUNT+2, 0.0));
    }

    dt = 1.0 / (double) TCOUNT;
    dx = numbers::pi / (double) (XCOUNT+1);

    for (int j=1; j<XCOUNT+1; j++){
        grid[0][j] = sin(dx * j);
    }
};

void BurgersEquation::nextTimeStep(int n, int lb, int rb){
    double newval;
    for (int j=lb; j<rb; j++){
        newval = dt/dx * grid[n][j-1] * grid[n][j] 
                        - pow(grid[n][j],2)
                        + (1 - 2*nu*dt/pow(dx,2)) * grid[n][j]
                        + nu * dt/pow(dx,2) * grid[n][j+1]
                        + nu * dt/pow(dx,2) * grid[n][j-1];

        {
            lock_guard<mutex> lck(writeMutex);
            grid[n+1][j] = newval;
        }
    }
}

void BurgersEquation::getSolution(int lb, int rb, barrier<> &syncpoint){
    for (int t=0; t<TCOUNT; t++){
        nextTimeStep(t, lb, rb);

        {
            lock_guard<mutex> lck(coutMutex);
            cout << "(" << lb << ", " << rb << ")" << endl;
        }

        syncpoint.arrive_and_wait();
    }
}

void BurgersEquation::saveResults(){
    fstream fs;
    fs.open("output/Solution.csv", fstream::out);

    double t = 0;

    for (auto row : grid){
        fs << t;
        t += dt;
        for (auto col : row){
            fs << "," << col;
        }
        fs << endl;
    }
    fs.close();
}
