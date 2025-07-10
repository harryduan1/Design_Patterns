## ✅ 一、定义：什么是接口隔离原则？

> **客户端不应该依赖它不使用的方法。**
>
> 一个类对另一个类的依赖，应该建立在最小的接口上。

---

## ✅ 二、通俗解释

> 不要强迫类实现它用不到的方法。
>
> 应该将 **大而全的接口，拆分成小而专的接口** 。

就像生活中一样：

* 你不会因为想吃饭就必须实现洗衣服、打扫卫生等功能。
* 你不想被“强迫”做无关的事。

---

## ✅ 三、违反 ISP 的例子（💣 大而臃肿的接口）

```c++
// 通用机器接口
class Machine {
public:
    virtual void print() = 0;
    virtual void scan() = 0;
    virtual void fax() = 0;
    virtual ~Machine() {}
};

// 只支持打印的设备
class SimplePrinter : public Machine {
public:
    void print() override {
        std::cout << "Printing...\n";
    }

    void scan() override {
        throw std::logic_error("Scan not supported!"); // ❌
    }

    void fax() override {
        throw std::logic_error("Fax not supported!");  // ❌
    }
};

```

👎 **问题：**

* `SimplePrinter` 只想打印，但被迫实现 scan 和 fax。
* 改接口容易影响所有实现者，造成 **破坏性修改** 。

---

## ✅ 遵守 ISP 的设计（🪓 拆接口）

```c++
class IPrinter {
public:
    virtual void print() = 0;
    virtual ~IPrinter() {}
};

class IScanner {
public:
    virtual void scan() = 0;
    virtual ~IScanner() {}
};

class IFax {
public:
    virtual void fax() = 0;
    virtual ~IFax() {}
};

// 只打印的设备
class SimplePrinter : public IPrinter {
public:
    void print() override {
        std::cout << "SimplePrinter printing\n";
    }
};

// 多功能一体机
class MultiFunctionPrinter : public IPrinter, public IScanner, public IFax {
public:
    void print() override {
        std::cout << "Printing...\n";
    }

    void scan() override {
        std::cout << "Scanning...\n";
    }

    void fax() override {
        std::cout << "Faxing...\n";
    }
};

```

👍 优点：

* 谁需要什么功能就实现什么接口。
* 避免“臃肿接口”，符合 **单一职责原则（SRP）** 。

---

## ✅ 四、接口隔离原则的现实意义

| 优点            | 描述                             |
| --------------- | -------------------------------- |
| ✅ 降低耦合     | 类之间依赖的接口更小、影响范围小 |
| ✅ 增强灵活性   | 可以自由组合接口功能             |
| ✅ 提高可维护性 | 改动不会影响用不到接口的类       |
| ✅ 更易于测试   | 更小的接口更容易模拟（Mock）     |

---

## ✅ 五、与其他设计原则关系

| 原则            | 关系说明                                   |
| --------------- | ------------------------------------------ |
| SRP（单一职责） | ISP 是接口层面的 SRP（一个接口只干一件事） |
| DIP（依赖倒置） | DIP 建议依赖接口，ISP 则建议接口要小而精   |

---

## ✅ 六、总结一句话

> **接口要小、精、专用 —— 谁用什么就提供什么，不要“一刀切”。**
>
