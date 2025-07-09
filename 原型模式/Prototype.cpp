#include <iostream>
#include <string>
#include <memory>

// ===== 抽象原型类 =====
class Prototype {
public:
    virtual std::shared_ptr<Prototype> clone() const = 0;
    virtual void print() const = 0;
    virtual ~Prototype() {}
};

// ===== 具体原型类 A =====
class ConcreteA : public Prototype {
private:
    int data_;
public:
    ConcreteA(int data) : data_(data) {}

    // 拷贝构造 + clone 方法
    std::shared_ptr<Prototype> clone() const override {
        return std::make_shared<ConcreteA>(*this);  // 深拷贝
    }

    void print() const override {
        std::cout << "ConcreteA with data = " << data_ << "\n";
    }
};

// ===== 具体原型类 B =====
class ConcreteB : public Prototype {
private:
    std::string name_;
public:
    ConcreteB(const std::string& name) : name_(name) {}

    std::shared_ptr<Prototype> clone() const override {
        return std::make_shared<ConcreteB>(*this);
    }

    void print() const override {
        std::cout << "ConcreteB with name = " << name_ << "\n";
    }
};

// ===== 客户端测试代码 =====
int main() {
    // 创建原型对象
    std::shared_ptr<Prototype> a = std::make_shared<ConcreteA>(42);
    std::shared_ptr<Prototype> b = std::make_shared<ConcreteB>("Hello");

    // 复制对象（无需知道实际类型）
    std::shared_ptr<Prototype> a_clone = a->clone();
    std::shared_ptr<Prototype> b_clone = b->clone();

    std::cout << "Original objects:\n";
    a->print();
    b->print();

    std::cout << "Cloned objects:\n";
    a_clone->print();
    b_clone->print();

    return 0;
}

// 输出结果

// Original objects:
// ConcreteA with data = 42
// ConcreteB with name = Hello
// Cloned objects:
// ConcreteA with data = 42
// ConcreteB with name = Hello

/*
定义： 原型模式 是一种创建型模式，允许你通过复制已有对象来创建新对象，而不是通过 new 关键字直接实例化。
常用于对象创建成本高或需要运行时决定类型的场景
*/