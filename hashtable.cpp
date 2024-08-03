#include <iostream>
#include <string>

#define HT_SIZE 13
#define HT_BASE 31
using namespace std;

typedef unsigned long long ull;

class Data {
private:
  int key;
  string value;
public:
  Data() : key(0), value("") {}
  Data(int key, string value) : key(key), value(value) {}
  int getKey() { return key; }
  string getValue() { return value; }
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
  List() {
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
    if (size == 0)
      cout << "(NULL)" << endl;
    else
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
  T getItemByValue(string value) {
    Node<T> *ptr = first->next;
    T data = ptr->data;
    if (!isEmpty()) {
      while (ptr != nullptr) {
        if (ptr->data.getValue() == value)
          return ptr->data;
        else
          ptr = ptr->next;
      }
      return data;
    } else
      return data;
  }
  void removeItemByValue(string value) {
    Node<T> *ptr = first->next;
    if (!isEmpty()) {
      while (ptr != nullptr) {
        if (ptr->data.getValue() == value) {
          removeNode(ptr);
          break;
        } else
          ptr = ptr->next;
      }
    } else
      cout << "list is empty" << endl;
  }
};

template<typename T> class HashTable {
private:
  List<T> array[HT_SIZE];
  ull fastExp(ull base, ull expoent, ull mod)
    {
        ull ans = 1;
        while (expoent) {
            if (expoent & 1)
                ans = ((ans % mod) * (base % mod)) % mod;
            base = ((base % mod) * (base % mod)) % mod;
            expoent >>= 1;
        }
        return ans % mod;
    }
    ull hash(std::string value)
    {
        ull hash = 0;
        ull keySize = value.size();
        for (ull i = 0; i < keySize; i++)
            hash = (hash + value[i] * (fastExp(HT_BASE, keySize - i - 1, HT_SIZE))) % HT_SIZE;
        return hash % HT_SIZE;
    }
public:
  HashTable() {}
  void insert(Data *data) {
    int index = hash(data->getValue());
    array[index].insert(*data);
  }

  Data getDataByKey(string key) {
    int index = hash(key);
    return array[index].getItemByValue(key);
  }

  Data popDataByKey(string key) {
    int index = hash(key);
    Data data = array[index].getItemByValue(key);
    array[index].removeItemByValue(key);
    return data;
  }

  void show() {
    cout << "[==== HASH TABLE ====]" << endl;
    for (int i = 0; i < HT_SIZE; ++i) {
      cout << i << "| ";
      array[i].show();
    }
    cout << "[=====================]" << endl;
  }
};

int main() {
  HashTable<Data> ht;
  string str1 = "Hash";
  string str2 = "pedro";
  string str3 = "Isabela";
  string str4 = "Jose";
  string str5 = "Maria";
  Data *data1 = new Data(1, str1);
  Data *data2 = new Data(2, str2);
  Data *data3 = new Data(3, str3);
  Data *data4 = new Data(4, str4);
  Data *data5 = new Data(5, str5);
  ht.insert(data1);
  ht.insert(data2);
  ht.insert(data3);
  ht.insert(data4);
  ht.insert(data5);
  ht.show();

  Data mydata = ht.getDataByKey(str3);
  cout << "my silly data: ";
  mydata.print();

  Data popedData = ht.popDataByKey(str3);
  cout << "my silly poped data: ";
  popedData.print();
  ht.show();
  return 0;
}