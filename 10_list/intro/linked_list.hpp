#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <initializer_list>
#include <iostream>

template <typename T> struct Node {
  T data;
  Node *next;

  Node(T d, Node *n) : data{d}, next{n} {}
  Node(T d) : Node(d, nullptr) {}

  friend std::ostream &operator<<(std::ostream &out, Node<T> *n) {
    return out << n->data;
  }
};

template <typename T> class LinkedList {
  typedef Node<T> _Node;

  _Node *head;
  std::size_t m_size = 0;

public:
  LinkedList() : m_size{0} { head = nullptr; }
  LinkedList(_Node *n) {
    head = n;
    for (auto i = n; i != nullptr; i = i->next)
      m_size++;
  }
  LinkedList(std::initializer_list<T> il) : head{nullptr}, m_size{il.size()} {
    if (il.size() == 0)
      return;
    for (auto it = std::rbegin(il); it != std::rend(il); ++it) {
      _Node *n = new _Node(*it, head);
      head = n;
    }
  }

  ~LinkedList() {
    while (head->next) {
      _Node *t = head->next;
      head->next = t->next;
      delete t;
    }
    delete head;
  }

  void clone(LinkedList<T> *ll) {
    if (head == nullptr)
      return;
    int iter = 0;
    for (_Node *temp = head; temp != nullptr; temp = temp->next) {
      ll->insert(iter, temp->data);
      iter++;
    }
  }

  bool insert(const std::size_t pos, const T &value) {
    if (pos > m_size)
      return false;
    m_size++;
    _Node *n = new _Node(value);
    if (pos == 0) {
      n->next = head;
      head = n;
      return true;
    }
    _Node *curr = head;
    _Node *next = head->next;
    for (std::size_t iter = 1; iter != pos; iter++) {
      curr = curr->next;
      next = next->next;
    }
    n->next = next;
    curr->next = n;
    return true;
  }

  _Node *get(const std::size_t pos) {
    if (pos > m_size)
      return nullptr;
    _Node *temp = head;
    for (std::size_t iter = 0; iter != pos; iter++) {
      temp = temp->next;
    }
    return temp;
  }

  bool push_front(const T &value) { return insert(0, value); }

  bool remove(const std::size_t pos) {
    if (pos > this->size())
      return false;
    m_size--;
    if (pos == 0) {
      _Node *temp = head;
      head = head->next;
      delete temp;
      return true;
    }
    _Node *temp = head;
    _Node *prev = head;
    for (int i = 0; i < pos + 1; i++) {
      if (i == pos && temp) {
        prev->next = temp->next;
        delete temp;
        return true;
      } else {
        prev = temp;
        if (prev == nullptr)
          return false;
        temp = temp->next;
      }
    }
    return false;
  }

  std::size_t size() { return m_size; }

  friend std::ostream &operator<<(std::ostream &out, LinkedList<T> &n) {
    if (n.m_size == 0) {
      out << "...";
      return out;
    }
    for (auto tmp = n.head; tmp != nullptr; tmp = tmp->next) {
      out << tmp->data;
      if (tmp->next != nullptr)
        out << "->";
    }
    return out;
  }

  bool operator==(LinkedList<T> &ll) {
    if (m_size != ll.m_size)
      return false;
    _Node *e2 = ll.head;
    for (_Node *tmp = head; tmp != nullptr; tmp = tmp->next) {
      if (tmp->data != e2->data)
        return false;
      e2 = e2->next;
    }
    return true;
  }

private:
  LinkedList(const LinkedList &) = delete;
  void operator=(const LinkedList &) = delete;
};

#endif
