#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

class Subject {
private:
    std::vector<Observer*> observers;

public:
    void attach(Observer* obs) {
        observers.push_back(obs);
    }

    void detach(Observer* obs) {
        observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
    }

protected:
    void notify(int value) {
        for (auto obs : observers) {
            obs->update(value);
        }
    }
};


class Observer {
public:
    virtual void update(int value) = 0;
    virtual ~Observer() = default;
};

class ConcreteSubject : public Subject {
private:
    int state = 0;

public:
    void setState(int value) {
        state = value;
        notify(state);  // 通知所有观察者
    }

    int getState() const {
        return state;
    }
};

class ConcreteObserver : public Observer {
private:
    std::string name;

public:
    explicit ConcreteObserver(const std::string& n) : name(n) {}

    void update(int value) override {
        std::cout << "Observer [" << name << "] received update: " << value << "\n";
    }
};

int main() {
    ConcreteSubject subject;

    ConcreteObserver observer1("A");
    ConcreteObserver observer2("B");

    subject.attach(&observer1);
    subject.attach(&observer2);

    subject.setState(100);  // 所有观察者收到通知

    subject.detach(&observer1);

    subject.setState(200);  // 只有 B 收到通知

    return 0;
}

// 输出结果
/*
Observer [A] received update: 100
Observer [B] received update: 100
Observer [B] received update: 200
*/

// 定义：观察者模式（Observer Pattern）是一种行为型设计模式，定义了一种一对多的依赖关系，
// 让多个观察者对象同时监听某一个主题对象，当主题对象发生变化时，所有依赖于它的观察者都会收到通知并自动更新。

//一句话总结 观察者模式 = 订阅 + 通知机制，让多个对象跟踪一个对象的变化。

