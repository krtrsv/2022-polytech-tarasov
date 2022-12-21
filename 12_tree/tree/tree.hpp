#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>

class BST {
  struct node {
    int data;
    node *left;
    node *right;
    node(int x, node *l = nullptr, node *r = nullptr)
        : data{x}, left{l}, right{r} {}
    friend std::ostream &operator<<(std::ostream &out, const node &n) {
      out << n.data;
      return out;
    }
  };

  node *root;

  node *makeEmpty(node *t) {
    if (t == nullptr)
      return nullptr;
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
    return nullptr;
  }

  node *insert(int x, node *t) {
    if (t == nullptr)
      t = new node{x};
    else if (x < t->data)
      t->left = insert(x, t->left);
    else if (x > t->data)
      t->right = insert(x, t->right);
    return t;
  }

  node *findMin(node *t) {
    if (!t || !t->left)
      return t;
    return findMin(t->left);
  }

  node *findMax(node *t) {
    if (!t || !t->right)
      return t;
    return findMax(t->right);
  }

  node *remove(int x, node *t) {
    node *temp;
    if (t == nullptr)
      return nullptr;
    else if (x < t->data)
      t->left = remove(x, t->left);
    else if (x > t->data)
      t->right = remove(x, t->right);
    else if (t->left && t->right) {
      temp = findMin(t->right);
      t->data = temp->data;
      t->right = remove(t->data, t->right);
    } else {
      temp = t;
      if (t->left == nullptr)
        t = t->right;
      else if (t->right == nullptr)
        t = t->left;
      delete temp;
    }

    return t;
  }

  void inorder(node *t) {
    if (t == nullptr)
      return;
    inorder(t->left);
    std::cout << t->data << " ";
    inorder(t->right);
  }

  node *find(node *t, int x) {
    if (t == nullptr || t->data == x)
      return t;
    return find(x < t->data ? t->left : t->right, x);
  }

public:
  BST() { root = nullptr; }

  ~BST() { root = makeEmpty(root); }

  bool insert(int x) {
    root = insert(x, root);
    return true;
  }
  bool remove(int x) {
    root = remove(x, root);
    return true;
  }
  node *search(int x) { return find(root, x); }

  void display() {
    inorder(root);
    std::cout << std::endl;
  }
};

#endif
