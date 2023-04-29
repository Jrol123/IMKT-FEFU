#include <iostream>

struct Node
{
    int val;
    Node * next = nullptr;
};

struct Queue
{
    int size = 0;
    Node *top = nullptr;

    void push(int val, Node *cur, int index = 0)
    {
        if (cur == nullptr)
        {
            top = new Node(val);
            size ++;
        } else if (cur->next != nullptr)
        {
            push(val, cur->next, ++index);
        } else
        {
            cur->next = new Node(val);
            size++;
        }
    }

    void pop()
    {
        Node * cur = top;
        top = top->next;
        free(cur);
        size --;
    }
    /*
     * При очищении top, top не зануляется
     */

    void clear(Node * cur)
    {
        if(cur -> next != nullptr)
        {
            clear(cur->next);
        }
        free(cur);
        size = 0;
        top = nullptr;
    }
};

int main()
{
    Queue * mainQ = new Queue;
    std::string input;
    while((std::cin >> input), input != "exit")
    {
        switch (input[1])
        {
            case 'u':
                std::cin >> input;
                mainQ->push(std::stoi(input), mainQ->top);
                std::cout << "ok" <<  std::endl;
                break;
            case 'o':
                if(mainQ->size > 0)
                {
                    std::cout << mainQ->top->val << std::endl;
                    mainQ->pop();
                }
                else
                {
                    std::cout << "error" <<  std::endl;
                }
                break;
            case 'r':
                if(mainQ->size > 0)
                {
                    std::cout << mainQ->top->val << std::endl;;
                    break;
                }
                else
                {
                    std::cout << "error" <<  std::endl;
                }
            case 'i':
                std::cout << mainQ->size << std::endl;
                break;
            case 'l':
                mainQ->clear(mainQ->top);
                std::cout << "ok" <<  std::endl;
                break;
        }
    }
    std:: cout << "bye";
    return 0;
}
