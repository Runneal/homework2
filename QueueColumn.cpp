#include <iostream>
#include "Vector.h"
#include <deque>
#include <random>

// ����洢���ӵ������͸߶ȵĽṹ��
struct Column {
    int index;
    int height;
};

// ����һ�������࣬�����洢����
class Queue {
private:
    std::deque<Column> data; 
public:
    // �ж϶����Ƿ�Ϊ��
    bool isEmpty() {
        return data.empty();
    }

    // ���ض��еĴ�С
    int size() {
        return data.size();
    }

    // ��������
    void push(Column column) {
        data.push_back(column);
    }

    // ��������
    Column pop() {
        Column front = data.front();
        data.pop_front();
        return front;
    }

    // ���ض��׵����ӣ�����ɾ����
    Column peek() {
        return data.front();
    }
};
// ����һ������������������ε�������
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
    return maxrectangle; // ����������
}
// ���������
int random(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> dis(min, max); 
    return dis(gen); // ����һ����[min, max]��Χ�ڵ������
}

// ��ӡ���������������
void print(std::vector<int>& heights) {
    std::cout << "���Ӹ߶ȷֱ�Ϊ: \n[";
    for (int i = 0; i < heights.size(); i++) {
        std::cout << heights[i];
        if (i != heights.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]\n";
    std::cout << "������Ϊ: " << maxRectangle(heights) << "\n\n";
}

// �������ݵĸ���
const int p = 10;

// �������鳤�ȵ���Сֵ�����ֵ
const int MIN_L = 1;
const int MAX_L = 105;
// ���Ӹ߶ȵ���Сֵ�����ֵ
const int MIN_H = 0;
const int MAX_H = 104;

//���ɲ������ݲ����ô�ӡ����
int main() {
    for (int i = 0; i < p; i++) { // ѭ������p���������
        int length = random(MIN_L, MAX_L); // ��������������������鳤��
        std::vector<int> heights(length); // ����һ������Ϊlength����������
        for (int j = 0; j < length; j++) { // ������������
            heights[j] = random(MIN_H, MAX_H); // ����������Ӹ߶�
        }
        print(heights);
    }
    return 0; 
}