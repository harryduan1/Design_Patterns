#include <iostream>
#include <memory>
#include <vector>

// 接收者类：灯
class Light {
public:
    void on() {
        std::cout << "Light is ON\n";
    }

    void off() {
        std::cout << "Light is OFF\n";
    }
};

// 命令接口
class Command {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Command() = default;
};

// 具体命令：打开灯
class LightOnCommand : public Command {
private:
    Light* light;
public:
    explicit LightOnCommand(Light* l) : light(l) {}
    void execute() override {
        light->on();
    }
    void undo() override {
        light->off();
    }
};

// 具体命令：关闭灯
class LightOffCommand : public Command {
private:
    Light* light;
public:
    explicit LightOffCommand(Light* l) : light(l) {}
    void execute() override {
        light->off();
    }
    void undo() override {
        light->on();
    }
};

// 调用者类：遥控器
class RemoteControl {
private:
    Command* onCommand;
    Command* offCommand;
    Command* lastCommand; // 用于撤销
public:
    RemoteControl() : onCommand(nullptr), offCommand(nullptr), lastCommand(nullptr) {}

    void setCommands(Command* onCmd, Command* offCmd) {
        onCommand = onCmd;
        offCommand = offCmd;
    }

    void pressOnButton() {
        if (onCommand) {
            onCommand->execute();
            lastCommand = onCommand;
        }
    }

    void pressOffButton() {
        if (offCommand) {
            offCommand->execute();
            lastCommand = offCommand;
        }
    }

    void pressUndoButton() {
        if (lastCommand) {
            std::cout << "Undoing last command: ";
            lastCommand->undo();
        }
    }
};

// 客户端代码
int main() {
    Light livingRoomLight;

    // 创建命令
    LightOnCommand onCmd(&livingRoomLight);
    LightOffCommand offCmd(&livingRoomLight);

    // 设置遥控器
    RemoteControl remote;
    remote.setCommands(&onCmd, &offCmd);

    remote.pressOnButton();    // 输出：Light is ON
    remote.pressOffButton();   // 输出：Light is OFF
    remote.pressUndoButton();  // 输出：Undoing last command: Light is ON

    return 0;
}

// 输出结果
/*
Light is ON
Light is OFF
Undoing last command: Light is ON
*/

/*
命令模式的定义：
将请求封装为一个对象，从而使你可以用不同的请求对客户进行参数化，支持请求排队、日志记录、撤销操作等功能。
*/

/*
用一句话总结：
把“动作的请求者”和“动作的执行者”解耦，通过中间的“命令对象”进行沟通。
*/