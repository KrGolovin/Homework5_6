//
// Created by Macbook Pro on 19/02/2020.
//

#ifndef STACK_STACKLIST_H
#define STACK_STACKLIST_H

#include "Stack.h"
#include "exceptions.h"
#include "List.h"
template <class T>
class StackList : public Stack<T>
{
public:
    StackList(); // size задает размер стека "по умолчанию"
    StackList(const StackList<T>& src);
    virtual ~StackList();
    void push(const T& e);
    const T& pop();
    bool isEmpty() { return list_.getTail() == nullptr;}
private:
    List<T> list_;     // массив элементов стека:
};

template<class T>
StackList<T>::StackList() {
}

template<class T>
StackList<T>::StackList(const StackList<T> &src) {
    while (!src.isEmpty()) {
        list_ += src.pop();
    }
}

template<class T>
StackList<T>::~StackList() {
}

template<class T>
void StackList<T>::push(const T &e) {
    list_ += e;
}

template<class T>
const T &StackList<T>::pop() {
    if (isEmpty()) {
        throw StackUnderflow();
    }
    Elem<T>* tmp = list_.getTail();
    T value = tmp->getValue();
    list_.getTail() = list_.getTail()->getPrev();
    delete(tmp);
    return  value;
}

#endif //STACK_STACKLIST_H
