/**
 * @file Singleton_ThreadSafe.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <iostream>
#include <memory>
#include <thread>
#include <mutex>

class Singleton
{
    private:
        static Singleton* pInstance_;
        static std::mutex mutex_;
    
    protected:
        Singleton(const std::string value) : value_(value) {}
        ~Singleton() {}
        std::string value_;
    
    public:
        Singleton(Singleton &other) = delete;
        void operator=(const Singleton &) = delete;
        static Singleton* getInstance(const std::string& value);
        void yourFunctionality()
        {
            std::cout << "Insert functionality here";
        }
        std::string getValue() const
        {
            return value_;
        }
};

Singleton* Singleton::pInstance_{nullptr};
std::mutex Singleton::mutex_;

Singleton*  Singleton::getInstance(const std::string& value)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if(pInstance_ == nullptr)
    {
        pInstance_ = new Singleton(value);
    }
    return pInstance_;
}

void thread1()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    auto singleton = Singleton::getInstance("THREAD_1");
    std::cout << singleton->getValue() << std::endl;
}

void thread2()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    auto singleton = Singleton::getInstance("Thread2");
    std::cout << singleton->getValue() << std::endl;
}

int main()
{
    std::thread firstThread(thread1);
    std::thread secondThread(thread2);
    firstThread.join();
    secondThread.join();

    return 0;
}