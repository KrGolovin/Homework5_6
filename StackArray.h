//
// Created by Macbook Pro on 19/02/2020.
//

#ifndef STACK_STACKARRAY_H
#define STACK_STACKARRAY_H

#include "exceptions.h"
#include "Stack.h"
template <class T>
class StackArray : public Stack<T>
{
public:
    StackArray(int size = 100); // size задает размер стека "по умолчанию"
    StackArray(const StackArray<T>& src);
    virtual ~StackArray() { delete[] array_; }
    void push(const T& e);
    const T& pop();
    bool isEmpty() { return top_ == 0; }
private:
    T* array_;     // массив элементов стека:
    int top_ = 0;  // вершина стека, элемент занесенный в стек последним
    int size_;     // размер стека
};

template <class T>
StackArray<T>::StackArray(int size) {
    try {
        array_ = new T[size_ = size];// пытаемся заказать память под элементы
    }
    catch (...) {                // если что-то случилось (например, размер слишком
        throw WrongStackSize(); // или отрицательный) - возникает исключительная top_ = 0;
        //3. Используя базовый класс exception, описанный в заголовочном файле exception, создать свой класс WrongStackSize для работы с исключительной ситуацией, которая может возникнуть, если в конструкторе стека, реализуемого через массив, неправильно задан размер.
    }
    //4. На основе шаблона для абстрактного типа стек создать шаблон для реализации
    //структуры данных ограниченный стек (через массив).
    //ситуация
}

template <class T>
StackArray<T>::StackArray(const StackArray<T>& src) {
    try {
        array_ = new T[size_ = src.size_];
    }
    catch (...) {
        throw WrongStackSize();
    }
    // копирование массива
    for (int i = 0; i < src.top_; i++) {
        array_[i] = src.array_[i];
    }
    top_ = src.top_;
}
template <class T>
void StackArray<T>::push(const T& e) {
    if (top_ == size_)
        throw StackOverflow(); // нет места для нового элемента
    top_++;
    array_[top_] = e;
}
// занесение элемента в стек
template <class T>
const T& StackArray<T>::pop()
{
    if (top_ == 0)
        throw StackUnderflow(); // стек пуст
    return array_[top_--];  // Элемент физически остается в стеке, но больше "не
}
#endif //STACK_STACKARRAY_H
