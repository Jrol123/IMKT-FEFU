#include <fstream>
//#include <iostream>

std::ofstream outf("output.txt");
template<typename T>
struct Set
{
private:
    struct Node
    {
        T val;
        Node* left = nullptr;
        Node* right = nullptr;
        explicit Node(const T& val) : val(val) {}
    };
    Node* root = nullptr;

    Node* insert(Node* cur, const T& val)
    {
        if (cur == nullptr)
        {
            size++;
            return new Node(val);
        }
        else if (val < cur->val)
        {
            cur->left = insert(cur->left, val);
        }
        else if (val > cur->val)
        {
            cur->right = insert(cur->right, val);
        }
        return cur;
    }

    Node* remove(Node* cur, const T& val)
    {
        if (cur == nullptr)
        {
            return nullptr;
        }
        else if (val < cur->val)
        {
            cur->left = remove(cur->left, val);
        }
        else if (val > cur->val)
        {
            cur->right = remove(cur->right, val);
        }
        else
        {
            // Если только один потомок
            if (cur->left == nullptr)
            {
                Node* rightChild = cur->right;
                delete cur;
                size--;
                return rightChild;
            }
            else if (cur->right == nullptr)
            {
                Node* leftChild = cur->left;
                delete cur;
                size--;
                return leftChild;
            }
            else
            {
                Node* minRight = cur->right;
                while (minRight->left != nullptr)
                {
                    minRight = minRight->left;
                }
                cur->val = minRight->val;
                cur->right = remove(cur->right, minRight->val);
            } // Если везде есть дети
        }
        return cur;
        /*
         * К сожалению, это нельзя сократить. Необходимо запоминать весь путь для того, чтобы полностью перестроить всё.
         * Хотя, в теории, можно ничего не возвращать...
         */
    }

    Node* contains(Node* cur, const T& val)
    {
        if (cur == nullptr)
        {
            return nullptr;
        }
        else if (val < cur->val)
        {
            return contains(cur->left, val);
        }
        else if (val > cur->val)
        {
            return contains(cur->right, val);
        }
        else
        {
            return cur;
        }
    }

    void print(Node* cur)
    {
        if(cur != nullptr)
        {
            print(cur->left);
            outf << cur->val << " ";
            print(cur->right);
        }
    }

public:
    int size = 0;
    void insert(const T& val)
    {
        root = insert(root, val);
    }
    void remove(const T& val)
    {
        root = remove(root, val);
    }
    bool contains(const T& val)
    {
        return (contains(root, val) != nullptr);
    }
    void print()
    {
        print(root);
    }
};

int main()
{
    std::ifstream inf("input.txt");
    Set<int> numbers;
    int num;
    while ((inf >> num), num != 0)
    {
        if (num > 0)
        {
            numbers.insert(num);
        }
        else
        {
            numbers.remove(-num);
        }
    }
    inf.close();


    numbers.print();
    outf.close();

    return 0;
}