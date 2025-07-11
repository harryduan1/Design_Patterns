#include <iostream>
#include <mutex>

// 单例类
class Singleton {
private:
    // 私有构造函数，防止外部实例化
    Singleton() {
        std::cout << "Singleton Constructor Called\n";
    }

    // 禁用拷贝构造和赋值
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    // 获取单例实例的静态方法
    static Singleton& getInstance() {
        static Singleton instance;  // C++11 起线程安全
        return instance;
    }

    // 示例方法
    void doSomething() {
        std::cout << "Doing something in Singleton.\n";
    }
};

// 客户端代码测试
int main() {
    Singleton& s1 = Singleton::getInstance();
    s1.doSomething();

    Singleton& s2 = Singleton::getInstance();
    s2.doSomething();

    // 比较地址，验证是否是同一实例
    std::cout << "Address of s1: " << &s1 << "\n";
    std::cout << "Address of s2: " << &s2 << "\n";

    return 0;
}

// 输出结果
/*
Singleton Constructor Called
Doing something in Singleton.
Doing something in Singleton.
Address of s1: 0x5644f2d2f010
Address of s2: 0x5644f2d2f010
*/