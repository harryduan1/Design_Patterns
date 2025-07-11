#include <iostream>
#include <memory>

// 实现接口
class TV {
public:
    virtual void on() = 0;
    virtual void off() = 0;
    virtual void tuneChannel(int channel) = 0;
    virtual ~TV() = default;
};

// 具体实现 1：Sony TV
class SonyTV : public TV {
public:
    void on() override {
        std::cout << "Sony TV is ON\n";
    }
    void off() override {
        std::cout << "Sony TV is OFF\n";
    }
    void tuneChannel(int channel) override {
        std::cout << "Sony TV tuned to channel " << channel << "\n";
    }
};

// 具体实现 2：Samsung TV
class SamsungTV : public TV {
public:
    void on() override {
        std::cout << "Samsung TV is ON\n";
    }
    void off() override {
        std::cout << "Samsung TV is OFF\n";
    }
    void tuneChannel(int channel) override {
        std::cout << "Samsung TV tuned to channel " << channel << "\n";
    }
};

// 抽象类：遥控器
class RemoteControl {
protected:
    std::shared_ptr<TV> tv;
public:
    explicit RemoteControl(std::shared_ptr<TV> t) : tv(std::move(t)) {}
    virtual void turnOn() {
        tv->on();
    }
    virtual void turnOff() {
        tv->off();
    }
    virtual void setChannel(int channel) {
        tv->tuneChannel(channel);
    }
    virtual ~RemoteControl() = default;
};

// 扩展抽象类：带静音功能的遥控器
class AdvancedRemoteControl : public RemoteControl {
public:
    explicit AdvancedRemoteControl(std::shared_ptr<TV> t) : RemoteControl(std::move(t)) {}
    void mute() {
        std::cout << "TV is muted.\n";
    }
};

// 客户端代码
int main() {
    std::shared_ptr<TV> sony = std::make_shared<SonyTV>();
    std::shared_ptr<TV> samsung = std::make_shared<SamsungTV>();

    RemoteControl basicRemote(sony);
    basicRemote.turnOn();
    basicRemote.setChannel(5);
    basicRemote.turnOff();

    std::cout << "-------------------------\n";

    AdvancedRemoteControl advancedRemote(samsung);
    advancedRemote.turnOn();
    advancedRemote.setChannel(10);
    advancedRemote.mute();
    advancedRemote.turnOff();

    return 0;
}

// 输出结果
/*
Sony TV is ON  
Sony TV tuned to channel 5
Sony TV is OFF
-------------------------
Samsung TV is ON
Samsung TV tuned to channel 10
TV is muted.
Samsung TV is OFF
*/