#pragma once

#define SIZE 100 // defining stack size.

template<typename T>
class Stack
{
    T* arr;
    int top;
    int capacity;

public:
    Stack(int size = SIZE);
    ~Stack();

    void push(T info);
    T pop();
    T peek();
    int size();
    bool isEmpty();
    bool isFull();
};

template<typename T>
Stack<T>::Stack(int size)
{
    arr = new T[size];
    capacity = size;
    top = -1;
}

template<typename T>
Stack<T>::~Stack() {
    delete[] arr;
}

template<typename T>
void Stack<T>::push(T x)
{
    if (isFull())
    {
        std::cout << "Stack Overflow\n";
        exit(EXIT_FAILURE);
    }
    arr[++top] = x;
}

template<typename T>
T Stack<T>::pop()
{
    if (isEmpty())
    {
        std::cout << "Stack Underflow\n";
        exit(EXIT_FAILURE);
    }
    return arr[top--];
}

template<typename T>
T Stack<T>::peek()
{
    if (!isEmpty()) {
        return arr[top];
    }
    else {
        std::cout << "Stack is empty...\n";
        exit(EXIT_FAILURE);
    }
}

template<typename T>
int Stack<T>::size() {
    return top + 1;
}

template<typename T>
bool Stack<T>::isEmpty() {
    return top == -1;
}

template<typename T>
bool Stack<T>::isFull() {
    return top == capacity - 1;
}