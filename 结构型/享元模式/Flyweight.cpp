#include <iostream>
#include <string>
#include <map>
#include <memory>

/*
示例场景：围棋棋子池
棋盘上有很多“黑子”和“白子”，它们颜色相同但位置不同。我们可以将颜色相同的棋子作为共享对象，通过位置等外部状态来区分，从而节省内存。
*/

// 抽象享元类
class ChessPiece {
public:
    virtual void display(int x, int y) = 0; // 外部状态：位置
    virtual ~ChessPiece() = default;
};

// 具体享元类（共享对象）
class BlackChess : public ChessPiece {
public:
    void display(int x, int y) override {
        std::cout << "Black Chess at (" << x << ", " << y << ")\n";
    }
};

class WhiteChess : public ChessPiece {
public:
    void display(int x, int y) override {
        std::cout << "White Chess at (" << x << ", " << y << ")\n";
    }
};

// 享元工厂：管理共享对象
class ChessFactory {
private:
    std::map<std::string, std::shared_ptr<ChessPiece>> chessMap;

public:
    std::shared_ptr<ChessPiece> getChess(const std::string& color) {
        auto it = chessMap.find(color);
        if (it != chessMap.end()) {
            return it->second;
        }

        std::shared_ptr<ChessPiece> chess;
        if (color == "black") {
            chess = std::make_shared<BlackChess>();
        } else if (color == "white") {
            chess = std::make_shared<WhiteChess>();
        } else {
            throw std::invalid_argument("Unknown color");
        }

        chessMap[color] = chess;
        return chess;
    }
};

// 测试代码
int main() {
    ChessFactory factory;

    auto black1 = factory.getChess("black");
    auto black2 = factory.getChess("black");
    auto white1 = factory.getChess("white");

    // 共享对象 + 外部状态（位置）
    black1->display(1, 2);
    black2->display(3, 5);
    white1->display(4, 4);

    // 检查共享：black1 和 black2 是否是同一个对象
    std::cout << "black1 and black2 are " << (black1 == black2 ? "the same" : "different") << " object.\n";

    return 0;
}

// 输出结果
/*
Black Chess at (1, 2)
Black Chess at (3, 5)
White Chess at (4, 4)
black1 and black2 are the same object.
*/