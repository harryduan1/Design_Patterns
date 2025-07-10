## ✅ 一、什么是依赖倒置原则（DIP）？

> **依赖倒置原则（Dependency Inversion Principle）是 SOLID 五大设计原则之一。**

### 🌟 定义：

> 高层模块不应该依赖低层模块，二者都应该依赖于抽象；
>
> 抽象不应该依赖细节，细节应该依赖抽象。

---

## ✅ 二、通俗理解

### 🔧 常见错误依赖：

```
高层模块（业务逻辑）
     ↓ 依赖
低层模块（数据库、网络、驱动等）

```

✅ 正确依赖方式（DIP）：

```
高层模块 ----> 接口（抽象） <---- 低层模块

```

* 高层模块依赖抽象（接口）
* 低层模块也实现接口，反过来依赖抽象
* 控制反转（IoC）+ 依赖注入（DI）是实现手段

---

## ✅ 三、举个例子（违反 vs 遵守）

### 🔴 违反依赖倒置：

```c++
class MySQLDatabase {
public:
    void connect() {
        std::cout << "Connect to MySQL\n";
    }
};

class UserService {
private:
    MySQLDatabase db;  // ❌ 直接依赖低层细节
public:
    void getUser() {
        db.connect();
        std::cout << "Get user\n";
    }
};

```

👎 问题：

* `UserService` 高层模块依赖了具体的 `MySQLDatabase`
* 将来要换数据库（如 PostgreSQL）要改 UserService 代码

---

### ✅ 遵守依赖倒置：

```c++
// 抽象接口
class IDatabase {
public:
    virtual void connect() = 0;
    virtual ~IDatabase() {}
};

// 低层模块实现接口
class MySQLDatabase : public IDatabase {
public:
    void connect() override {
        std::cout << "Connect to MySQL\n";
    }
};

class UserService {
private:
    IDatabase* db;  // 依赖于抽象 ✅
public:
    UserService(IDatabase* database) : db(database) {}

    void getUser() {
        db->connect();
        std::cout << "Get user\n";
    }
};

```

👆 优点：

* `UserService` 只依赖 `IDatabase` 抽象，不依赖具体类
* 支持未来扩展（比如 PostgreSQL、SQLite）
* 可以用 mock 实现做测试，符合开闭原则

---

## ✅ 四、依赖倒置原则核心要点

| 原则             | 解释                                   |
| ---------------- | -------------------------------------- |
| 高层模块依赖抽象 | 比如业务逻辑依赖接口，不依赖具体实现类 |
| 低层模块实现抽象 | 数据库、驱动、API 等细节通过接口暴露   |
| 抽象不依赖于细节 | 接口稳定、实现可变                     |
| 细节依赖于抽象   | 实现类去遵循接口定义                   |

---

## ✅ 五、如何实现 DIP

| 方法            | 描述                                   |
| --------------- | -------------------------------------- |
| 接口编程        | 用纯虚类（C++）或函数指针（C）         |
| 依赖注入（DI）  | 将依赖从构造函数、set 函数或参数传入   |
| 控制反转（IoC） | 高层模块不创建底层对象，由外部容器控制 |

---

## ✅ 六、与其他设计模式的关系

| 模式/原则    | 说明                                   |
| ------------ | -------------------------------------- |
| 工厂模式     | 通过工厂返回接口，实现依赖抽象         |
| 策略模式     | 将行为封装为接口，实现“细节依赖抽象” |
| 服务注册中心 | 管理抽象到实现的映射，配合 IoC 容器    |

---

## ✅ 七、总结一句话

> **依赖倒置原则的核心：依赖抽象，而不是具体实现。**
>
> 这有助于实现松耦合、可测试、易扩展的系统架构。
>
