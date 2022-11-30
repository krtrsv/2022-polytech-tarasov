struct QNode {
  int data;
  QNode *next;
  QNode(int d) {
    data = d;
    next = nullptr;
  }
};

struct Queue {
  QNode *front, *rear;
  Queue() { front = rear = nullptr; }

  void enqueue(int x) {
    QNode *temp = new QNode(x);

    if (rear == nullptr) {
      front = rear = temp;
      return;
    }

    rear->next = temp;
    rear = temp;
  }

  void dequeue() {
    if (front == nullptr)
      return;

    QNode *temp = front;
    front = front->next;

    if (front == nullptr)
      rear = nullptr;

    delete (temp);
  }
};
