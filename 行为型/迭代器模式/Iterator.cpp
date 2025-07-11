#include <iostream>
#include <vector>
#include <string>

template <typename T>
class Iterator {
public:
    virtual bool hasNext() const = 0;
    virtual T next() = 0;
    virtual ~Iterator() = default;
};

template <typename T>
class Aggregate {
public:
    virtual Iterator<T>* createIterator() = 0;
    virtual ~Aggregate() = default;
};

class StringList : public Aggregate<std::string> {
private:
    std::vector<std::string> data;

public:
    void add(const std::string& str) {
        data.push_back(str);
    }

    std::string get(int index) const {
        return data[index];
    }

    int size() const {
        return static_cast<int>(data.size());
    }

    // 声明迭代器类为友元，以便访问私有成员
    friend class StringListIterator;

    Iterator<std::string>* createIterator() override;
};

class StringListIterator : public Iterator<std::string> {
private:
    const StringList& list;
    int index = 0;

public:
    explicit StringListIterator(const StringList& l) : list(l) {}

    bool hasNext() const override {
        return index < list.size();
    }

    std::string next() override {
        return list.get(index++);
    }
};

Iterator<std::string>* StringList::createIterator() {
    return new StringListIterator(*this);
}

int main() {
    StringList list;
    list.add("Apple");
    list.add("Banana");
    list.add("Cherry");

    Iterator<std::string>* it = list.createIterator();
    while (it->hasNext()) {
        std::cout << it->next() << "\n";
    }

    delete it;  // 释放迭代器资源
    return 0;
}

// 输出结果
/*
Apple
Banana
Cherry
*/

/*
定义：迭代器模式：提供一种方法顺序访问一个聚合对象中各个元素，而不暴露该对象的内部表示。

它属于 行为型设计模式。
*/

// 一句话总结 迭代器模式 = 将遍历行为从容器结构中抽离出来，支持一致性访问。

