#include <iostream>
#include <fstream>
using namespace std;

struct Node
{
    int val;
    Node *next, *prev;

    void push_back()
    {
        Node *buff = new Node;
    }
};

int main()
{
    ifstream inf("input.txt");
    ofstream outf("output.txt");

    Node c = Node(11);


}