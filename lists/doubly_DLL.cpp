#include <iostream>
using namespace std;

typedef string Value;
typedef int Key;

class Data {
private:
  Key key;
  Value value;

public:
  Data() : key(0), value("") {}
  Data(Key key, Value value) : key(key), value(value) {}

  void print() { cout << "key: " << key << ", value: " << value << endl; }
};

template <typename T> class Node {
public:
  Data data;
  Node<T> *next;
  Node<T> *prev;
  Node() : next(nullptr), prev(nullptr) {}
};

template <typename T> class List {
private:
  Node<T> *first;
  Node<T> *last;
  int size;
  Node<T> *getNodeByPos(int pos) {
    Node<T> *ptr;
    if (pos <= size / 2) {
      ptr = first->next;
      for (int i = 0; i < pos; i++) {
        ptr = ptr->next;
      }
    } else {
      ptr = last->prev;
      for (int i = 0; i < pos; i++) {
        ptr = ptr->prev;
      }
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

  Node<T> *sucessor(Node<T> *target) {
    Node<T> *ptr = last;
    while (ptr->prev != target && ptr != nullptr) {
      ptr = ptr->prev;
    }
    return ptr;
  }

  void removeNode(int pos, Node<T> *target) {
    Node<T> *ptr;
    if (pos <= size / 2) {
      ptr = predecessor(target);
      ptr->next = target->next;
      if (ptr->next == nullptr)
        last = ptr;
    } else {
      ptr = sucessor(target);
      ptr->prev = target->prev;
      if (ptr->prev == nullptr)
        first = ptr;
    }
    delete target;
    target = nullptr;
  }

public:
  void create() {
    first = new Node<T>();
    first->next = nullptr;
    first->prev = nullptr;
    last = first;
    size = 0;
  }
  int getSize() { return size; }
  bool isEmpty() { return size == 0; }
  void insert(T data) {
    last->next = new Node<T>;
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
  Data getDataByPos(int pos) {
    if (!isEmpty() && pos < size) {
      if (pos <= size / 2) {
        Node<T> *ptr = first->next;
        for (int i = 0; i < pos; ++i) {
          ptr = ptr->next;
        }
        return ptr->data;
      } else {
        Node<T> *ptr = last->prev;
        for (int i = 0; i < size - pos; ++i) {
          ptr = ptr->prev;
        }
        return ptr->data;
      }
    } else
      return first->data;
  }
  void removeDataByPos(int pos) {
    if (!isEmpty() && pos < size) {
      Node<T> *target = getNodeByPos(pos);
      if (target != nullptr) {
        removeNode(pos, target);
        --size;
      }
    }
  }
};

int main() {
  Data item1 = Data(1, "joao");
  Data item2 = Data(2, "pedro");
  Data item3 = Data(3, "davi");
  Data item4 = Data(4, "maria");
  Data item5 = Data(5, "jose");
  Data item6 = Data(6, "marcos");
  List<Data> l;
  l.create();
  l.insert(item1);
  l.insert(item2);
  l.insert(item3);
  l.insert(item4);
  l.insert(item5);
  l.insert(item6);
  l.show();
  int pos = 3;
  Data myData = l.getDataByPos(pos);
  cout << "data found: ";
  myData.print();
  l.removeDataByPos(pos);
  l.show();
  return 0;
}