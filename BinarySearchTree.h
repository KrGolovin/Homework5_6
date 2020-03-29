//
// Created by Macbook Pro on 04/03/2020.
//

#ifndef BINARYTREE_BINARYSEARCHTREE_H
#define BINARYTREE_BINARYSEARCHTREE_H

#include <iostream>
#include <algorithm>
#include <stack>
#include "StackList.h"

using namespace std;

//
// Определение шаблона класса BinarySearchTree
//
template<class T>
class BinarySearchTree {
private:
  // Описание структуры узла со ссылками на детей
  struct Node {
    T key_;         // значение ключа, содержащееся в узле
    Node *left_;     // указатель на левое поддерево
    Node *right_;    // указатель на правое поддерево
    Node *p_;        // указатель на  родителя !!! не используется
    // Конструктор узла
    Node(const T &key, Node *left = nullptr, Node *right = nullptr, Node *p = nullptr) : key_(key), left_(left),
                                                                                         right_(right), p_(p) {}

    ~Node() = default;
  };

  // Дерево реализовано в виде указателя на корневой узел.
  Node *root_;
public:

  // Конструктор "по умолчанию" создает пустое дерево
  BinarySearchTree() : root_(nullptr) {

  }

  // Деструктор освобождает память, занятую узлами дерева
  virtual ~BinarySearchTree() {
    deleteSubtree(root_);
  }

  // Печать строкового изображения дерева в выходной поток out
  void print(ostream &out) const {
    printNode(out, root_);
    out << endl;
  }

  // Функция поиска по ключу в бинарном дереве поиска
  bool iterativeSearch(const T &key) const {
    return (iterativeSearchNode(key) != nullptr);
  }

// Вставка нового элемента в дерево, не нарушающая порядка // элементов. Вставка производится в лист дерева
  void insert(const T &key) {
    if (root_ == nullptr) {
      root_ = new Node(key, nullptr, nullptr, nullptr);
      return;
    }
    Node *curr = root_;
    while (curr->key_ != key) {
      if (key < curr->key_) {
        if (curr->left_ == nullptr) {
          curr->left_ = new Node(key, nullptr, nullptr, curr);
          return;
        } else {
          curr = curr->left_;
        }
      } else {
        if (curr->right_ == nullptr) {
          curr->right_ = new Node(key, nullptr, nullptr, curr);
          return;
        } else {
          curr = curr->right_;
        }
      }
    }
    throw "Just is";
  }

  void insertReq(const T &key) {
    if (root_ == nullptr) {
      root_ = new Node(key, nullptr, nullptr, nullptr);
      return;
    }
    insertR(root_, key);
  }

// Удаление элемента из дерева, не нарушающее порядка элементов
  void deleteKey(const T &key) {
    Node *curr = iterativeSearchNode(key);
    if (curr == nullptr) {
      throw "Didn't find key";
    }
    if (curr->right_ == nullptr && curr->left_ == nullptr) { // оба потомка - пустые
      Node *parent = curr->p_;
      if (parent == nullptr) {
        root_ = nullptr;
      } else if (parent->key_ < curr->key_) {
        parent->right_ = nullptr;
      } else {
        parent->left_ = nullptr;
      }
      delete (curr);
    } else if (curr->left_ == nullptr || curr->right_ == nullptr) { // один из потомков - пустой
      Node *child = nullptr;
      (curr->left_ != nullptr) ? child = curr->left_ : child = curr->right_;
      Node *parent = curr->p_;
      if (parent == nullptr) {
        root_ = (curr->left_ != nullptr) ? curr->left_ : curr->right_;
        root_->p_ = nullptr;
      } else if (parent->key_ < curr->key_) {
        parent->right_ = (curr->left_ != nullptr) ? curr->left_ : curr->right_;
        child->p_ = parent;
      } else {
        parent->left_ = (curr->left_ != nullptr) ? curr->left_ : curr->right_;
        child->p_ = parent;
      }
      delete (curr);
    } else { // оба не пустые
      Node *next = getNext(curr);
      curr->key_ = next->key_;
      if (next->p_->left_ == next) {
        next->p_->left_ = next->right_;
        if (next->right_ != nullptr) {
          next->right_->p_ = next->p_;
        }
      } else {
        next->p_->right_ = next->left_;
        if (next->left_ != nullptr)
          next->right_->p_ = next->p_;
      }
      delete (next);
    }

  }

