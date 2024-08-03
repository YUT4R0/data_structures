#include <iostream>
using namespace std;

class Data {
private:
  int key;
  string value;
public:
  Data() : key(0), value("") {}
  Data(int key, string value) : key(key), value(value) {}
  void print() { cout << "key: " << key << ", value: " << value << endl; }
};

template <typename T> class Node {
public:
  Data data;
  Node<T> *next;
  Node() : next(nullptr) {}
};

template <typename T> class List {
private:
  Node<T> *first;
  Node<T> *last;
  int size;
  Node<T> *getNodeByPos(int pos) {
    Node<T> *ptr = first->next;
    for (int i = 0; i < pos; ++i) {
      ptr = ptr->next;
    }
    return ptr;
  }
  Node<T> *predecessor(Node<T> *target) {
    Node<T> *ptr = first;
    while (ptr->next != target && ptr != nullptr) {
      ptr = ptr->next;
    }
    return ptr;
  }
  void removeNode(Node<T> *target) {
    Node<T> *ptr = predecessor(target);
    ptr->next = target->next;
    if (ptr->next == nullptr)
      last = ptr;
    delete target;
    target = nullptr;
  }

public:
  void create() {
    first = new Node<T>();
    first->next = nullptr;
    last = first;
    size = 0;
  }
  int getSize() { return size; }
  bool isEmpty() { return size == 0; }
  void insert(Data data) {
    last->next = new Node<T>();
    last = last->next;
    last->next = nullptr;
    last->data = data;
    ++size;
  }
  void show() {
    Node<T> *ptr = first->next;
    while (ptr != nullptr) {
      ptr->data.print();
      ptr = ptr->next;
    }
    cout << "size: " << size << endl;
  }
  Data getItemByPos(int pos) {
    if (!isEmpty()) {
      Node<T> *ptr = first->next;
      for (int i = 0; i < pos; ++i) {
        ptr = ptr->next;
      }
      return ptr->data;
    } else
      return first->data;
  }
  void removeItemByPos(int pos) {
    if (!isEmpty()) {
      Node<T> *target = getNodeByPos(pos);
      if (target != nullptr)
        removeNode(target);
      --size;
    }
  }
};

int main() {
  Data item1 = Data(1, "joao");
  Data item2 = Data(2, "pedro");
  Data item3 = Data(3, "davi");
  Data item4 = Data(4, "maria");
  Data item5 = Data(5, "jose");

  List<Data> l;
  l.create();
  l.insert(item1);
  l.insert(item2);
  l.insert(item3);
  l.insert(item4);
  l.insert(item5);
  l.show();
  int pos = 3;
  Data myItem = l.getItemByPos(pos);
  cout << "data found: ";
  myItem.print();
  l.removeItemByPos(pos);
  l.show();
  return 0;
}