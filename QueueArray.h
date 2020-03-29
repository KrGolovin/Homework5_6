//
// Created by Macbook Pro on 29/03/2020.
//

#ifndef HOMEWORK5_6_QUEUEARRAY_H
#define HOMEWORK5_6_QUEUEARRAY_H

#include "Queue.h"
#include "exceptions.h"

//==============================================================
// Шаблон класса QueueArray - реализация ограниченной очереди.
// Элементы очереди помещаются в массив.
//==============================================================
template<class T>
class QueueArray : public Queue<T> {
public:
  QueueArray(int size = 100); // size задает размер "по умолчанию"
  QueueArray(const QueueArray<T> &src);

  virtual ~QueueArray() { delete[] array_; }

  void enQueue(const T &e);

  const T &deQueue();

  bool isEmpty() { return head_ == tail_; }

  int sizeInQueue() const {
    if (head_ > tail_) {
      return size_ - head_ + tail_;
    }
    else  {
      return tail_ - head_;
    }
  }

private:
  T *array_; // массив элементов очереди
  int head_ = 1; // Очередь пуста, если head[Q] = tail[Q].
  int tail_ = 1; // Первоначально: head[Q] = tail[Q] = 1;
  int size_; // размер очереди
};

template<class T>
QueueArray<T>::QueueArray(int size) {
  try {
    array_ = new T[size_ = size];// пытаемся заказать память под элементы
  } catch (...) { // если что-то случилось (например, размер слишком большой
    throw WrongQueueSize(); // или отрицательный) - возникает искл.ситуация
  }
  head_ = 1;
  tail_ = 1;
}

template<class T>
QueueArray<T>::QueueArray(const QueueArray<T> &src) {
  try {
    array_ = new T[size_ = src.size_];
  } catch (...) {
    throw WrongQueueSize();
  }
  for (int i = src.head_; i != src.tail_; i = (i + 1) % src.size_) {
    enQueue(src.array_[i]);
  }
}

template<class T>
void QueueArray<T>::enQueue(const T &e) {
  if (head_ == tail_ + 1)
    throw QueueOverflow(); // нет места для нового элемента
  array_[tail_] = e;
  tail_ = (tail_ + 1) % size_;
}

template<class T>
const T &QueueArray<T>::deQueue() {
  if (head_ == tail_)
    throw QueueUnderflow(); // очередь пуста
  T ans = array_[head_];
  head_ = (head_ + 1) % size_;
  return ans;
}



#endif //HOMEWORK5_6_QUEUEARRAY_H
