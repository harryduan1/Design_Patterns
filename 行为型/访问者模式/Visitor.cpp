#include <iostream>
#include <vector>
#include <memory>

// 前向声明
class Circle;
class Rectangle;

// 抽象访问者
class Visitor {
public:
    virtual void visit(Circle* c) = 0;
    virtual void visit(Rectangle* r) = 0;
    virtual ~Visitor() = default;
};

// 抽象元素
class Shape {
public:
    virtual void accept(Visitor* visitor) = 0;
    virtual ~Shape() = default;
};

// 具体元素：圆形
class Circle : public Shape {
public:
    float radius;
    explicit Circle(float r) : radius(r) {}

    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};

// 具体元素：矩形
class Rectangle : public Shape {
public:
    float width;
    float height;

    Rectangle(float w, float h) : width(w), height(h) {}

    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};

// 具体访问者：打印信息
class PrintVisitor : public Visitor {
public:
    void visit(Circle* c) override {
        std::cout << "Circle with radius: " << c->radius << std::endl;
    }

    void visit(Rectangle* r) override {
        std::cout << "Rectangle with width: " << r->width << ", height: " << r->height << std::endl;
    }
};

// 具体访问者：计算面积
class AreaVisitor : public Visitor {
public:
    void visit(Circle* c) override {
        float area = 3.14159f * c->radius * c->radius;
        std::cout << "Circle area: " << area << std::endl;
    }

    void visit(Rectangle* r) override {
        float area = r->width * r->height;
        std::cout << "Rectangle area: " << area << std::endl;
    }
};

// 测试客户端
int main() {
    std::vector<std::shared_ptr<Shape>> shapes;
    shapes.push_back(std::make_shared<Circle>(5.0f));
    shapes.push_back(std::make_shared<Rectangle>(4.0f, 6.0f));

    PrintVisitor printer;
    AreaVisitor areaCalc;

    std::cout << "--- Printing Shapes ---" << std::endl;
    for (const auto& shape : shapes) {
        shape->accept(&printer);
    }

    std::cout << "\n--- Calculating Area ---" << std::endl;
    for (const auto& shape : shapes) {
        shape->accept(&areaCalc);
    }

    return 0;
}

// 输出结果
/*
--- Printing Shapes ---
Circle with radius: 5
Rectangle with width: 4, height: 6

--- Calculating Area ---
Circle area: 78.5397
Rectangle area: 24
*/