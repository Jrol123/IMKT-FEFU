#include <algorithm>
#include <vector>
#include <iostream>
#include <string>

enum Rank
{
    Six = 6,
    Seven = 7,
    Eight = 8,
    Nine = 9,
    Ten = 10,
    Joker = 11,
    Queen = 12,
    King = 13,
    Ace = 14,
    Lover = 69,
    Attorney = 420,
    MKN = 999,
    //Name = x
}; // Присваивание числу x string-значение

enum Test
{
    T = 6,
    Y, // Далее автоматически идёт нумерация с 7 и т. д.
    U,
    I
};

typedef struct coord
{
    int age;
    std::string name;
    Rank FavouriteNumber;

    coord(int age, std::string name, Rank Symbol)
    {
        this->age = age;
        this->name = name;
        this->FavouriteNumber = Symbol;
    }//Конструктор

    coord(int age, std::string name)
    {
        this->age = age;
        this->name = name;
        this->FavouriteNumber = Rank::Six;
    }//Можно создавать несколько конструкторов для разных входных данных

    void birthday()
    {
        age += 1;
        std::cout << "Happy Birthday, " << name << std::endl;
        std::cout << "Your age now is: " << age << std::endl;

        std::cout << std::endl;
    }

    void setAge(int age)
    {
        this->age = age; // this -> Указывает на локальность этой переменной. (+ смотри на цветовую идентификацию)
        std::cout << "Now you're: " << this->age << std::endl;

        std::cout << std::endl;
    }

    void rankUp(int iCount)
    {
        Rank NewRank = (Rank)(int(FavouriteNumber) + iCount); // Перевод из типа Rank в int, прибавляем нужное значение, переводим обратно в Rank
        FavouriteNumber = NewRank; // Не обязательно использовать this-> всегда
        std::cout << "Now you're: " << this->FavouriteNumber << std::endl;

        std::cout << std::endl;
    }// Функция

    void rankUp()
    {
        Rank NewRank = (Rank)(int(FavouriteNumber) + 1);
        FavouriteNumber = NewRank;
        std::cout << "Now you're: " << this->FavouriteNumber << std::endl;

        std::cout << std::endl;
    }//Можно создавать несколько функций для разных входных данных
}person; // Бессмысленное называние структуры coord кличкой person

int main()
{
    person Lila =  person(11, "Lila", Rank::Queen);
    person Daemon = coord(11, "Daemon"); // Обратите внимание на вызываемый конструктор!

    Lila.birthday();
    Lila.setAge(18);
    Lila.setAge(22);

    std::cout << (int)Lila.FavouriteNumber + 1 << std::endl;

    std::cout << std::endl;

    std::cout << Lila.name << " " << Lila.age << " " << Lila.FavouriteNumber << std::endl << std::endl;
    std::cout << Daemon.name << " " << Daemon.age << " " << Daemon.FavouriteNumber << std::endl << std::endl;

    std::cout << std::endl;

    Lila.rankUp(2);
    Daemon.rankUp();
}