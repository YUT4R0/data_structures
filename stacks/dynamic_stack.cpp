#include <iostream>
using namespace std;

typedef int Key;
typedef string Value;

class Data {
private:
  Key key;
  Value value;

public:
  Data() : key(0), value("") {}
  Data(Key key, Value value) : key(key), value(value) {}
  void print() { cout << "key: " << key << ", value: " << value << endl; }
  Key getKey() { return key; }
  Value getValue() { return value; }
};

template <typename T> class Node {
public:
  T data;
  Node<T> *next;
  Node() : next(nullptr) {}
};

template <typename T> class Stack {
private:
  Node<T> *top;
  int size;

public:
  Stack() : top(new Node<T>), size(0) {}

  bool isEmpty() { return size == 0; }
  int getSize() { return size; }

  void orderedPush(T data) {
    Node<T> *newNode = new Node<T>;
    newNode->data = data;
    if (isEmpty() || newNode->data.getKey() > top->data.getKey()) {
      newNode->next = top;
      top = newNode;
    } else {
      Node<T> *current = top;
      while (current->next != nullptr &&
             current->next->data.getKey() >= newNode->data.getKey())
        current = current->next;
      newNode->next = current->next;
      current->next = newNode;
    }
    ++size;
  }
  void push(T data) {
    Node<T> *newNode = new Node<T>;
    newNode->data = data;
    newNode->next = top;
    top = newNode;
    ++size;
  }
  T pop() {
    Node<T> *temp = top;
    T data = temp->data;
    top = top->next;
    delete temp;
    temp = nullptr;
    --size;
    return data;
  }

  void show() {
    cout << "====> STACK <====" << endl;
    Node<T> *ptr = top;
    while (ptr->next != nullptr) {
      ptr->data.print();
      ptr = ptr->next;
    }
    cout << "size: " << size << endl;
  }
};

int main() {
  Stack<Data> stack;
  Data d1 = Data(1, "one");
  Data d2 = Data(2, "two");
  Data d3 = Data(3, "three");
  Data d4 = Data(4, "four");
  Data d5 = Data(5, "five");

  stack.push(d1);
  stack.push(d5);
  stack.push(d3);
  stack.push(d2);
  stack.push(d4);
  stack.show();

  Data thisItem = stack.pop();
  thisItem.print();
  stack.show();
  return 0;
}