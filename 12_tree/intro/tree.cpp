#include <bits/stdc++.h>

struct Node {
  int data;
  struct Node *left, *right;

  Node(int d, Node *l = nullptr, Node *r = nullptr)
      : data{d}, left{l}, right{r} {}
};

void printInorder(const Node *node) {
  if (node == nullptr)
    return;

  printInorder(node->left);
  std::cout << node->data << " ";
  printInorder(node->right);
}

void printPreorder(const Node *node) {
  if (node == nullptr)
    return;

  std::cout << node->data << " ";
  printPreorder(node->left);
  printPreorder(node->right);
}

void printPostorder(const Node *node) {
  if (node == nullptr)
    return;

  printPostorder(node->left);
  printPostorder(node->right);
  std::cout << node->data << " ";
}

int main() {
  auto root = new Node(1);
  root->left = new Node(2);
  root->right = new Node(3);
  root->left->left = new Node(4);
  root->left->right = new Node(5);
  root->left->right->left = new Node(6);
  root->left->right->right = new Node(7);

  std::cout << "inorder: ";
  printInorder(root);
  std::cout << "\npreorder: ";
  printPreorder(root);
  std::cout << "\npostorder: ";
  printPostorder(root);
  std::cout << '\n';

  return 0;
}
