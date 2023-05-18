#include <iostream>
#include <vector>
#define input std::cin
#define output std::cout
#define vec std::vector

struct Node
{
private:
    int cost = INT_MIN;
    short index = INT_MIN;
    vec<Node*> vector_parents;
    vec<int> vector_costs;

    void findLowestCostNode()
    {
        int lowestCost = INT_MAX;
        for(short index = 0; index < vector_parents.size(); ++index)
        {
            lowestCost = std::min(lowestCost, vector_parents[index]->get_cost());
        }
        cost = lowestCost;
    }
public:
    int get_cost()
    {
        if (cost == INT_MIN)
        {
            this->findLowestCostNode();
        }
        return this->cost;
    }
    short get_index()
    {
        return index;
    }
    void set_index(const short &val)
    {
        index = val;
    }
    void set_cost(const short &val)
    {
        cost = val;
    }
    void add_parent(Node * node)
    {
        this->vector_parents.push_back(node);
    }
    void add_cost(const int &val)
    {
        this->vector_costs.push_back(val);
    }
};

int main()
{
    short countCities;
    input >> countCities;
    vec<Node> graph(countCities);

//    vec<vec<int>> vector_smezhnost;
    for (short index = 0; index < countCities; ++index)
    {
        graph[index].set_index(index + 1);
//        vector_smezhnost.push_back(vec<int>());
        for(short subIndex = 0; subIndex < countCities; ++subIndex)
        {
            int len;
            input >> len;

            if (len != 0)
            {
                graph[subIndex].add_parent(&graph[index]);
                graph[subIndex].add_cost(len);
            }

//            vector_smezhnost[index].push_back(len);
        }
    }

    short first_city, second_city;
    input >> first_city >> second_city;
    graph[first_city - 1]. = 0;

    output << graph[second_city - 1].get_cost() << std::endl;

//    for(int index = 0; index < countCities; index++)
//    {
//        vector_costs[index].set_index(index);
//    }

}