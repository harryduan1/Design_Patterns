#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>

/*
解析和计算简单的加法表达式（如 "5 + 10 + 20"）
解释器模式通常用于实现语言解释器、公式求值器、命令解析器等。
*/

// 抽象表达式
class Expression {
public:
    virtual int interpret() = 0;
    virtual ~Expression() = default;
};

// 终结符表达式：数字
class NumberExpression : public Expression {
private:
    int number;
public:
    explicit NumberExpression(int num) : number(num) {}
    int interpret() override {
        return number;
    }
};

// 非终结符表达式：加法
class AddExpression : public Expression {
private:
    std::shared_ptr<Expression> left;
    std::shared_ptr<Expression> right;
public:
    AddExpression(std::shared_ptr<Expression> l, std::shared_ptr<Expression> r)
        : left(std::move(l)), right(std::move(r)) {}

    int interpret() override {
        return left->interpret() + right->interpret();
    }
};

// 解析器（构建 AST）
class Interpreter {
public:
    // 将字符串解析为表达式树，支持 a + b + c 形式
    std::shared_ptr<Expression> parse(const std::string& expr) {
        std::istringstream iss(expr);
        std::string token;
        std::shared_ptr<Expression> result = nullptr;

        while (iss >> token) {
            if (token == "+") {
                std::string rightStr;
                iss >> rightStr;
                int num = std::stoi(rightStr);
                auto right = std::make_shared<NumberExpression>(num);
                result = std::make_shared<AddExpression>(result, right);
            } else {
                int num = std::stoi(token);
                result = std::make_shared<NumberExpression>(num);
            }
        }

        return result;
    }
};

// 测试
int main() {
    Interpreter interpreter;
    std::string expression = "5 + 10 + 20";
    auto tree = interpreter.parse(expression);

    std::cout << "Expression: " << expression << std::endl;
    std::cout << "Result: " << tree->interpret() << std::endl;

    return 0;
}

// 输出结果
/*
Expression: 5 + 10 + 20
Result: 35
*/