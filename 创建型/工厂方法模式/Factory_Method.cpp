#include <iostream>
#include <memory>

// ===== 抽象产品 =====
class Shape {
public:
    virtual void draw() = 0;
    virtual ~Shape() {}
};

// ===== 具体产品 =====
class Circle : public Shape {
public:
    void draw() override {
        std::cout << "Drawing Circle\n";
    }
};

class Square : public Shape {
public:
    void draw() override {
        std::cout << "Drawing Square\n";
    }
};

// ===== 工厂接口 =====
class ShapeFactory {
public:
    virtual std::shared_ptr<Shape> createShape() = 0;
    virtual ~ShapeFactory() {}
};

// ===== 具体工厂：CircleFactory =====
class CircleFactory : public ShapeFactory {
public:
    std::shared_ptr<Shape> createShape() override {
        return std::make_shared<Circle>();
    }
};

// ===== 具体工厂：SquareFactory =====
class SquareFactory : public ShapeFactory {
public:
    std::shared_ptr<Shape> createShape() override {
        return std::make_shared<Square>();
    }
};

// ===== 客户端代码 =====
int main() {
    std::unique_ptr<ShapeFactory> factory;

    // 使用 Circle 工厂
    factory = std::make_unique<CircleFactory>();
    std::shared_ptr<Shape> shape1 = factory->createShape();
    shape1->draw();

    // 使用 Square 工厂
    factory = std::make_unique<SquareFactory>();
    std::shared_ptr<Shape> shape2 = factory->createShape();
    shape2->draw();

    return 0;
}

// 输出结果
// Drawing Circle
// Drawing Square


// 定义： 工厂方法模式通过将对象的创建委托给子类，使得代码遵循开闭原则（Open-Closed Principle），每增加一个产品，只需增加一个工厂类。
