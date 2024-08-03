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
  void setValue(Value value) { this->value = value; }
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
  void _insert(T data, Node<T> *&node) {
    if (node == nullptr) {
      node = new Node<T>;
      node->left = node->right = nullptr;
      node->data = data;
    } else if (data.getKey() < node->data.getKey())
      _insert(data, node->left);
    else if (data.getKey() > node->data.getKey())
      _insert(data, node->right);
    else {
      cout << "Key already exists" << endl;
      return;
    }
    handleBalance(node);
  }
  T _search(T &data, Node<T> *&node) {
    if (data.getKey() < node->data.getKey())
      _search(data, node->left);
    else if (data.getKey() > node->data.getKey())
      _search(data, node->right);
    else
      data = node->data;
    return data;
  }
  void proccessItem(T data, Node<T> *node) {
    cout << "key: " << data.getKey() << ", value: " << data.getValue()
         << ", BF: " << BF(node) << endl;
  }
  void _preOrderTravel(Node<T> *node) {
    if (node != nullptr) {
      proccessItem(node->data, node);
      _preOrderTravel(node->left);
      _preOrderTravel(node->right);
    }
  }
  void _centralTravel(Node<T> *node) {
    if (node != nullptr) {
      _centralTravel(node->left);
      proccessItem(node->data, node);
      _centralTravel(node->right);
    }
  }
  void _posOrderTravel(Node<T> *node) {
    if (node != nullptr) {
      _posOrderTravel(node->left);
      _posOrderTravel(node->right);
      proccessItem(node->data, node);
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
  void _removeNode(T data, Node<T> *&node) {
    if (node == nullptr)
      cout << "item not found" << endl;
    else if (data.getKey() < node->data.getKey())
      _removeNode(data, node->left);
    else if (data.getKey() > node->data.getKey())
      _removeNode(data, node->right);
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
    handleBalance(node);
  }
  int _getTreeHeight(Node<T> *node) {
    if (node == nullptr)
      return 0;
    else {
      int leftHeight = _getTreeHeight(node->left);
      int rightHeight = _getTreeHeight(node->right);
      return 1 + std::max(leftHeight, rightHeight);
    }
  }
  int BF(Node<T> *node) {
    if (node == nullptr)
      return 0;
    else {
      int lh = _getTreeHeight(node->left);
      int rh = _getTreeHeight(node->right);
      return rh - lh;
    }
  }
  void handleBalance(Node<T> *&node) {
    if (BF(node) < -1) {
      if (BF(node->left) <= 0)
        RR(node);
      else
        DRR(node);
    } else if (BF(node) > 1) {
      if (BF(node->right) >= 0)
        LR(node);
      else
        DLR(node);
    }
  }
  void LR(Node<T> *&node) {
    Node<T> *y = node->right;
    Node<T> *z = y->left;
    node->right = z;
    y->left = node;
    node = y;
  }
  void RR(Node<T> *&node) {
    Node<T> *y = node->left;
    Node<T> *z = y->right;
    node->left = z;
    y->right = node;
    node = y;
  }
  void DLR(Node<T> *&node) {
    RR(node->right);
    LR(node);
  }
  void DRR(Node<T> *&node) {
    LR(node->left);
    RR(node);
  }
public:
  BinarySearchTree() : root(nullptr) {}
  void insert(T &data) { _insert(data, root); }
  T search(T &data) { return _search(data, root); }
  void preOrderTravel() { _preOrderTravel(root); }
  void centralTravel() { _centralTravel(root); }
  void posOrderTravel() { _posOrderTravel(root); }
  void removeNode(T &data) { _removeNode(data, root); }
  int getTreeHeight() { return _getTreeHeight(root) - 1; }
};

int main() {
  BinarySearchTree<Data> bst;
  Data data10(10, "A");
  Data data12(12, "B");
  Data data4(4, "C");
  Data data2(2, "D");
  Data data6(6, "E");
  Data data8(8, "Z");
  bst.insert(data10);
  bst.insert(data12);
  bst.insert(data4);
  bst.insert(data2);
  bst.insert(data6);
  bst.insert(data8);
  bst.centralTravel();

  int h = bst.getTreeHeight();
  cout << "Height of the tree: " << h << endl;
  cout << "data to remove: ";
  Data mydt = bst.search(data2);
  mydt.print();
  Data mydt2 = bst.search(data4);
  mydt2.print();
  

  bst.removeNode(mydt);
  bst.removeNode(mydt2);
  bst.centralTravel();
  return 0;
}