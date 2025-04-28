/**
 * @file B_tree.cpp
 *
 * @brief Реализует методы класса Б-дерева
 */

#include "B_tree.h"
#include <vector>
/// Макрос для вектора.
#define vec std::vector

/**
 * @brief Класс Б-дерева.
 *
 * @tparam type Тип данных. Лучше всего работать с чем-то, что поддерживает операции сравнения.
 */
template<typename type>
class B_tree
{
private:
    /**
     * @brief Вершина Б-дерева.
     */
    struct Node
    {
    private:
        /// Является ли вершина листом.
        bool leaf = false;
        /// Количество ключей вершин.
        int n = 1;
        /// Ключи вершин.
        vec<type> key;
        /// Указатели на детей вершин.
        Node** c = nullptr;

    public:
        Node(const type& key, const unsigned int& size)
        {
            leaf = false;
            n = 1;
            this->key.resize(2 * size);
            this->key[0] = key;
        }
    };
    /// Минимальная степень дерева.
    unsigned int t = 2;
    /// Указатель на корень дерева.
    Node* root = nullptr;

public:
    B_tree(const type& key, const unsigned int& t = 2)
    {
        this->t = t;
        root = Node(key, t);
    }
    /**
     * @brief Вставляет ключ в дерево.
     *
     * @param key ключ, который нужно вставить.
     */
    void insert(const unsigned int& key)
    {
        Node* cur = root;
        // Если вершина полностью заполнена.
        if (cur->n == 2*t - 1)
        {

        }
        else
        {
            insert_nonFull(cur, key);
        }
    }
    void insert_nonFull(Node* cur, const unsigned int& key)
    {
        int cur_len = cur->n;
        if (cur->leaf)
        {
            while (cur_len >= 1 && key < cur->key[cur_len])
            {
                cur->key[cur_len + 1] + cur->key[cur_len];
                cur_len -= 1;
            }
            cur->key[cur_len + 1] = key;
            cur->n += 1;
        }
        else
        {
            while (cur_len >= 1 && key < cur->key[cur_len])
            {
                cur_len -= 1;
            }
            cur_len += 1;
            if (cur->c[cur_len].n == 2 * t - 1)
            {
                split_child(cur, cur_len);
                if(key > cur->key[cur_len])
                    cur_len += 1;
            }
            insert_nonFull(cur->c[cur_len], key);
        }
    }
    void split_child(Node* cur, int index)
    {

    }
    void find_key(int key)
    {

    }
};