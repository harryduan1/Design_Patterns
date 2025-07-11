#include <iostream>
#include <string>
#include <vector>
#include <memory>

class FileSystemEntity {
public:
    virtual void display(int indent = 0) const = 0;
    virtual void add(std::shared_ptr<FileSystemEntity> entity) {
        // 默认不支持添加
    }
    virtual ~FileSystemEntity() = default;
};

class File : public FileSystemEntity {
private:
    std::string name;

public:
    explicit File(const std::string& name) : name(name) {}

    void display(int indent = 0) const override {
        std::cout << std::string(indent, ' ') << "- File: " << name << "\n";
    }
};

class Directory : public FileSystemEntity {
private:
    std::string name;
    std::vector<std::shared_ptr<FileSystemEntity>> children;

public:
    explicit Directory(const std::string& name) : name(name) {}

    void add(std::shared_ptr<FileSystemEntity> entity) override {
        children.push_back(entity);
    }

    void display(int indent = 0) const override {
        std::cout << std::string(indent, ' ') << "+ Dir: " << name << "\n";
        for (const auto& child : children) {
            child->display(indent + 4);  // 缩进
        }
    }
};

int main() {
    auto root = std::make_shared<Directory>("root");
    auto bin = std::make_shared<Directory>("bin");
    auto etc = std::make_shared<Directory>("etc");
    auto home = std::make_shared<Directory>("home");

    root->add(bin);
    root->add(etc);
    root->add(home);

    bin->add(std::make_shared<File>("ls"));
    bin->add(std::make_shared<File>("cat"));

    etc->add(std::make_shared<File>("config.ini"));

    auto user = std::make_shared<Directory>("user");
    user->add(std::make_shared<File>("readme.txt"));
    home->add(user);

    root->display();

    return 0;
}

// Output:
/*
+ Dir: root
    + Dir: bin
        - File: ls
        - File: cat
    + Dir: etc
        - File: config.ini
    + Dir: home
        + Dir: user
            - File: readme.txt
*/

/*
定义：组合模式（Composite Pattern）：将对象组合成树形结构以表示“部分-整体”的层次结构。
使得用户对单个对象和组合对象的使用具有一致性。

它属于 结构型设计模式。
*/

/*
一句话总结
组合模式 = 把“单个对象”和“对象集合”抽象为统一类型，支持递归结构的统一操作。
*/