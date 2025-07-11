#include <iostream>
#include <string>
#include <memory>

// 日志级别
enum LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

// 抽象处理者类
class Logger {
protected:
    std::shared_ptr<Logger> nextLogger;

public:
    void setNext(std::shared_ptr<Logger> next) {
        nextLogger = next;
    }

    void handle(LogLevel level, const std::string& message) {
        if (canHandle(level)) {
            write(message);
        } else if (nextLogger) {
            nextLogger->handle(level, message);
        } else {
            std::cout << "No handler for log level.\n";
        }
    }

    virtual bool canHandle(LogLevel level) = 0;
    virtual void write(const std::string& message) = 0;
    virtual ~Logger() = default;
};

// 具体处理者：处理 ERROR 级别日志
class ErrorLogger : public Logger {
public:
    bool canHandle(LogLevel level) override {
        return level == ERROR;
    }

    void write(const std::string& message) override {
        std::cout << "[ERROR]: " << message << std::endl;
    }
};

// 具体处理者：处理 WARNING 级别日志
class WarningLogger : public Logger {
public:
    bool canHandle(LogLevel level) override {
        return level == WARNING;
    }

    void write(const std::string& message) override {
        std::cout << "[WARNING]: " << message << std::endl;
    }
};

// 具体处理者：处理 INFO 级别日志
class InfoLogger : public Logger {
public:
    bool canHandle(LogLevel level) override {
        return level == INFO;
    }

    void write(const std::string& message) override {
        std::cout << "[INFO]: " << message << std::endl;
    }
};

// 具体处理者：处理 DEBUG 级别日志
class DebugLogger : public Logger {
public:
    bool canHandle(LogLevel level) override {
        return level == DEBUG;
    }

    void write(const std::string& message) override {
        std::cout << "[DEBUG]: " << message << std::endl;
    }
};

// 测试
int main() {
    // 创建处理者对象
    auto debugLogger = std::make_shared<DebugLogger>();
    auto infoLogger = std::make_shared<InfoLogger>();
    auto warningLogger = std::make_shared<WarningLogger>();
    auto errorLogger = std::make_shared<ErrorLogger>();

    // 设置职责链：Debug → Info → Warning → Error
    debugLogger->setNext(infoLogger);
    infoLogger->setNext(warningLogger);
    warningLogger->setNext(errorLogger);

    // 发出不同级别的日志请求
    debugLogger->handle(DEBUG, "This is a debug message");
    debugLogger->handle(INFO, "This is an info message");
    debugLogger->handle(WARNING, "This is a warning message");
    debugLogger->handle(ERROR, "This is an error message");

    return 0;
}

// 输出结果
/*
[DEBUG]: This is a debug message
[INFO]: This is an info message
[WARNING]: This is a warning message
[ERROR]: This is an error message
*/