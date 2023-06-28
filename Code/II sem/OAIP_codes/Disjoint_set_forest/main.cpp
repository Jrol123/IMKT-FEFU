#include <iostream>
#include <vector>
#define vec std::vector
#define pr std::pair

template<typename type>
void print(type item)
{
    std::cout << item << std::endl;
}

/**
 * @brief Класс DSF (Disjoint Set Forest) для упорядочивания множеств.
 *
 * DSF позволяет объединять множества и определять, в каком множестве находится элемент.
 *
 * @tparam type Тип элементов множества.
 */
template<typename type>
struct DSF
{
private:
    /**
     * @brief Массив множеств.
     *
     * Реализован как множество пар. \n
     * Номер множества — элемент.
     */
    vec<pr<unsigned int, type>> mass_elements;

    /**
     * @brief Количество элементов.
     *
     * Нужно для проверки на выход за рамки массива.
     */
    unsigned int size;

    /**
     * @brief Функция для проверки вводимых пользователем индексов на соответствие пределам.
     *
     * @param index Вводимый пользователем индекс.
     * @return bool — Находится ли индекс в допустимых пределах.
     */
    bool check_bounds(const unsigned int& index)
    {
        return (0 < index <= size);
    }

    /**
     * @brief Вспомогательный метод для объединения множеств.
     *
     * @param child_index Индекс элемента, чьё множество нужно добавить в множество parent_index.
     * @param parent_index Индекс элемента, в множество которого добавляется множество child_index.
     */
    void combine_private(const unsigned int &child_index, const unsigned int &parent_index)
    {
        mass_elements[child_index].first = parent_index;
    }

    /**
     * @brief Вспомогательный метод для получения номера множества элемента.
     *
     * @Эвристики< <b> Сжатие пути</b> \n
     * Используется эвристика сжатия пути. \n
     * Заключается в обновлении ссылок на родительские узлы таким образом, чтобы они указывали непосредственно на корневой узел. \n
     * Более подробно описано на сайте: \n
     * https://neerc.ifmo.ru/wiki/index.php?title=СНМ_(реализация_с_помощью_леса_корневых_деревьев)
     *
     * @param index_item Индекс элемента, номер множества которого нужно получить.
     * @return int — Номер множества, в котором находится элемент.
     */
    int get_private(const unsigned int &index_item)
    {
        if (mass_elements[index_item].first != index_item)
        {
            mass_elements[index_item].first = get_private(mass_elements[index_item].first);
        }
        return mass_elements[index_item].first;
    }

public:

    /**
     * @brief Конструктор класса DSF.
     *
     * Изначально у каждого элемента своё множества.
     *
     * @param size Количество элементов в множестве.
     * @param elements Вектор элементов множества.
     */
    DSF(const unsigned int &size, const vec<type> &elements)
    {
        this->size = size;
        mass_elements.resize(size);
        for (unsigned int index = 0; index < size; index++)
        {
            mass_elements[index].first = index;
            mass_elements[index].second = elements[index];
        }
    }

    /**
     * @brief Метод для объединения множеств.
     *
     * Индексы вводятся относительно пользователя (начиная с 1-цы).
     *
     * @param child_index Индекс элемента, чьё множество нужно добавить в множество parent_index.
     * @param parent_index Индекс элемента, в множество которого добавляется множество child_index.
     * @pre 0 < < index <= size
     */
    void combine(const unsigned int &child_index, const unsigned int &parent_index)
    {
        if (!check_bounds(child_index) || !check_bounds(parent_index))
        {
            return;
        }
        return combine_private(child_index - 1, parent_index - 1);
    }

    /**
     * @brief Метод для получения номера множества элемента.
     *
     * Индекс вводится относительно пользователя (начиная с 1-цы).
     *
     * @param index_item Индекс элемента, номер множества которого нужно получить.
     * @return int — Номер множества, в котором находится элемент.
     * @pre 0 < index <= size
     */
    int get(const unsigned int &index_item)
    {
        if (!check_bounds(index_item))
        {
            return -1;
        }
        return get_private(index_item - 1) + 1;
    }
};

/**
 * @brief Пример использования класса DSF
 */
void example_usage()
{
    // Создание объекта класса DSF.
    DSF<int> dsf (5, {1, 2, 3, 4, 5});

    // Объединение множеств, в которых находятся элементы с индексами 1 и 2.
    dsf.combine(1, 2);

    // Получение номера множества, в котором находится элемент с индексом 1.
    int set_number = dsf.get(1);

    // Вывод.
    print(set_number);
}

/**
 * @brief Проверка на анти-переписывание всего.
 */
void test1()
{
    DSF<int> dsf (5, {1, 2, 3, 4, 5});

    dsf.combine(1, 2);

    int set_number1 = dsf.get(1);
    int set_number3 = dsf.get(3);

    print(set_number1);
    print(set_number3);

    print("");
}

/**
 * Проверка на выход за пределы массива.
 */
void test2()
{
    DSF<int> dsf (5, {1, 2, 3, 4, 5});

    dsf.combine(1, 2);

    int set_number = dsf.get(6);

    print(set_number);

    print("");
}

int main()
{
    test1();
//    test2();

    return 0;
}