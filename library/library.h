#include <mutex>
#include <vector>

using namespace std;


// deadlock_example.cpp
struct CriticalData
{
    mutex mut;
};

void deadLock(CriticalData& a, CriticalData& b);

// rungekutta.cpp
class BurgersEquation{
    public:
        BurgersEquation(float nu, int nx, int nt, int nthread);

        void nextTimeStep(int n, int lb, int rb);

        void getSolution(int threadnumber, int lb, int rb);
        void printTimePoint(int t);

    private:
        int TCOUNT, XCOUNT, THREADCOUNT;
        vector<bool> THREADSTATUS;
        bool allDone();

        vector<vector<double>> grid;
        double nu, dt, dx;
};