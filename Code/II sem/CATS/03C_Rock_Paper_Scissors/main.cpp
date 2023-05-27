#include <fstream>
#include <vector>

/*
 * Идея следующая — сделать List (Set) для каждого предмета и после запроса проходить по этому листу для первого игрока и искать предмет второго.
 * Если он найден — победа первого. Если нет, то переходим ко второму игроку. Если и у него не найден, то ничья.
 */

const unsigned short max_count_items = 2440 + 1; // 'z' * 20 = 2440

struct Set
{
private:
    struct List
    {
    private:
        struct Node
        {
            std::string val;
            Node* next = nullptr;

            explicit Node(const std::string& val)
            {
                this-> val = val;
            }
        };

        Node* begin = nullptr;

    public:

        std::string item = "NONE";

        void push(const std::string& val)
        {
            if (this->begin == nullptr)
            {
                this->begin = new Node(val);
            }

            Node* cur = begin;
            bool state = true;
            if (cur->val != val)
            {
                while (cur->next != nullptr)
                {
                    cur = cur->next;
                    if (cur->val == val)
                    {
                        state = false;
                        break;
                    }
                }
                if (state)
                {
                    cur->next = new Node(val);
                }
            }
        }

        bool find(const std::string& val)
        {
            Node* cur = begin;
            if (cur->val == val)
            {
                return true;
            }
            while (cur->next != nullptr)
            {
                cur = cur->next;
                if (cur->val == val)
                {
                    return true;
                }
            }
            return false;
        }
    };

    unsigned int hash(const std::string& obj)
    {
        unsigned int sum = 0;
        for(char i : obj)
        {
            sum += i;
        }
        return sum;
    }

public:
//    std::vector<List> space(max_count_items);
    List space[max_count_items];
    void push(const std::string& item1, const std::string& item2)
    {
        int val1 = hash(item1);
        if (space[val1].item == item1)
        {
            space[val1].push(item2);
        }
        else
        {
            bool state = false;
//            throw std::runtime_error("Хеш-функция не подходит на моменте init");
            for(unsigned int index = val1 + 1; index < max_count_items; ++index)
            {
                if (space[val1].item == item1)
                {
                    space[val1].push(item2);
                    state = true;
                    break;
                }
            }
            if (!state)
            {
                for(unsigned int index = 0; index < val1; ++index)
                {
                    if (space[val1].item == item1)
                    {
                        space[val1].push(item2);
                        break;
                    }
                }
            }
        }
    }

    void init(const std::string& item)
    {
        unsigned int val1 = hash(item);
        if(space[val1].item == "NONE")
        {
            space[val1].item = item;
        }
        else
        {
            bool state = false;
//            throw std::runtime_error("Хеш-функция не подходит на моменте init");
            for(unsigned int index = val1 + 1; index < max_count_items; ++index)
            {
                if(space[val1].item == "NONE")
                {
                    space[val1].item = item;
                    state = true;
                    break;
                }
            }
            if (!state)
            {
                for(unsigned int index = 0; index < val1; ++index)
                {
                    if(space[val1].item == "NONE")
                    {
                        space[val1].item = item;
                        break;
                    }
                }
            }

        }
    }

    bool find(const std::string& item1, const std::string& item2)
    {
        int val1 = hash(item1);
        if (space[val1].item == item1)
        {
            return space[val1].find(item2);
        }
        else
        {
            bool state = false;
            for(unsigned int index = val1 + 1; index < max_count_items; ++index)
            {
                if (space[val1].item == item1)
                {
                    return space[val1].find(item2);
                }
            }
            for(unsigned int index = 0; index < val1; ++index)
            {
                if (space[val1].item == item1)
                {
                    return space[val1].find(item2);
                }
            }
        }
    }
};





int main()
{
    std::ifstream inf ("input.txt");
    unsigned short count_items; // 2 <= c <= 1000
    unsigned short count_pairs, count_games; // 1 <= c <= 20000
    inf >> count_items;

    Set mass;

    for(int index = 0; index < count_items; index++)
    {
        std::string item;
        inf >> item;
        mass.init(item);
    } // проименование

    inf >> count_pairs;


    for(int index = 0; index < count_pairs; index++)
    {
        std::string item1, item2;
        inf >> item1 >> item2;
        mass.push(item1, item2);
    }

    inf >> count_games;

    std::ofstream outf("output.txt");

    for(int index = 0; index < count_games; index++)
    {
        std::string item1, item2;
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
    }


    /*
     * 1 — 1-й игрок победил
     * 2 — 2-й игрок победил
     * 0 — ничья
     */
}
