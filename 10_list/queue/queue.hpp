#include <utility>

#define OK 0
#define EMPTY 1

struct Node {
  int data;
  Node *next;
};

inline void enqueue(Node **head, int value) {
  Node *n = new Node{value, *head};
  *head = n;
}

inline std::pair<int, int> dequeue(Node **head) {
  if (*head == nullptr)
    return {EMPTY, 0};
  int n = (*head)->data;
  *head = (*head)->next;
  return {OK, n};
}
