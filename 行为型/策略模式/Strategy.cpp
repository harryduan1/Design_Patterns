#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

// 抽象策略类
class SortStrategy {
public:
    virtual void sort(std::vector<int>& data) = 0;
    virtual ~SortStrategy() {}
};

// 具体策略：冒泡排序
class BubbleSort : public SortStrategy {
public:
    void sort(std::vector<int>& data) override {
        std::cout << "Using Bubble Sort...\n";
        for (size_t i = 0; i < data.size(); ++i) {
            for (size_t j = 0; j < data.size() - i - 1; ++j) {
                if (data[j] > data[j+1]) {
                    std::swap(data[j], data[j+1]);
                }
            }
        }
    }
};

// 具体策略：快速排序
class QuickSort : public SortStrategy {
public:
    void sort(std::vector<int>& data) override {
        std::cout << "Using Quick Sort...\n";
        quicksort(data, 0, data.size() - 1);
    }

private:
    void quicksort(std::vector<int>& data, int left, int right) {
        if (left >= right) return;
        int pivot = data[right];
        int partitionIndex = left;
        for (int i = left; i < right; ++i) {
            if (data[i] < pivot) {
                std::swap(data[i], data[partitionIndex++]);
            }
        }
        std::swap(data[partitionIndex], data[right]);
        quicksort(data, left, partitionIndex - 1);
        quicksort(data, partitionIndex + 1, right);
    }
};

// 上下文类：持有一个策略
class SortContext {
private:
    std::unique_ptr<SortStrategy> strategy;
public:
    void setStrategy(SortStrategy* s) {
        strategy.reset(s);
    }

    void executeStrategy(std::vector<int>& data) {
        if (strategy) {
            strategy->sort(data);
        } else {
            std::cout << "No sorting strategy set!\n";
        }
    }
};

// 测试主程序
int main() {
    std::vector<int> data = {10, 3, 5, 8, 2, 7};

    SortContext context;

    // 使用冒泡排序
    context.setStrategy(new BubbleSort());
    std::vector<int> data1 = data;
    context.executeStrategy(data1);
    for (int num : data1) std::cout << num << " ";
    std::cout << "\n";

    // 使用快速排序
    context.setStrategy(new QuickSort());
    std::vector<int> data2 = data;
    context.executeStrategy(data2);
    for (int num : data2) std::cout << num << " ";
    std::cout << "\n";

    return 0;
}

// 输出结果：
// Using Bubble Sort...
// 2 3 5 7 8 10 
// Using Quick Sort...
// 2 3 5 7 8 10 

// 策略模式（Strategy Pattern）是一种行为型设计模式，它允许你定义一系列算法（策略），
// 将每个算法封装到独立的类中，并使它们可以互换使用，避免在客户端写大量 if-else 或 switch 分支。