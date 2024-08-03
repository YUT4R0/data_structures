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
  void setKey(Key key) { this->key = key; }
  void setValue(Value value) { this->value = value;}
  Key getKey() { return key; }
  Value getValue() { return value; }
};

template <typename T> class Node {
public:
  Key key;
  Data data;
  Node<T> *left, *right;
};

template <typename T> class BinarySearchTree {
private:
  Node<T> *root;
  void insertOnBST(T data, Node<T> *&node) {
    if (node == nullptr) {
      node = new Node<T>;
      node->left = node->right = nullptr;
      node->data = data;
    } else if (data.getKey() < node->data.getKey())
      insertOnBST(data, node->left);
    else if (data.getKey() > node->data.getKey())
      insertOnBST(data, node->right);
    else
      cout << "Key already exists" << endl;
  }
  T searchOnBST(T &data, Node<T> *&node) {
    if (data.getKey() < node->data.getKey())
      searchOnBST(data, node->left);
    else if (data.getKey() > node->data.getKey())
      searchOnBST(data, node->right);
    else
      data = node->data;
    return data;
  }
  void proccessItem(T data) {
    data.print();
  }
  void preOrderTravelBST(Node<T> *node) {
    if (node != nullptr) {
      proccessItem(node->data);
      preOrderTravelBST(node->left);
      preOrderTravelBST(node->right);
    }
  }
  void centralTravelBST(Node<T> *node) {
    if (node != nullptr) {
      centralTravelBST(node->left);
      proccessItem(node->data);
      centralTravelBST(node->right);
    }
  }
  void posOrderTravelBST(Node<T> *node) {
    if (node != nullptr) {
      posOrderTravelBST(node->left);
      posOrderTravelBST(node->right);
      proccessItem(node->data);
    }
  }
  void removeTempOnBST(Node<T> *parent, Node<T> *&node) {
    if (node->right != nullptr)
      removeTempOnBST(parent, node->right);
    else {
      parent->data = node->data;
      parent = node;
      node = node->left;
      delete parent;
    }
  }
  void removeNodeOnBST(T data, Node<T> *&node) {
    if (node == nullptr)
      cout << "item not found" << endl;
    else if (data.getKey() < node->data.getKey())
      removeNodeOnBST(data, node->left);
    else if (data.getKey() > node->data.getKey())
      removeNodeOnBST(data, node->right);
    else if (node->left == nullptr) {
      Node<T> *temp = node;
      node = node->right;
      delete temp;
    } else if (node->right == nullptr) {
      Node<T> *temp = node;
      node = node->left;
      delete temp;
    } else
      removeTempOnBST(node, node->left);
  }

public:
  BinarySearchTree() : root(nullptr) {}
  void insert(T &data) { insertOnBST(data, root); }
  T search(T &data) { return searchOnBST(data, root); }
  void preOrderTravel() { preOrderTravelBST(root); }
  void centralTravel() { centralTravelBST(root); }
  void posOrderTravel() { posOrderTravelBST(root); }
  void removeNode(T &data) { removeNodeOnBST(data, root); }
};

int main() {
  BinarySearchTree<Data> bst;
  Data data1(1, "A");
  Data data2(2, "B");
  Data data3(3, "C");
  Data data4(4, "D");
  Data data5(5, "E");
  bst.insert(data3);
  bst.insert(data2);
  bst.insert(data1);
  bst.insert(data4);
  bst.insert(data5);
  bst.posOrderTravel();

  cout << "founded: " << endl;
  Data myd = bst.search(data5);
  myd.print();
  Data myd2 = bst.search(data3);
  myd2.print();

  cout << "REMOVE: " << endl;
  bst.removeNode(data3);
  bst.posOrderTravel();
  return 0;
}