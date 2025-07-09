#include <stdio.h>
#include <stdlib.h>

// ======= 1. 定义虚函数表（抽象接口） =======

typedef struct Shape Shape;  // 前向声明

typedef struct {
    void (*draw)(Shape*);  // “虚函数”
} ShapeVTable;

// ======= 2. 定义基类 =======

struct Shape {
    const ShapeVTable* vtable;  // 虚表指针
};

// 提供一个调用接口（类似于虚函数调用）
void Shape_draw(Shape* shape) {
    shape->vtable->draw(shape);
}

// ======= 3. 派生类：Circle =======

typedef struct {
    Shape base;  // 继承：基类作为第一个成员
    int radius;
} Circle;

// Circle 实现的 draw 函数
void Circle_draw(Shape* shape) {
    Circle* self = (Circle*)shape;  // 向下转型
    printf("Drawing a circle with radius %d\n", self->radius);
}

// Circle 的虚函数表
const ShapeVTable circle_vtable = {
    .draw = Circle_draw
};

// 构造函数
Circle* Circle_new(int radius) {
    Circle* c = malloc(sizeof(Circle));
    c->base.vtable = &circle_vtable;
    c->radius = radius;
    return c;
}

// ======= 4. 派生类：Square =======

typedef struct {
    Shape base;
    int size;
} Square;

void Square_draw(Shape* shape) {
    Square* self = (Square*)shape;
    printf("Drawing a square with size %d\n", self->size);
}

const ShapeVTable square_vtable = {
    .draw = Square_draw
};

Square* Square_new(int size) {
    Square* s = malloc(sizeof(Square));
    s->base.vtable = &square_vtable;
    s->size = size;
    return s;
}

// ======= 5. 客户端代码（多态调用） =======

int main() {
    // 多态数组：基类指针数组
    Shape* shapes[2];

    shapes[0] = (Shape*)Circle_new(5);
    shapes[1] = (Shape*)Square_new(10);

    for (int i = 0; i < 2; ++i) {
        Shape_draw(shapes[i]);  // 多态调用
    }

    // 释放资源
    for (int i = 0; i < 2; ++i) {
        free(shapes[i]);
    }

    return 0;
}

// 输出结果
// Drawing a circle with radius 5
// Drawing a square with size 10

// cpp
/*
class Shape {
public:
    virtual void draw();
};

class Circle : public Shape {
public:
    void draw() override;
};
*/

/*
使用 结构体 + 函数指针 + “虚函数表”模拟继承与多态。
| C++ 概念      | C 的模拟方式      |
| ----------- | ------------ |
| 类           | `struct`     |
| 虚函数         | 函数指针         |
| 虚函数表 vtable | 包含函数指针的结构体   |
| 基类指针调用子类实现  | 基类结构体中保存函数指针 |
*/

