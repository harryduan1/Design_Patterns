#include <iostream>

class CPU {
public:
    void freeze() {
        std::cout << "CPU: freeze\n";
    }

    void jump(long position) {
        std::cout << "CPU: jump to " << position << "\n";
    }

    void execute() {
        std::cout << "CPU: execute\n";
    }
};

class Memory {
public:
    void load(long position, const std::string& data) {
        std::cout << "Memory: loading \"" << data << "\" to position " << position << "\n";
    }
};

class HardDrive {
public:
    std::string read(long lba, int size) {
        std::cout << "HardDrive: reading " << size << " bytes at " << lba << "\n";
        return "OS Boot Data";
    }
};

class ComputerFacade {
private:
    CPU cpu;
    Memory memory;
    HardDrive hardDrive;

public:
    void start() {
        std::cout << "Starting computer...\n";
        cpu.freeze();
        std::string bootData = hardDrive.read(0, 1024);
        memory.load(0, bootData);
        cpu.jump(0);
        cpu.execute();
    }
};

int main() {
    ComputerFacade computer;
    computer.start();  // 一行调用，隐藏了复杂子系统
    return 0;
}

// 输出结果
/*
Starting computer...
CPU: freeze
HardDrive: reading 1024 bytes at 0
Memory: loading "OS Boot Data" to position 0
CPU: jump to 0
CPU: execute
*/

// 定义：外观模式（Facade Pattern）：为子系统中的一组接口提供一个统一的高层接口，使得子系统更容易使用。它属于结构型设计模式。

/*
现实中的外观模式应用
操作系统开机流程封装成一个 boot() 函数

游戏引擎中的 Game::Init() 封装多个子模块初始化

嵌入式驱动中，Camera::Start() 封装了 Sensor、ISP、BUF 等
*/

// 外观模式 = 简化接口的“总控室”，对外统一出口，对内多通道调度。