#include <mutex>
#include <vector>

using namespace std;

// deadlock_example.cpp
struct CriticalData
{
    mutex mut;
};

void deadLock(CriticalData& a, CriticalData& b);

// burgers_equation.cpp
class BurgersEquation{
    public:
        BurgersEquation(float nu, int nx, int nt);

        void nextTimeStep(int n, int lb, int rb);

        void getSolution(int lb, int rb, barrier<> &syncpoint);
        void saveResults();

    private:
        int TCOUNT, XCOUNT, THREADCOUNT;

        vector<vector<double>> grid;
        double nu, dt, dx;
};