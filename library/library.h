#include <mutex>

using namespace std;

struct CriticalData
{
    mutex mut;
};

void deadLock(CriticalData& a, CriticalData& b);