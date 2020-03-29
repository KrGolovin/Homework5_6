//
// Created by Macbook Pro on 10/12/2019.
//

#pragma once
#include "string.h"
using namespace std;
template <class T>
class Elem
{
public:
    Elem(T, Elem<T>*);
    Elem<T>* & getPrev();
    void setValue(T value);
    void setPrev(Elem<T> *);
    T getValue() const;
private:
    Elem<T>* prev_;
    T value_;

};

template <class T>
Elem<T>::Elem(T value, Elem<T>* prev):value_(value), prev_(prev) {}

template <class T>
Elem<T>* & Elem<T>::getPrev() {
    return prev_;
}

template <class T>
void Elem<T>::setValue(T value) {
    value_ = value;
}

template <class T>
void Elem<T>::setPrev(Elem<T>* prev) {
    prev_ = prev;
}

template <class T>
T Elem<T>::getValue() const {
    return value_;
}



