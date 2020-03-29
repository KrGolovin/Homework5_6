//
// Created by Macbook Pro on 29/03/2020.
//

#ifndef HOMEWORK5_6_EXCEPTIONS_H
#define HOMEWORK5_6_EXCEPTIONS_H

#include <exception>

//========================================================================
// Классы QueueOverflow и QueueUnderflow представляют две основные
// исключительные ситуации, которые могут возникнуть при работе с очередью
//========================================================================
class QueueOverflow : public std::exception {
public:
  QueueOverflow() : reason("Queue Overflow") {}

  const char *what() const noexcept override { return reason; }

private:
  const char *reason; // ! const
};

class QueueUnderflow : public std::exception {
public:
  QueueUnderflow() : reason("Queue Underflow") {}

  const char *what() const noexcept override { return reason; }

private:
  const char *reason; // ! const
};

class WrongQueueSize : public std::exception {
public:
  WrongQueueSize() : reason("Wrong Queue Size") {}

  const char *what() const noexcept override { return reason; }

private:
  const char *reason; // ! const
};

class StackOverflow : public std::exception
{
public:
  StackOverflow() : reason("Stack Overflow") {}
  const char* what() const noexcept { return reason; }
private:
  const char* reason;  // ! const
};

class StackUnderflow : public std::exception
{
public:
  StackUnderflow() : reason("Stack Underflow") {}
  const char* what() const noexcept { return reason; }
private:
  const char* reason;  // ! const
};

class WrongStackSize : public std::exception {
public:
  WrongStackSize() : reason("Wrong Stack Size") {}

  const char *what() const noexcept { return reason; }

private:
  const char *reason;  // ! const
};

#endif //HOMEWORK5_6_EXCEPTIONS_H
