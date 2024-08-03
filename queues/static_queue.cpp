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

template <typename T> class Queue {
private:
  int front, rear, LEN, current_LEN;
  T *data;

public:
  void create(int len) {
    LEN = len;
    data = new T[len];
    front = 0;
    rear = 0;
    current_LEN = 0;
  }

  bool isFull() { return current_LEN == LEN; }
  bool isEmpty() { return current_LEN == 0; }

  void enqueue(T item) {
    if (!isFull()) {
      data[rear] = item;
      rear = (rear + 1) % LEN;
      ++current_LEN;
    } else
      cout << "the queue is full!" << endl;
  }

  void dequeue() {
    if (!isEmpty()) {
      front = (front + 1) % LEN;
      --current_LEN;
    } else
      cout << "the queue is empty!" << endl;
  }

  void show() {
    cout << "=====> QUEUE <=====" << endl;
    for (int i = 0; i < current_LEN; ++i) {
      int pos = (front + i) % LEN;
      data[pos].print();
    }
    cout << "size: " << current_LEN << endl;
  }
};

int main() {
  Queue<Data> queue;
  const int LEN = 7;
  queue.create(LEN);
  string mock[] = {"Pedro", "Maria", "Jose", "Ana", "Joao", "Lucas", "Marcos"};
  for (int i = 0; i < LEN; ++i) {
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
  queue.enqueue(d1);
  queue.enqueue(d2);
  queue.show();
  return 0;
}