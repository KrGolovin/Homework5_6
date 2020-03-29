//
// Created by Macbook Pro on 29/03/2020.
//

#ifndef HOMEWORK5_6_QUEUELIST_H
#define HOMEWORK5_6_QUEUELIST_H
#include "Queue.h"
#include "exceptions.h"

//==============================================================
// Шаблон класса QueueArray - реализация ограниченной очереди.
// Элементы очереди помещаются в массив.
//==============================================================
template<class T>
class QueueList : public Queue<T> {
public:
  QueueList() = default;
  QueueList(const QueueList<T> &src);

  virtual ~QueueList();

  void enQueue(const T &e);

  const T &deQueue();

  bool isEmpty() { return head_ == nullptr; }

private:
  class Elem {
  public:
    explicit Elem(T value, Elem* next = nullptr) : value(value), next (next){}
    T value;
    Elem* next;
  };
  Elem* head_ = nullptr;
  Elem* tail_ = nullptr;
};


template<class T>
QueueList<T>::QueueList(const QueueList<T> &src) {
  if (!src.isEmpty()) {
    for (QueueList<T>::Elem * curr = src.head_; curr != nullptr; ++curr) {
      enQueue(curr->value);
    }
  }
}

template<class T>
void QueueList<T>::enQueue(const T &e) {
  if (isEmpty()) {
    tail_ = new Elem(e);
    head_ = tail_;
  } else {
    tail_->next = new Elem(e);
    tail_ = tail_->next;
  }
}

template<class T>
const T &QueueList<T>::deQueue() {
  if (isEmpty())
    throw QueueUnderflow(); // очередь пуста
  T ans = head_->value;
  QueueList<T>::Elem * tmp = head_->next;
  delete (head_);
  head_ = tmp;
  tail_ = (head_ == nullptr) ? nullptr : tail_;
  return ans;
}

template<class T>
QueueList<T>::~QueueList() {
  while (head_ != nullptr) {
    deQueue();
  }
}

#endif //HOMEWORK5_6_QUEUELIST_H
