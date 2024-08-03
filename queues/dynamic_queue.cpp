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
};

template <typename T> class Node {
public:
  Data data;
  Node<T> *next;
  Node() : next(nullptr) {}
};

template <typename T> class Queue {
private:
  Node<T> *front, *rear;
  int current_LEN;
public:
  Queue() : front(new Node<T>), rear(front), current_LEN(0) {
    front->next = rear->next = nullptr;
  }

  bool isEmpty() { return current_LEN == 0; }

  void enqueue(T data) {
    rear->next = new Node<T>;
    rear = rear->next;
    rear->data = data;
    rear->next = nullptr;
    ++current_LEN;
  }

  void dequeue() {
    if (!isEmpty()) {
      Node<T> *temp = front;
      front = front->next;
      delete temp;
      temp = nullptr;
      --current_LEN;
    } else
      cout << "the queue is empty!" << endl;
  }

  void show() {
    cout << "=====> QUEUE <=====" << endl;
    Node<T> *ptr = new Node<T>;
    ptr = front->next;
    while (ptr != nullptr) {
      ptr->data.print();
      ptr = ptr->next;
    }
    cout << "size: " << current_LEN << endl;
  }
};

int main() {
  Queue<Data> queue;
  string mock[] = {"Pedro", "Maria", "Jose", "Ana", "Joao", "Lucas", "Marcos"};
  for (int i = 0; i < 7; ++i) {
    Data d = Data(i + 1, mock[i]);
    queue.enqueue(d);
  }
  queue.show();

  queue.dequeue();
  queue.dequeue();
  queue.dequeue();
  queue.show();
  Data d1 = Data(10, "Onichan");
  Data d2 = Data(69, "Jeffersson");
  Data d3 = Data(69, "Jeffersson");
  Data d4 = Data(69, "Jeffersson");
  queue.enqueue(d1);
  queue.enqueue(d2);
  queue.enqueue(d3);
  queue.enqueue(d4);
  queue.show();

  queue.dequeue();
  queue.dequeue();
  queue.show();
  return 0;
}