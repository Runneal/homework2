#include <iostream>
#include <cstdlib>
#include <cstdio>
template<typename T>
class Queue {
private:
    T* queue;     // ���е�����
    int front;    // ��ͷָ��
    int rear;     // ��βָ��
    int capacity; // ��������
public:

    // ���캯��
    Queue(int cap) : front(0), rear(0), capacity(cap) {
        queue = new T[cap]; // ��̬��������ռ�
    }

    // ��������
    ~Queue() {
        delete[] queue; // �ͷ�����ռ�
    }

    // �ж϶����Ƿ�Ϊ��
    bool isEmpty() {
        return front == rear;
    }

    // �ж϶����Ƿ���
    bool isFull() {
        return (rear + 1) % capacity == front;
    }

    // ��ȡ��ͷԪ��
    T& Front() {
        if (isEmpty()) {
            std::cout<<"Queue is empty"<< std::endl;
            exit(-1);
        }
        return queue[front];
    }

    // ��ȡ��βԪ��
    T& back() {
        if (isEmpty()) {
            std::cout << "Queue is empty" << std::endl;
            std::exit(-1);
        }
        return queue[rear-1];
    }

    // ���һ��Ԫ��
    void enqueue(T element) {
        if (isFull()) {
            std::cout << "Queue is full" << std::endl;
            exit(-1);
        }
        queue[rear] = element; // ��Ԫ�ظ�ֵ�������ж�βָ����ָ���λ��
        rear = (rear + 1) % capacity; // ����βָ���һ�������ȡģ
    }

    // ����һ��Ԫ��
    T dequeue() {
        if (isEmpty()) {
            std::cout << "Queue is empty" << std::endl;
            std::exit(-1);
        }
        T front_value = queue[front]; // ��ȡ�����ж�ͷָ����ָ���Ԫ��
        front = (front + 1) % capacity; // ����ͷָ���һ�������ȡģ
        return front_value; // ���س���Ԫ��
    }

};
