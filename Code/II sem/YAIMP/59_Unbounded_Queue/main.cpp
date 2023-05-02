#include <iostream>
using namespace std;

const int MAX_SIZE = 1000000;

struct Queue {
  int arr[MAX_SIZE];
  int front = 0, index = 0;

  void push(int n) {
    if (index >= MAX_SIZE) {
      cout << "error\n";
      return;
    }
    arr[index++] = n;
    cout << "ok\n";
  }

  void pop() {
    if (front == index) {
      cout << "error\n";
      return;
    }
    cout << arr[front++] << "\n";
  }

  void clear() {
    front = index = 0;
    cout << "ok\n";
  }

  void size() {
    cout << index - front << "\n";
  }

  void front_element() {
    if (front == index) {
      cout << "error\n";
      return;
    }
    cout << arr[front] << "\n";
  }
};

int main() {
  Queue q;
  string command;
  int n;

  while (cin >> command) {
    if (command == "push") {
      cin >> n;
      q.push(n);
    }
    else if (command == "pop") {
      q.pop();
    }
    else if (command == "front") {
      q.front_element();
    }
    else if (command == "size") {
      q.size();
    }
    else if (command == "clear") {
      q.clear();
    }
    else if (command == "exit") {
      cout << "bye\n";
      break;
    }
  }
}