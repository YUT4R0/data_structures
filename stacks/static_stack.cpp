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

template <typename T> class Stack {
private:
  int top;
  int LEN;
  T *stack;
public:
  void create(int LEN) {
    stack = new T[LEN];
    top = 0;
  }

  void push(T data) {
    if (top < LEN - 1) {
      stack[++top] = data;
    } else cout << "the stack is full!" << endl;
  }

  void pop() {
    if (top >= 0) --top;
    else cout << "the stack is empty!" << endl;
  }

  void print() {
    cout << "====> STACK <====" << endl;
    for (int i = top; i >= 1; --i) {
      stack[i].print();
    }
    cout << endl;
  }
};

int main() {
  const int LEN = 10;
  Stack<Data> stack;
  stack.create(LEN);

  Data d1 = Data(1, "one");
  Data d2 = Data(2, "two");
  Data d3 = Data(3, "three");
  Data d4 = Data(4, "four");
  Data d5 = Data(5, "five");
  
  stack.push(d1);
  stack.push(d2);
  stack.push(d3);
  stack.push(d4);
  stack.push(d5);
  stack.print();

  stack.pop();
  stack.pop();
  stack.print();
  
  return 0;
}