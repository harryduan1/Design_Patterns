#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>

// 预声明
class User;

// 抽象中介者
class ChatMediator {
public:
    virtual void sendMessage(const std::string& message, User* sender) = 0;
    virtual void addUser(User* user) = 0;
    virtual ~ChatMediator() = default;
};

// 抽象同事类
class User {
protected:
    ChatMediator* mediator;
    std::string name;

public:
    User(ChatMediator* med, const std::string& uname) : mediator(med), name(uname) {}
    virtual void send(const std::string& message) = 0;
    virtual void receive(const std::string& message, const std::string& from) = 0;
    std::string getName() const { return name; }
    virtual ~User() = default;
};

// 具体中介者：聊天室
class ChatRoom : public ChatMediator {
private:
    std::vector<User*> users;

public:
    void addUser(User* user) override {
        users.push_back(user);
    }

    void sendMessage(const std::string& message, User* sender) override {
        for (User* user : users) {
            if (user != sender) {
                user->receive(message, sender->getName());
            }
        }
    }
};

// 具体同事类
class ConcreteUser : public User {
public:
    ConcreteUser(ChatMediator* med, const std::string& uname) : User(med, uname) {}

    void send(const std::string& message) override {
        std::cout << "[" << name << "] 发送消息: " << message << std::endl;
        mediator->sendMessage(message, this);
    }

    void receive(const std::string& message, const std::string& from) override {
        std::cout << "[" << name << "] 接收到来自 [" << from << "] 的消息: " << message << std::endl;
    }
};

// 测试代码
int main() {
    ChatRoom chatRoom;

    ConcreteUser user1(&chatRoom, "Alice");
    ConcreteUser user2(&chatRoom, "Bob");
    ConcreteUser user3(&chatRoom, "Charlie");

    chatRoom.addUser(&user1);
    chatRoom.addUser(&user2);
    chatRoom.addUser(&user3);

    user1.send("Hello everyone!");
    user2.send("Hi Alice!");
    user3.send("Hey guys!");

    return 0;
}

// 输出结果
/*
[Alice] 发送消息: Hello everyone!
[Bob] 接收到来自 [Alice] 的消息: Hello everyone!
[Charlie] 接收到来自 [Alice] 的消息: Hello everyone!
[Bob] 发送消息: Hi Alice!
[Alice] 接收到来自 [Bob] 的消息: Hi Alice!
[Charlie] 接收到来自 [Bob] 的消息: Hi Alice!
[Charlie] 发送消息: Hey guys!
[Alice] 接收到来自 [Charlie] 的消息: Hey guys!
[Bob] 接收到来自 [Charlie] 的消息: Hey guys!
*/