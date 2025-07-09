#include <iostream>
#include <memory>

// === 抽象产品：按钮 ===
class Button {
public:
    virtual void paint() = 0;
    virtual ~Button() {}
};

// === 抽象产品：复选框 ===
class CheckBox {
public:
    virtual void paint() = 0;
    virtual ~CheckBox() {}
};

// === 具体产品：Windows风格按钮 ===
class WindowsButton : public Button {
public:
    void paint() override {
        std::cout << "Render a button in Windows style\n";
    }
};

// === 具体产品：Mac风格按钮 ===
class MacButton : public Button {
public:
    void paint() override {
        std::cout << "Render a button in Mac style\n";
    }
};

// === 具体产品：Windows风格复选框 ===
class WindowsCheckBox : public CheckBox {
public:
    void paint() override {
        std::cout << "Render a checkbox in Windows style\n";
    }
};

// === 具体产品：Mac风格复选框 ===
class MacCheckBox : public CheckBox {
public:
    void paint() override {
        std::cout << "Render a checkbox in Mac style\n";
    }
};

// === 抽象工厂 ===
class GUIFactory {
public:
    virtual std::shared_ptr<Button> createButton() = 0;
    virtual std::shared_ptr<CheckBox> createCheckBox() = 0;
    virtual ~GUIFactory() {}
};

// === 具体工厂：Windows风格 ===
class WindowsFactory : public GUIFactory {
public:
    std::shared_ptr<Button> createButton() override {
        return std::make_shared<WindowsButton>();
    }

    std::shared_ptr<CheckBox> createCheckBox() override {
        return std::make_shared<WindowsCheckBox>();
    }
};

// === 具体工厂：Mac风格 ===
class MacFactory : public GUIFactory {
public:
    std::shared_ptr<Button> createButton() override {
        return std::make_shared<MacButton>();
    }

    std::shared_ptr<CheckBox> createCheckBox() override {
        return std::make_shared<MacCheckBox>();
    }
};

// === 客户端代码 ===
void buildUI(std::shared_ptr<GUIFactory> factory) {
    auto button = factory->createButton();
    auto checkbox = factory->createCheckBox();
    button->paint();
    checkbox->paint();
}

int main() {
    std::cout << "[Windows UI]\n";
    buildUI(std::make_shared<WindowsFactory>());

    std::cout << "\n[Mac UI]\n";
    buildUI(std::make_shared<MacFactory>());

    return 0;
}

// 输出结果
// [Windows UI]
// Render a button in Windows style
// Render a checkbox in Windows style

// [Mac UI]
// Render a button in Mac style
// Render a checkbox in Mac style


/*
定义：抽象工厂模式提供一个接口，用于创建一系列相关或相互依赖的对象，而无需指定它们的具体类。
它允许客户端代码在不修改的情况下切换产品族。
这种模式通常用于需要跨多个产品系列创建对象的场景，例如在不同的操作系统上创建用户界面组件时，
可以使用不同的工厂来创建相应风格的按钮和复选框。
通过使用抽象工厂模式，可以确保在创建产品时，所有产品都属于同一产品族，从而避免了不兼容的产品组合。
这样，客户端代码只需依赖于抽象工厂接口，而不需要了解具体的产品类，从而实现了更好的解耦和扩展性。
这种模式的优点是可以轻松添加新的产品系列，只需创建新的工厂类和具体产品类，而不需要修改现有的代码。
这符合开闭原则（Open-Closed Principle），使得系统更易于维护和扩展。
*/

