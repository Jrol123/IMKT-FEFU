#include <iostream>
using namespace std;

struct Node
{
    int val = 0;
    Node *left;
    Node *right;
};

Node *search(Node *root, int key)
{
    if ((*root).val == 0|| root -> val == key)
    {
        return root;
    }
    else if (root -> val < key)
    {
        return search(root -> right, key);
    }
    else if (root -> val > key)
    {
        return search(root -> left, key);
    }
}

Node *add(Node *root, int key, bool moreLess)
{
    if (moreLess && root -> right == nullptr)
    {
        (*(root ->right)).val = key;
    }
    else if (root -> val < key)
    {
        return add(root -> right, key, false);
    }
    else if (root -> val > key)
    {
        return add(root -> left, key, true);
    }
}

int main()
{
    Node test;
    int num = 11;
    test.val = 20;
    cout << search(&test, num) << endl;
    add(&test, num, test.val >= num);
    cout << search(&test, num) << endl;
}
