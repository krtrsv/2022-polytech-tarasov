#include "linked_list.hpp"

LinkedList::LinkedList() : m_size{0} { head = nullptr; }
LinkedList::LinkedList(Node *n) {
  head = n;
  for (auto i = n; i != nullptr; i = i->next)
    m_size++;
}

LinkedList::LinkedList(std::initializer_list<int> il)
    : head{nullptr}, m_size{il.size()} {
  if (il.size() == 0)
    return;
  for (auto it = std::rbegin(il); it != std::rend(il); ++it) {
    Node *n = new Node(*it, head);
    head = n;
  }
}

LinkedList::~LinkedList() {
  while (head->next) {
    Node *t = head->next;
    head->next = t->next;
    delete t;
  }
  delete head;
}

void LinkedList::clone(LinkedList *ll) {
  if (head == nullptr)
    return;
  int iter = 0;
  for (Node *temp = head; temp != nullptr; temp = temp->next) {
    ll->insert(iter, temp->data);
    iter++;
  }
}

bool LinkedList::insert(const std::size_t pos, const int &value) {
  if (pos > m_size)
    return false;
  m_size++;
  Node *n = new Node(value);
  if (pos == 0) {
    n->next = head;
    head = n;
    return true;
  }
  Node *curr = head;
  Node *next = head->next;
  for (std::size_t iter = 1; iter != pos; iter++) {
    curr = curr->next;
    next = next->next;
  }
  n->next = next;
  curr->next = n;
  return true;
}

Node *LinkedList::get(const std::size_t pos) {
  if (pos > m_size)
    return nullptr;
  Node *temp = head;
  for (std::size_t iter = 0; iter != pos; iter++) {
    temp = temp->next;
  }
  return temp;
}

bool LinkedList::push_front(const int &value) { return insert(0, value); }

bool LinkedList::remove(const std::size_t pos) {
  if (pos > this->size())
    return false;
  m_size--;
  if (pos == 0) {
    Node *temp = head;
    head = head->next;
    delete temp;
    return true;
  }
  Node *temp = head;
  Node *prev = head;
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

std::size_t LinkedList::size() { return m_size; }

std::ostream &operator<<(std::ostream &out, LinkedList &n) {
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

bool LinkedList::operator==(LinkedList &ll) {
  if (m_size != ll.m_size)
    return false;
  Node *e2 = ll.head;
  for (Node *tmp = head; tmp != nullptr; tmp = tmp->next) {
    if (tmp->data != e2->data)
      return false;
    e2 = e2->next;
  }
  return true;
}