  void deleteKeyReq(const T &key) {
    root_ = deleteKeyR(root_, key);
  }

// Определение количества узлов дерева
  int getCount() const {
    return getCountSubTree(this->root_);
  }

  // Определение высоты дерева
  int getHeight() const {
    return getHeightSubTree(this->root_);
  }

  bool isEmpty() const {
    return root_ == nullptr;
  }

  int getCountEven() {
    return getCountEvenReq(root_);
  }

  T getKey(int index) {
    if (index < 0) {
      throw "Out of bound";
    }
    int curr = -1;
    T ans = getKeySubTree(root_, curr, index);
    if (curr < index) {
      throw "Out of bound";
    } else {
      return ans;
    }

  }

  T getNext(T value) {
    return getNext(root_, value);
  }
  void wideWalk() {
    QueueList<Node *> queue;
    queue.enQueue(root_);
    while (!queue.isEmpty()) {
      Node * curr = queue.deQueue();
      if (curr != nullptr) {
        cout << curr->key_ << ' ';
        queue.enQueue(curr->left_);
        queue.enQueue(curr->right_);
      }
    }
  }

  void horizontalWalk() {
    StackList< Node * > stack;
    stack.push(root_);
    Node *temp = root_;
    Node *lastLeft = nullptr;
    while (!stack.isEmpty()) {
      while (temp->left_) {
        temp = temp->left_;
        stack.push(temp);
      }
      lastLeft = stack.pop();
      std::cout << lastLeft->key_ << " ";
      if (lastLeft->right_ != nullptr) {
        temp = lastLeft->right_;
        stack.push(temp);
      }
    }
  }

  void inQueue(QueueList<T> & queue) const{
    StackList< Node * > stack;
    stack.push(root_);
    Node *temp = root_;
    Node *lastLeft = nullptr;
    while (!stack.isEmpty()) {
      while (temp->left_) {
        temp = temp->left_;
        stack.push(temp);
      }
      lastLeft = stack.pop();
      queue.enQueue(lastLeft->key_);
      if (lastLeft->right_ != nullptr) {
        temp = lastLeft->right_;
        stack.push(temp);
      }
    }
  }

  bool isEqual(const BinarySearchTree<T> & second) {
    QueueList<T> firstQueue;
    QueueList<T> secondQueue;
    inQueue(firstQueue);
    second.inQueue(secondQueue);
    while (!firstQueue.isEmpty() && !secondQueue.isEmpty()) {
      if (firstQueue.deQueue() != secondQueue.deQueue()) {
        return false;
      }
      return firstQueue.isEmpty() == secondQueue.isEmpty();
    }
  }
private:

  // Функция поиска адреса узла по ключу в бинарном дереве поиска
  Node *iterativeSearchNode(const T &key) const {
    Node *curr = root_;
    while (curr != nullptr) {
      if (curr->key_ == key) {
        return curr;
      } else if (key < curr->key_) {
        curr = curr->left_;
      } else {
        curr = curr->right_;
      }
    }
    return curr;
  }

  //
  // Рекурсивные функции, представляющие
  // рекурсивные тела основных интерфейсных методов
  //
  void insertR(Node *node, const T &key) {
    if (node->key_ == key) {
      throw "Just is";
    }
    if (node->key_ > key) {
      if (node->left_ == nullptr) {
        node->left_ = new Node(key, nullptr, nullptr, node);
      } else {
        insertR(node->left_, key);
      }
    } else {
      if (node->right_ == nullptr) {
        node->right_ = new Node(key, nullptr, nullptr, node);
      } else {
        insertR(node->right_, key);
      }
    }
  }

