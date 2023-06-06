#include <fstream>
#define strg std::string

/*
 * Идея следующая — сделать List (Set) для каждого предмета и после запроса проходить по этому листу для первого игрока и искать предмет второго.
 * Если он найден — победа первого. Если нет, то переходим ко второму игроку. Если и у него не найден, то ничья.
 */

const unsigned short max_count_items = ('z' - 'a' + 1) * 20;

struct Set
{
private:
    template<typename T>
    struct List
    {
    private:
        struct Node
        {
            T val;
            Node* next = nullptr;

            explicit Node(const T& val)
            {
                this->val = T(val);
            }
        };

    public:

        strg name= "HASH";
        Node* begin_Node = nullptr;

        List()
        = default;

        explicit List(const strg& name)
        {
            this->name = name;
        }

        void push(const T& val)
        {
            if (this->begin_Node == nullptr)
            {
                begin_Node = new Node(val);
                return;
            }
            Node* cur = this->begin_Node;
            while(cur-> next != nullptr)
            {
                cur = cur->next;
            }
            cur->next = new Node(val);
        }

        bool find(const T& val)
        {
            // shokolad
            if (this->begin_Node == nullptr)
                return false;
            Node* cur = this->begin_Node;
            if (cur->val == val)
                return true;
            while(cur->next != nullptr)
            {
                if (cur->next->val == val)
                {
                    return true;
                }
                cur = cur->next;
            }
            return false;
        }
    };

    unsigned short hash(const strg& val)
    {
        unsigned short sum = 0;

        for (const unsigned char sym:val)
        {
            sum += sym - 'a' + 1;
        }

        return sum - 1;
    }

    List<List<strg>> space[max_count_items];

    auto find(const strg& val)
    {
        unsigned short val_dom = hash(val); // t

        auto* cur = space[val_dom].begin_Node;
        while(cur->val.name != val)
        {
            cur = cur->next;
        }

        return cur;
    }

public:

    void init(const strg& name)
    {
        unsigned short val_name = hash(name);
        space[val_name].push(List<strg>(name));
    }

    void push(const strg& dom, const strg& sub)
    {
        find(dom)->val.push(sub);
    }

    bool find(const strg& dom, const strg& sub)
    {
        return find(dom)->val.find(sub);
    }
};
/*
 * В теории можно сделать Set Set-ов
 */

int main()
{
    std::ifstream inf ("input.txt");
    unsigned short count_items; // 2 <= c <= 1000
    unsigned short count_pairs, count_games; // 1 <= c <= 20000
    inf >> count_items;

    Set mass;

    for(int index = 0; index < count_items; index++)
    {
        strg item;
        inf >> item;
        mass.init(item);
    } // Проименование

    inf >> count_pairs;


    for(int index = 0; index < count_pairs; index++)
    {
        strg item1, item2;
        inf >> item1 >> item2;
        mass.push(item1, item2);
    } // Добавление пар предметов

    inf >> count_games;

    std::ofstream outf("output.txt");

    for(int index = 0; index < count_games; index++)
    {
        strg item1, item2;
        inf >> item1 >> item2;
        if(mass.find(item1, item2))
        {
            outf << "1 ";
        }
        else if(mass.find(item2, item1))
        {
            outf << "2 ";
        }
        else
        {
            outf << "0 ";
        }
    } // Сравнение


    /*
     * 1 — 1-й игрок победил
     * 2 — 2-й игрок победил
     * 0 — ничья
     */
}
