#include <iostream>
#include <memory>
#include <string>

// ===== 抽象产品接口 =====
class Shape {
public:
    virtual void draw() = 0;
    virtual ~Shape() {}
};

// ===== 具体产品类 =====
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

class Rectangle : public Shape {
public:
    void draw() override {
        std::cout << "Drawing Rectangle\n";
    }
};

// ===== 简单工厂类 =====
class ShapeFactory {
public:
    static std::shared_ptr<Shape> createShape(const std::string& type) {
        if (type == "circle") {
            return std::make_shared<Circle>();
        } else if (type == "square") {
            return std::make_shared<Square>();
        } else if (type == "rectangle") {
            return std::make_shared<Rectangle>();
        } else {
            std::cerr << "Unknown shape type: " << type << "\n";
            return nullptr;
        }
    }
};

// ===== 客户端调用 =====
int main() {
    std::shared_ptr<Shape> shape1 = ShapeFactory::createShape("circle");
    if (shape1) shape1->draw();

    std::shared_ptr<Shape> shape2 = ShapeFactory::createShape("square");
    if (shape2) shape2->draw();

    std::shared_ptr<Shape> shape3 = ShapeFactory::createShape("rectangle");
    if (shape3) shape3->draw();

    std::shared_ptr<Shape> shape4 = ShapeFactory::createShape("triangle"); // 错误类型
    if (shape4) shape4->draw();

    return 0;
}

// 输出结果
// Drawing Circle
// Drawing Square
// Drawing Rectangle
// Unknown shape type: triangle

// 定义：由一个工厂类根据传入参数，决定创建哪个产品类的实例。客户端无需知道产品的具体类名，只需向工厂请求对象即可。