  Node *deleteKeyR(Node *node, const T &key) {
    if (node == nullptr) {
      throw "Didn't find key";
    }
    if (node->key_ > key) {
      node->left_ = deleteKeyR(node->left_, key);
    } else if (node->key_ < key) {
      node->right_ = deleteKeyR(node->right_, key);
    } else if (node->left_ != nullptr && node->right_ != nullptr) {
      node->key_ = getMin(node->right_)->key_;
      node->right_ = deleteKeyR(node->right_, node->key_);
    } else {
      if (node->left_ != nullptr) {
        node = node->left_;
      } else if (node->right_ != nullptr) {
        node = node->right_;
      } else {
        Node *tmp = node;
        delete (tmp);
        node = nullptr;
      }
    }
    return node;
  }

  // Рекурсивная функция для освобождения памяти
  void deleteSubtree(Node *node) {
    if (node == nullptr) {
      return;
    }
    deleteSubtree(node->left_);
    deleteSubtree(node->right_);
    delete (node);
  }

  // Рекурсивная функция определения количества узлов дерева
  int getCountSubTree(Node *node) const {
    if (node == nullptr)
      return 0;
    return (1 + getCountSubTree(node->left_) + getCountSubTree(node->right_));
  }

  int getCountEvenReq(Node *node) const {
    if (node == nullptr) {
      return 0;
    }
    return (((node->key_ + 1) % 2) + getCountEvenReq(node->left_) + getCountEvenReq(node->right_));
  }


  // Рекурсивная функция определения высоты дерева
  int getHeightSubTree(Node *node) const {
    if (node == nullptr) {
      return 0;
    }
    return max(getHeightSubTree(node->left_), getHeightSubTree(node->right_)) + 1;
  }

// Рекурсивная функция для вывода изображения дерева в выходной поток
  void printNode(ostream &out, Node *root) const {
    // Изображение дерева заключается в круглые скобки.
    out << '(';
    if (root) {
      // Для узлов дерева должна быть определена (или переопределена)
      // операция вывода в выходной поток <<
      out << root->key_;
      printNode(out, root->left_);
      printNode(out, root->right_);
    }
    out << ')';
  }

  // Рекурсивная функция для организации обхода узлов дерева.
  void inorderWalk(Node *node) const {
    if (node == nullptr) {
      return;
    }
    inorderWalk(node->left_);
    inorderWalk(node->right_);
  }

  Node *getNext(Node *node) const {
    if (node->right_ == nullptr) {
      while (node != nullptr && node->right_ == nullptr) {
        node = node->p_;
      }
      if (node == nullptr) {
        return nullptr;
      }
    }
    node = node->right_;
    while (node->left_ != nullptr) {
      node = node->left_;
    }
    return node;
  }

  Node *getMin(Node *node) const {
    if (isEmpty()) {
      return nullptr;
    }
    Node *curr = node;
    while (curr->left_ != nullptr) {
      curr = curr->left_;
    }
    return curr;
  }

  Node *getMax(Node *node) const {
    if (isEmpty()) {
      return nullptr;
    }
    Node *curr = node;
    while (curr->right_ != nullptr) {
      curr = curr->right_;
    }
    return curr;
  }

  T getKeySubTree(Node *node, int &curr, int value) {
    if (node->left_ != nullptr) {
      T leftValue = 0;
      leftValue = getKeySubTree(node->left_, curr, value);
      if (curr >= value) {
        return leftValue;
      }
    }
    curr++;
    if (curr == value) {
      return node->key_;
    }
    if (node->right_ != nullptr) {
      return getKeySubTree(node->right_, curr, value);
    }
    return node->key_;
  }

  T getNext(Node *node, int value) {
    if (node == nullptr) {
      throw "Nan";
    }
    if (node->key_ > value) {
      if (node->left_ == nullptr) {
        return node->key_;
      }
      if (node->left_->key_ > value) {
        return getNext(node->left_, value);
      }
      if (node->left_->key_ <= value) {
        try {
          T tmp = getNext(node->left_, value);
          if (tmp > value) {
            return tmp;
          } else {
            return node->key_;
          }
        } catch (const char *e) {
          return node->key_;
        }
      }
    } else {
      return getNext(node->right_, value);
    }
  }

}; // конец шаблона класса TreeBinarySearchTree



#endif //BINARYTREE_BINARYSEARCHTREE_H
