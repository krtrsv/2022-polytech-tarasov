#ifndef REVERSE_LL_HPP
#define REVERSE_LL_HPP

#include <random>

struct Node {
  int data;
  Node *next;
};

inline Node *generate(int n) {
  Node *ptr = nullptr;
  for (int i = n; i > 0; --i) {
    Node *new_node = new Node{i, ptr};
    ptr = new_node;
  }
  return ptr;
}

inline Node *generate_random(int n) {
  std::random_device rd;

  std::mt19937 rng(rd());
  std::default_random_engine dre{rd()};
  std::uniform_int_distribution<int> randint{10, 99};

  Node *ptr = nullptr;
  for (int i = n; i > 0; --i) {
    Node *new_node = new Node{randint(dre), ptr};
    ptr = new_node;
  }
  return ptr;
}

inline void reverse(Node **head) {
  Node *current = *head;
  Node *prev = nullptr, *next = nullptr;

  while (current != nullptr) {
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }
  *head = prev;
}

inline void reverse(Node **head, int left, int right) {
  Node *curr = *head, *prev = NULL;
  int i;
  for (i = 0; i < left; i++) {
    prev = curr;
    curr = curr->next;
  }
  Node *rtail = curr;
  Node *rhead = NULL;
  while (i <= right) {
    Node *next = curr->next;
    curr->next = rhead;
    rhead = curr;
    curr = next;
    i++;
  }
  if (prev != NULL)
    prev->next = rhead;
  else
    *head = rhead;
  rtail->next = curr;
}

#endif
