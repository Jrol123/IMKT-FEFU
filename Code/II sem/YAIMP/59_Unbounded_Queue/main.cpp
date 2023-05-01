#include <iostream>

struct Node
{
    int val;
    Node * next = nullptr;
    explicit Node(int v): val(v){}
};

struct Queue
{
    int size = 0;
    Node *top = nullptr;

    void push(int val)
    {
        if (top == nullptr)
        {
            top = new Node(val);
            size++;
        }
        else
        {
            Node *cur = top;
            while (cur->next != nullptr)
            {
                cur = cur->next;
            }
            cur->next = new Node(val);
            size++;
        }
    }

    void pop()
    {
        Node * cur = top;
        top = top->next;
        delete cur;
        size --;
    }

    void clear()
    {
        while (top != nullptr)
        {
            Node *cur = top;
            top = top->next;
            delete cur;
        }
        size = 0;
    }
};

int main()
{
    Queue mainQ;
    std::string input;
    while((std::cin >> input), input != "exit")
    {
        switch (input[1])
        {
            case 'u':
                std::cin >> input;
                mainQ.push(std::stoi(input));
                std::cout << "ok" <<  std::endl;
                break;
            case 'o':
                if(mainQ.size > 0)
                {
                    std::cout << mainQ.top->val << std::endl;
                    mainQ.pop();
                }
                else
                {
                    std::cout << "error" <<  std::endl;
                }
                break;
            case 'r':
                if(mainQ.size > 0)
                {
                    std::cout << mainQ.top->val << std::endl;
                }
                else
                {
                    std::cout << "error" <<  std::endl;
                }
                break;
            case 'i':
                std::cout << mainQ.size << std::endl;
                break;
            case 'l':
                mainQ.clear();
                std::cout << "ok" <<  std::endl;
                break;
        }
    }
    std:: cout << "bye\n";
    return 0;
}
