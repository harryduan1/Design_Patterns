#include <iostream>
#include <string>
#include <vector>

class Memento {
private:
    std::string state;

public:
    explicit Memento(const std::string& s) : state(s) {}
    std::string getState() const { return state; }
};

class Editor {
private:
    std::string text;

public:
    void setText(const std::string& s) {
        text = s;
        std::cout << "Text set to: " << text << "\n";
    }

    std::string getText() const {
        return text;
    }

    Memento* save() {
        return new Memento(text);
    }

    void restore(Memento* m) {
        text = m->getState();
        std::cout << "Restored to: " << text << "\n";
    }
};

class History {
private:
    std::vector<Memento*> history;

public:
    void push(Memento* m) {
        history.push_back(m);
    }

    Memento* pop() {
        if (history.empty()) return nullptr;
        Memento* m = history.back();
        history.pop_back();
        return m;
    }

    ~History() {
        for (auto m : history) delete m;
    }
};

int main() {
    Editor editor;
    History history;

    editor.setText("Hello");
    history.push(editor.save());  // 保存1

    editor.setText("Hello, world!");
    history.push(editor.save());  // 保存2

    editor.setText("Hello, world!!!");

    std::cout << "Now: " << editor.getText() << "\n";

    // 撤销一次
    editor.restore(history.pop());

    // 撤销第二次
    editor.restore(history.pop());

    return 0;
}

// Output:
/*
Text set to: Hello
Text set to: Hello, world!
Text set to: Hello, world!!!
Now: Hello, world!!!
Restored to: Hello, world!
Restored to: Hello
*/

// 定义：备忘录模式（Memento Pattern）：在不破坏封装性的前提下，捕获一个对象的内部状态，并在以后将其恢复到这个状态。
// 它属于 行为型设计模式。

// 一句话总结 备忘录模式 = 快照 + 恢复机制，解耦历史管理与对象本体。