#include <iostream>
#include <string>
#include <memory>

// 抽象组件：咖啡接口
class Coffee {
public:
    virtual std::string getDescription() const = 0;
    virtual double cost() const = 0;
    virtual ~Coffee() {}
};

// 具体组件：原味咖啡
class SimpleCoffee : public Coffee {
public:
    std::string getDescription() const override {
        return "Simple Coffee";
    }

    double cost() const override {
        return 2.0;
    }
};

// 抽象装饰器类：继承 Coffee
class CoffeeDecorator : public Coffee {
protected:
    std::shared_ptr<Coffee> coffee;
public:
    CoffeeDecorator(std::shared_ptr<Coffee> c) : coffee(c) {}
};

// 具体装饰器：牛奶
class MilkDecorator : public CoffeeDecorator {
public:
    MilkDecorator(std::shared_ptr<Coffee> c) : CoffeeDecorator(c) {}

    std::string getDescription() const override {
        return coffee->getDescription() + ", Milk";
    }

    double cost() const override {
        return coffee->cost() + 0.5;
    }
};

// 具体装饰器：糖
class SugarDecorator : public CoffeeDecorator {
public:
    SugarDecorator(std::shared_ptr<Coffee> c) : CoffeeDecorator(c) {}

    std::string getDescription() const override {
        return coffee->getDescription() + ", Sugar";
    }

    double cost() const override {
        return coffee->cost() + 0.3;
    }
};

// 主函数测试
int main() {
    // 原味咖啡
    std::shared_ptr<Coffee> myCoffee = std::make_shared<SimpleCoffee>();
    std::cout << myCoffee->getDescription() << " : $" << myCoffee->cost() << "\n";

    // 加牛奶
    myCoffee = std::make_shared<MilkDecorator>(myCoffee);
    std::cout << myCoffee->getDescription() << " : $" << myCoffee->cost() << "\n";

    // 加糖
    myCoffee = std::make_shared<SugarDecorator>(myCoffee);
    std::cout << myCoffee->getDescription() << " : $" << myCoffee->cost() << "\n";

    return 0;
}

// 输出结果：
// Simple Coffee : $2
// Simple Coffee, Milk : $2.5
// Simple Coffee, Milk, Sugar : $2.8

