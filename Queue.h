//
// Created by Macbook Pro on 29/03/2020.
//

#ifndef HOMEWORK5_6_QUEUE_H
#define HOMEWORK5_6_QUEUE_H

// =============================================================
// Шаблон класса Queue представляет понятие абстрактного очередь
//==============================================================
template<class T>
class Queue {
public:
  virtual ~Queue() {}// Виртуальный - для переопределения
// Абстрактные операции со стеком
  virtual void enQueue(const T &e) = 0; // Добавление элемента в стек
  virtual const T &deQueue() = 0;// Удаление и возвращение верхнего элемента.
  // Если элементов нет, может возникнуть QueuekUnderflow
  virtual bool isEmpty() = 0; // Проверка на пустоту
};

#endif //HOMEWORK5_6_QUEUE_H
