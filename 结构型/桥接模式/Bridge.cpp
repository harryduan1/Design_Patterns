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

/*
桥接模式是设计Java虚拟机和实现JDBC等驱动程序的核心模式之一，应用较为广泛。在软件开发中如果一个类或一个系统有多个变化维度时，
都可以尝试使用桥接模式对其进行设计。桥接模式为多维度变化的系统提供了一套完整的解决方案，并且降低了系统的复杂度。
1.主要优点

桥接模式的主要优点如下：

(1)分离抽象接口及其实现部分。桥接模式使用“对象间的关联关系”解耦了抽象和实现之间固有的绑定关系，使得抽象和实现可以沿着各自的维度来变化。
所谓抽象和实现沿着各自维度的变化，也就是说抽象和实现不再在同一个继承层次结构中，
而是“子类化”它们，使它们各自都具有自己的子类，以便任何组合子类，从而获得多维度组合对象。

(2)在很多情况下，桥接模式可以取代多层继承方案，多层继承方案违背了“单一职责原则”，复用性较差，且类的个数非常多，
桥接模式是比多层继承方案更好的解决方法，它极大减少了子类的个数。

(3)桥接模式提高了系统的可扩展性，在两个变化维度中任意扩展一个维度，都不需要修改原有系统，符合“开闭原则”。

2.主要缺点

桥接模式的主要缺点如下：

(1)桥接模式的使用会增加系统的理解与设计难度，由于关联关系建立在抽象层，要求开发者一开始就针对抽象层进行设计与编程。

(2)桥接模式要求正确识别出系统中两个独立变化的维度，因此其使用范围具有一定的局限性，如何正确识别两个独立维度也需要一定的经验积累。

3.适用场景

在以下情况下可以考虑使用桥接模式：

(1)如果一个系统需要在抽象化和具体化之间增加更多的灵活性，避免在两个层次之间建立静态的继承关系，
通过桥接模式可以使它们在抽象层建立一个关联关系。

(2)“抽象部分”和“实现部分”可以以继承的方式独立扩展而互不影响，在程序运行时可以动态将一个抽象化子类的对象和一个实现化子类的对象进行组合，
即系统需要对抽象化角色和实现化角色进行动态耦合。

(3)一个类存在两个（或多个）独立变化的维度，且这两个（或多个）维度都需要独立进行扩展。

(4)对于那些不希望使用继承或因为多层继承导致系统类的个数急剧增加的系统，桥接模式尤为适用。

练习

> Sunny软件公司欲开发一个数据转换工具，可以将数据库中的数据转换成多种文件格式，
例如txt、xml、pdf等格式，同时该工具需要支持多种不同的数据库。试使用桥接模式对其进行设计。
*/