#include <iostream>

// ===== 抽象类：饮料制作流程 =====
class CaffeineBeverage {
public:
    // 模板方法（算法框架，不可更改）
    void prepareRecipe() {
        boilWater();        // 公共步骤
        brew();             // 变化点（延迟到子类）
        pourInCup();        // 公共步骤
        addCondiments();    // 变化点（延迟到子类）
    }

    virtual ~CaffeineBeverage() {}

protected:
    void boilWater() {
        std::cout << "Boiling water\n";
    }

    void pourInCup() {
        std::cout << "Pouring into cup\n";
    }

    // 抽象步骤（必须由子类实现）
    virtual void brew() = 0;
    virtual void addCondiments() = 0;
};

// ===== 子类：Tea =====
class Tea : public CaffeineBeverage {
protected:
    void brew() override {
        std::cout << "Steeping the tea\n";
    }

    void addCondiments() override {
        std::cout << "Adding lemon\n";
    }
};

// ===== 子类：Coffee =====
class Coffee : public CaffeineBeverage {
protected:
    void brew() override {
        std::cout << "Dripping coffee through filter\n";
    }

    void addCondiments() override {
        std::cout << "Adding sugar and milk\n";
    }
};

// ===== 客户端代码 =====
int main() {
    std::cout << "Making tea:\n";
    Tea tea;
    tea.prepareRecipe();

    std::cout << "\nMaking coffee:\n";
    Coffee coffee;
    coffee.prepareRecipe();

    return 0;
}


// 输出结果

/*
Making tea:
Boiling water
Steeping the tea
Pouring into cup
Adding lemon

Making coffee:
Boiling water
Dripping coffee through filter
Pouring into cup
Adding sugar and milk
*/

// 定义：模板方法模式定义一个操作的算法骨架，将某些步骤延迟到子类中。子类可以重写某些步骤，但不能改变整体算法结构。

/*
| 优点       | 说明                |
| -------- | ----------------- |
| ✅ 封装通用流程 | 避免重复代码            |
| ✅ 支持定制化  | 子类可复用公共流程，仅重写必要步骤 |
| ✅ 遵循开闭原则 | 修改流程只需添加新子类       |
*/

/*
适用场景：

多个子类共用一个通用算法框架

编译器前后端结构：前端语法分析统一，后端优化可变

游戏引擎中的角色状态更新流程

嵌入式设备初始化流程（如 sensor_init → power_on → config_xxx）
*/