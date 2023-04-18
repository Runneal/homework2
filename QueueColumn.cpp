#include <iostream>
#include "Vector.h"
#include <deque>
#include <random>

// 定义存储柱子的索引和高度的结构体
struct Column {
    int index;
    int height;
};

// 定义一个队列类，用来存储柱子
class Queue {
private:
    std::deque<Column> data; 
public:
    // 判断队列是否为空
    bool isEmpty() {
        return data.empty();
    }

    // 返回队列的大小
    int size() {
        return data.size();
    }

    // 插入柱子
    void push(Column column) {
        data.push_back(column);
    }

    // 弹出柱子
    Column pop() {
        Column front = data.front();
        data.pop_front();
        return front;
    }

    // 返回队首的柱子，但不删除它
    Column peek() {
        return data.front();
    }
};
// 定义一个函数，用来计算矩形的最大面积
int maxRectangle(std::vector<int>& heights) {
    int maxrectangle = 0; 
    Queue stack; 
    for (int i = 0; i < heights.size(); i++) { 
        while (!stack.isEmpty() && heights[i] < stack.peek().height) { 
            Column top = stack.pop(); 
            int width = stack.isEmpty() ? i : i - stack.peek().index - 1; 
            int area = top.height * width; 
            maxrectangle = std::max(maxrectangle, area); 
        }
        stack.push(Column{ i, heights[i] }); 
    }
    while (!stack.isEmpty()) { 
        Column top = stack.pop(); 
        int width = stack.isEmpty() ? heights.size() : heights.size() - stack.peek().index - 1; 
        int area = top.height * width; 
        maxrectangle = std::max(maxrectangle, area); 
    }
    return maxrectangle; // 返回最大面积
}
// 生成随机数
int random(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> dis(min, max); 
    return dis(gen); // 返回一个在[min, max]范围内的随机数
}

// 打印柱子数组和最大面积
void print(std::vector<int>& heights) {
    std::cout << "柱子高度分别为: \n[";
    for (int i = 0; i < heights.size(); i++) {
        std::cout << heights[i];
        if (i != heights.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]\n";
    std::cout << "最大面积为: " << maxRectangle(heights) << "\n\n";
}

// 测试数据的个数
const int p = 10;

// 柱子数组长度的最小值和最大值
const int MIN_L = 1;
const int MAX_L = 105;
// 柱子高度的最小值和最大值
const int MIN_H = 0;
const int MAX_H = 104;

//生成测试数据并调用打印函数
int main() {
    for (int i = 0; i < p; i++) { // 循环生成p组测试数据
        int length = random(MIN_L, MAX_L); // 区间内随机生成柱子数组长度
        std::vector<int> heights(length); // 创建一个长度为length的柱子数组
        for (int j = 0; j < length; j++) { // 遍历柱子数组
            heights[j] = random(MIN_H, MAX_H); // 随机生成柱子高度
        }
        print(heights);
    }
    return 0; 
}