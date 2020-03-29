//
// Created by Macbook Pro on 06/02/2020.
//

#ifndef UNTITLED5_LIST_H
#define UNTITLED5_LIST_H

#include <iostream>
#include "Elem.h"
template <class T>
class List {
public:
    List();
    List(List<T> &&);
    ~List();
    void operator+=(T);
    Elem<T>* & getTail();

private:

    //Elem<T>* head_;
    Elem<T>* tail_;

};

template<class T>
List<T>::List(): tail_(nullptr){
}

template<class T>
List<T>::List(List<T> && second): tail_(second.tail_) {
    second.tail_ = nullptr;
}

template<class T>
List<T>::~List() {
    while(tail_ != nullptr) {
        Elem<T> * curr = tail_;
        tail_ = tail_->getPrev();
        delete(curr);
    }
}

template<class T>
void List<T>::operator+=(T value) {
    Elem<T>* tmp = new Elem<T>(value, tail_);
    tail_ = tmp;
}

template<class T>
Elem<T>* & List<T>::getTail() {
    return tail_;
}

#endif //UNTITLED5_LIST_H
