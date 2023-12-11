#include <iostream>
#include <memory>
#include <mutex>
#include <vector>
#include <thread>

// Singleton class
class Singleton
{
private:
    // Private constructor to not create instance directly
    Singleton(std::string val):val(val) {}

    std::string val;

    static std::unique_ptr<Singleton> instance;
    static std::mutex mutex_;
public:

    // Delete copy constructor
    Singleton(Singleton const&) = delete;

    // Delete assignment operator
    void operator=(Singleton const&) = delete;

    // Static method to get instance
    static Singleton* getInstance(std::string val)
    {
        std::lock_guard<std::mutex> lock(mutex_);   // Lock mutex for thread safety
        if(instance == nullptr)
        {
            instance = std::unique_ptr<Singleton>(new Singleton(val));
        }
        return instance.get();
    }

    // Set value
    void setValue(std::string val)
    {
        std::lock_guard<std::mutex> lock(mutex_);   // Lock mutex for thread safety
        this->val = val;
    }

    // Get value
    std::string getValue()
    {
        std::lock_guard<std::mutex> lock(mutex_);   // Lock mutex for thread safety
        return this->val;
    }

    ~Singleton() {
        std::cout << "Destructor called" << std::endl;
    
    }

};

// Initialize pointer to zero so that it can be initialized in first call to getInstance
std::unique_ptr<Singleton> Singleton::instance = nullptr;
std::mutex Singleton::mutex_;   // Initialize mutex

int main()
{
    // Get instance
    Singleton* s = Singleton::getInstance("Hello");
    std::cout << s->getValue() << std::endl;        // Hello

    // Get instance again
    Singleton* s2 = Singleton::getInstance("World");
    std::cout << s2->getValue() << std::endl;       // Hello

    // Set value
    s2->setValue("World");
    std::cout << s->getValue() << std::endl;        // World

    std::cout<< s << std::endl;     // Same address
    std::cout<< s2 << std::endl;    // Same address

    //---------------------------------------------

    std::vector<std::thread> threads;

    for(int i=0; i<50; i++)
    {
        threads.push_back(std::thread([&i](){
            Singleton *s = Singleton::getInstance(std::to_string(i));
            std::cout <<"Thread: "<<i<<" val: "<<s->getValue() << std::endl;
            if(i==49)
            {
                s->setValue(std::to_string(i));
            }
        }));
    }

    // when i from 0 to 49 then s.getValue() will be World

    for(auto& thread : threads)
    {
        thread.join();
    }

    std::cout<<s->getValue()<<std::endl;    // 49

    return 0;
}