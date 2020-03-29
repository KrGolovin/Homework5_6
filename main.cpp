#include <iostream>
#include "QueueArray.h"
#include "QueueList.h"
#include "BinarySearchTree.h"

int main() {
  //Queue тесты
  QueueArray<int> queueArray(10);
  QueueList<int> queueList;
  Queue<int> *queues[] = {&queueArray, & queueList};
  //Queue<int> * queueArray = new QueueArray<int>(10);
  for (int k = 0; k < 2; ++k) {
    try {
      for (int i = 0; i < 10; ++i) {
        queues[k]->enQueue(i);
      }
    } catch (std::exception &e) {
      std::cout << e.what() << '\n';
    }
    while (!queues[k]->isEmpty()) {
      std::cout << queues[k]->deQueue() << ' ';
    }
    std::cout << '\n';
    try {
      queues[k]->deQueue();
    } catch (std::exception &e) {
      std::cout << e.what() << '\n';
    }
  }
  //

  // тесты методов дерева
  int * array = new int[10];
  for (int i = 0; i < 10; ++i) {
    array[i] = (rand() % 100);
  }
  BinarySearchTree<int> tree;
  for (int i = 0; i < 10; i++) {
    tree.insert(array[i]);
  }
  tree.horizontalWalk();
  std::cout << '\n';
  tree.wideWalk();
  std::cout << '\n';
  BinarySearchTree<int> copyTree;
  for (int i = 0; i < 10; i++) {
    copyTree.insert(array[i]);
  }
  std::cout << tree.isEqual(copyTree) << '\n';
  copyTree.deleteKey(array[0]);
  std::cout << tree.isEqual(copyTree);

  return 0;
}
