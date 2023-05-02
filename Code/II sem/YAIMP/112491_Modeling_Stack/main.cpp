#include <iostream>
#include <fstream>
using namespace std;

ofstream outf ("output.txt");

const int MAX_SIZE = 1000000;

struct Stack {
    int arr[MAX_SIZE];
    int front = 0, index = 0;

    void push(int n) {
        if (index >= MAX_SIZE) {
            outf << "ERROR\n";
            return;
        }
        arr[index++] = n;
//        cout << "ok\n";
    }

    void pop() {
        if (front == index) {
            outf << "ERROR\n";
            return;
        }
//        cout << arr[index - 1] << "\n"; index--;
    }

    void clear() {
        front = index = 0;
//        cout << "ok\n";
    }

    int size() {
        return index - front;
    }

    void back_element() {
        if (front == index) {
            outf << "ERROR\n";
            return;
        }
//        cout << arr[index - 1] << "\n";
    }
};

int main() {
    Stack s;
    char command;
    int num;
    ifstream inf("input.txt");

    while ((inf.get() >> command), command != '\377')
    {
        switch (command)
        {
            case '+':
                inf >> num;
                s.push(num);
                break;
            case '-':
                s.pop();
                break;
        }
    }
    inf.close();
    int countEl = s.size();

    if(countEl != 0)
    {
        for(int index = 0; index < countEl; index++)
        {
            outf << s.arr[index];
        }
    }
    else
    {
        outf << "EMPTY";
    }
    outf.close();

    return 0;
}