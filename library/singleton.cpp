#include <iostream>
#include <mutex>

using namespace std;

class Singleton{
    private:
        static once_flag initInstaneFlag;
        static Singleton* instance;
        Singleton() = default;
        ~Singleton() = default;

        static void initSingleton(){
            instance = new Singleton();
        }

    public:
        Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton&) = delete;

        static Singleton* getInstance(){
            call_once(initInstaneFlag, Singleton::initSingleton);
            return instance;
        }
};