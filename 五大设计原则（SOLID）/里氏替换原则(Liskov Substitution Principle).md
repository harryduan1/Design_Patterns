## ✅ 一、什么是里氏替换原则？

> **LSP 是 SOLID 五大设计原则中的第三个原则** ，由 **Barbara Liskov 教授** 在 1987 年提出。

### 🌟 定义：

> 如果对每一个类型为 T1 的对象 o1，都有类型为 T2 的对象 o2，使得在不改变程序正确性的前提下，o1 能被 o2 替换，那么 T2 是 T1 的子类型。
>
> —— Barbara Liskov

### ✅ 通俗解释：

> **子类对象必须能够替换父类对象，并保证原有功能逻辑不出错。**

---

## ✅ 二、一句话总结

> **子类能完全替代父类出现的地方，且行为正确、不破坏语义。**

---

## ✅ 三、举个简单的 C++ 例子（✅ 正确的替代）

```c++
class Bird {
public:
    virtual void fly() {
        std::cout << "Bird is flying\n";
    }
};

class Sparrow : public Bird {
public:
    void fly() override {
        std::cout << "Sparrow is flying\n";
    }
};

void letBirdFly(Bird* b) {
    b->fly();  // 不管是 Bird 还是 Sparrow，逻辑一致
}

int main() {
    Sparrow sp;
    letBirdFly(&sp);  // ✅ 替代成立，符合里氏替换原则
}

```

---

## ❌ 违反里氏替换原则的例子

```c++
class Bird {
public:
    virtual void fly() {
        std::cout << "Bird is flying\n";
    }
};

class Ostrich : public Bird {
public:
    void fly() override {
        throw std::logic_error("Ostrich can't fly!");  // ❌ 不符合逻辑
    }
};

```

👎 **问题分析：**

* 父类 Bird 的 fly() 意图是“能飞”
* 子类 Ostrich 却不能飞，抛异常或空实现
* 这时如果某个函数使用 `Bird*`，传入 Ostrich 会造成异常

---

## ✅ 解决方式

将飞行动作抽象成独立接口，而不是所有 Bird 都继承 fly：

```c++
class Bird { };

class IFlyable {
public:
    virtual void fly() = 0;
};

class Sparrow : public Bird, public IFlyable {
public:
    void fly() override {
        std::cout << "Sparrow flies!\n";
    }
};

class Ostrich : public Bird {
    // 不实现 fly
};

```

👍 这样只有能飞的鸟才实现 fly 接口，避免不符合语义的继承。

---

## ✅ 四、LSP 在设计中常见的体现

| 场景                       | 正确做法                           |
| -------------------------- | ---------------------------------- |
| 继承父类后不能实现所有功能 | 拆接口（ISP），组合代替继承        |
| 子类修改父类方法逻辑       | 保证不会破坏语义和预期行为         |
| 子类添加限制（比如异常）   | 是典型的违反，应通过策略模式等解决 |

---

## ✅ 五、LSP 和其他设计原则关系

* 和 **开闭原则（OCP）** 搭配使用：OCP 要求扩展不改父类，LSP 保证子类的扩展是正确的。
* 和 **依赖倒置原则（DIP）** 搭配：高层模块依赖接口，LSP 保证替换时仍然正确。

---

## ✅ 六、真实工程中建议

| 做法                      | 理由                                 |
| ------------------------- | ------------------------------------ |
| ✔ 明确继承的语义         | 不要盲目继承，只因“代码复用”       |
| ✔ 用组合优于继承         | 当不确定是否满足里氏替换时，考虑组合 |
| ✔ 尽量用接口抽象行为     | 让行为“明确”，避免父类行为模糊     |
| ❌ 子类实现空函数、抛异常 | 极可能是违反了 LSP                   |

---

## ✅ 七、一句话总结

> **继承不仅是“代码复用”，更是“语义契约” —— 子类必须能替代父类，且行为一致。**
>
