#include <iostream>

class Context;  // 前向声明

class State {
public:
    virtual void handle(Context* context) = 0;
    virtual ~State() {}
};

class OnState : public State {
public:
    void handle(Context* context) override;
};

class OffState : public State {
public:
    void handle(Context* context) override;
};

class Context {
private:
    State* currentState;

public:
    explicit Context(State* state) : currentState(state) {}

    void setState(State* state) {
        currentState = state;
    }

    void request() {
        if (currentState)
            currentState->handle(this);
    }
};

void OnState::handle(Context* context) {
    std::cout << "Light is ON. Switching to OFF...\n";
    context->setState(new OffState());
    delete this;
}

void OffState::handle(Context* context) {
    std::cout << "Light is OFF. Switching to ON...\n";
    context->setState(new OnState());
    delete this;
}

int main() {
    Context* light = new Context(new OffState());

    // 模拟用户多次按开关按钮
    for (int i = 0; i < 4; ++i) {
        light->request();  // 切换状态
    }

    delete light;
    return 0;
}

// 输出结果
/*
Light is OFF. Switching to ON...
Light is ON. Switching to OFF...
Light is OFF. Switching to ON...
Light is ON. Switching to OFF...
*/

/*
定义：状态模式允许一个对象在其内部状态发生改变时改变它的行为，看起来就像是改变了它的类一样。

它属于 行为型设计模式，核心思想是：状态即行为的封装。
*/

// 一句话总结 状态模式 = 行为由状态决定，状态由类来封装，切换清晰、扩展方便。




