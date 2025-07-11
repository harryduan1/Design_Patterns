#include <iostream>

class ChineseSocket {
public:
    virtual void chargeByChinesePlug() = 0;
    virtual ~ChineseSocket() = default;
};

class BritishPlug {
public:
    void chargeByBritishPlug() {
        std::cout << "🔌 Charging using British Plug 🇬🇧\n";
    }
};

class PlugAdapter : public ChineseSocket {
private:
    BritishPlug* britishPlug;

public:
    PlugAdapter(BritishPlug* plug) : britishPlug(plug) {}

    void chargeByChinesePlug() override {
        std::cout << "Adapter converts Chinese socket to British plug...\n";
        britishPlug->chargeByBritishPlug();  // 委托调用
    }
};

int main() {
    BritishPlug* ukPlug = new BritishPlug();

    // 将英标插头适配成中国插座
    ChineseSocket* socket = new PlugAdapter(ukPlug);

    // 客户端只认中国插座接口
    socket->chargeByChinesePlug();

    delete socket;
    delete ukPlug;

    return 0;
}

// 输出结果
/*
Adapter converts Chinese socket to British plug...
🔌 Charging using British Plug 🇬🇧
*/

/*
定义：适配器模式（Adapter Pattern）：将一个类的接口转换成客户端期望的另一个接口，解决接口不兼容的问题。
它属于 结构型设计模式。
*/

// 一句话总结 适配器模式 = 旧接口不变，新接口兼容，目标统一、调用无忧。