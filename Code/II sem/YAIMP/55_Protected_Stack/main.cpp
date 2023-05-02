#include <iostream>
using namespace std;

const int MAX_SIZE = 1000000;

struct Stack {
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
    cout << arr[index - 1] << "\n"; index--;
  }

  void clear() {
    front = index = 0;
    cout << "ok\n";
  }

  void size() {
    cout << index - front << "\n";
  }

  void back_element() {
    if (front == index) {
      cout << "error\n";
      return;
    }
    cout << arr[index - 1] << "\n";
  }
};

int main() {
  Stack s;
  string command;
  int n;

  while (cin >> command) {
    if (command == "push") {
      cin >> n;
      s.push(n);
    }
    else if (command == "pop") {
      s.pop();
    }
    else if (command == "back") {
      s.back_element();
    }
    else if (command == "size") {
      s.size();
    }
    else if (command == "clear") {
      s.clear();
    }
    else if (command == "exit") {
      cout << "bye\n";
      break;
    }
  }
}