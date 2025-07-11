#include <iostream>
#include <string>

class Computer {
public:
    std::string cpu;
    std::string gpu;
    std::string memory;
    std::string storage;

    void show() const {
        std::cout << "Computer Configuration:\n";
        std::cout << "  CPU: " << cpu << "\n";
        std::cout << "  GPU: " << gpu << "\n";
        std::cout << "  Memory: " << memory << "\n";
        std::cout << "  Storage: " << storage << "\n";
    }
};

class ComputerBuilder {
public:
    virtual ~ComputerBuilder() = default;
    virtual void buildCPU() = 0;
    virtual void buildGPU() = 0;
    virtual void buildMemory() = 0;
    virtual void buildStorage() = 0;
    virtual Computer* getResult() = 0;
};

class GamingComputerBuilder : public ComputerBuilder {
private:
    Computer* computer;

public:
    GamingComputerBuilder() { computer = new Computer(); }
    ~GamingComputerBuilder() { /* 注意：此处不 delete，留给外部处理 */ }

    void buildCPU() override { computer->cpu = "Intel i9"; }
    void buildGPU() override { computer->gpu = "NVIDIA RTX 4090"; }
    void buildMemory() override { computer->memory = "32GB DDR5"; }
    void buildStorage() override { computer->storage = "2TB NVMe SSD"; }

    Computer* getResult() override { return computer; }
};

class Director {
public:
    void construct(ComputerBuilder* builder) {
        builder->buildCPU();
        builder->buildGPU();
        builder->buildMemory();
        builder->buildStorage();
    }
};

int main() {
    Director director;
    GamingComputerBuilder builder;

    director.construct(&builder);

    Computer* computer = builder.getResult();
    computer->show();

    delete computer;  // ✅ 注意释放
    return 0;
}

// 输出结果
/*
Computer Configuration:
  CPU: Intel i9
  GPU: NVIDIA RTX 4090
  Memory: 32GB DDR5
  Storage: 2TB NVMe SSD
*/

/*
定义：
建造者模式（Builder Pattern）：将一个复杂对象的构建过程与其表示分离，使得同样的构建过程可以创建不同的表示。

它属于 创建型设计模式，适合构建过程复杂、参数多的对象
*/

/*
现实中的建造者模式应用
C++/Java 中的 StringBuilder, HttpRequest.Builder

游戏角色构建器、配置加载器、日志格式器

protobuf / JSON 序列化构建器
*/

// 简写版本
/*
class ChainBuilder {
private:
    Computer* computer = new Computer();

public:
    ChainBuilder& setCPU(const std::string& cpu) {
        computer->cpu = cpu;
        return *this;
    }

    ChainBuilder& setGPU(const std::string& gpu) {
        computer->gpu = gpu;
        return *this;
    }

    ChainBuilder& setMemory(const std::string& memory) {
        computer->memory = memory;
        return *this;
    }

    ChainBuilder& setStorage(const std::string& storage) {
        computer->storage = storage;
        return *this;
    }

    Computer* build() {
        return computer;
    }
};

int main() {
    Computer* pc = ChainBuilder()
                .setCPU("i7")
                .setGPU("RTX 3060")
                .setMemory("16GB")
                .setStorage("1TB SSD")
                .build();
    pc->show();
    delete pc;
    return 0;
}
*/

// 一句话总结 建造者模式 = 分步骤构建复杂对象，让构建过程与表示解耦。