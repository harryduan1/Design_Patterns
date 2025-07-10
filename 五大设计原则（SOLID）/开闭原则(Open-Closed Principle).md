## ✅ 一、什么是开闭原则？

> **开闭原则（Open-Closed Principle，OCP）** 是面向对象设计中的 **SOLID 五大原则** 之一。

### 🌟 定义：

> **软件实体（类、模块、函数）应该对扩展开放，对修改关闭。**

即：

* **对扩展开放** ：允许新增功能。
* **对修改关闭** ：已有代码不需要改动。

---

## ✅ 二、通俗理解

> 不要通过**改原来的代码**来实现新功能，而是通过**扩展新代码**来实现。

### ✅ 比喻：

> 插线板设计：当你要增加插口功能时，只需要加新插头（扩展），**不需要拆开插线板本体（修改）**

---

## ✅ 三、常见的错误示例（违反 OCP）

```c++
enum ShapeType { CIRCLE, RECTANGLE };

class Shape {
public:
    ShapeType type;
};

class Drawing {
public:
    void draw(Shape* shape) {
        if (shape->type == CIRCLE) {
            std::cout << "Drawing circle\n";
        } else if (shape->type == RECTANGLE) {
            std::cout << "Drawing rectangle\n";
        }
        // ❌ 新增三角形时，需要改这里
    }
};

```

👎 问题：

* 每增加一种图形，就要改 `draw()` 方法
* **不符合“对修改关闭”原则**

---

## ✅ 四、如何重构：遵循 OCP 的方式（多态）

```c++
// 抽象类
class Shape {
public:
    virtual void draw() = 0;
    virtual ~Shape() {}
};

// 扩展类：Circle
class Circle : public Shape {
public:
    void draw() override {
        std::cout << "Drawing circle\n";
    }
};

// 扩展类：Rectangle
class Rectangle : public Shape {
public:
    void draw() override {
        std::cout << "Drawing rectangle\n";
    }
};

// 调用方
class Drawing {
public:
    void drawShape(Shape* shape) {
        shape->draw();  // ✅ 不用修改，支持扩展
    }
};

```

👍 优点：

* 新增图形时只需新增子类（如 Triangle）
* 原有的 `Drawing` 类无需修改
* 实现了**开闭原则**

---

## ✅ 五、开闭原则的实现方式

| 方法                   | 说明                         |
| ---------------------- | ---------------------------- |
| 接口/抽象类 + 多态     | 面向抽象编程，新增功能写子类 |
| 策略模式               | 动态替换算法                 |
| 装饰器模式             | 动态扩展功能，不改原类       |
| 责任链、命令、观察者等 | 都属于“开放扩展”机制       |

---

## ✅ 六、开闭原则在实际项目中的应用

| 场景                     | 应用                                     |
| ------------------------ | ---------------------------------------- |
| UI 控件                  | 新增按钮/控件类型，继承基类即可          |
| 设备通讯层（如串口/ADB） | 每种设备写一个 `DeviceInterface`实现   |
| 状态处理系统（状态机）   | 每种状态写一个状态类                     |
| 消息处理系统             | 新增消息类型时只需新增处理类，不改旧代码 |

---

## ✅ 七、开闭原则的好处

| 好处            | 说明                     |
| --------------- | ------------------------ |
| ✅ 降低耦合     | 原始类不被频繁修改       |
| ✅ 易于扩展     | 新需求只需“加”         |
| ✅ 提高稳定性   | 老代码不动更安全         |
| ✅ 支持插件机制 | 插件即扩展，不动核心代码 |

---

## ✅ 八、一句话总结

> **开闭原则 = 加功能时“加代码”，而不是“改代码”。**

遵循它会让你的系统 **可扩展、易维护、稳定可靠** 。
