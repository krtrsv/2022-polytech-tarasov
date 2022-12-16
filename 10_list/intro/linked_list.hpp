#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <initializer_list>
#include <iostream>

struct Node {
  int data;
  Node *next;

  Node(int d, Node *n) : data{d}, next{n} {}
  Node(int d) : Node(d, nullptr) {}

  friend std::ostream &operator<<(std::ostream &out, Node *n) {
    return out << n->data;
  }
};

class LinkedList {
  Node *head;
  std::size_t m_size = 0;

public:
  LinkedList();
  LinkedList(Node *n);
  LinkedList(std::initializer_list<int> il);
  ~LinkedList();

public:
  void clone(LinkedList *ll);
  bool insert(const std::size_t pos, const int &value);
  bool push_front(const int &value);
  bool remove(const std::size_t pos);
  Node *get(const std::size_t pos);
  std::size_t size();
  friend std::ostream &operator<<(std::ostream &out, LinkedList &n);
  bool operator==(LinkedList &ll);

private:
  LinkedList(const LinkedList &) = delete;
  void operator=(const LinkedList &) = delete;
};

#endif
