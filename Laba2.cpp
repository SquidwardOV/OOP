Money.h

#include <iostream>

class Money {
private:
    long* rubles;
    unsigned char* kopecks;

public:
    Money();
    /// <summary>
    /// конструктор
    /// </summary>
    /// <param name="rubles">рубли</param>
    /// <param name="kopecks">копейки</param>
    Money(long* rubles, unsigned char* kopecks);
    /// <summary>
    /// конструктор копирования
    /// </summary>
    /// <param name="other">сумма</param>
    Money(const Money& other);
    ~Money();
    /// <summary>
    /// Перегруженный оператор присваивания
    /// </summary>
    /// <param name="other">сумма</param>
    /// <returns>рубли и копейки</returns>
    Money& operator=(const Money& other);

    /// <summary>
    /// Перегруженный оператор сложения
    /// </summary>
    /// <param name="other">сумма</param>
    /// <returns>рубли и копейки</returns>
    Money operator+(const Money& other)const;

    /// <summary>
    /// перегруженный оператор вычитания
    /// </summary>
    /// <param name="other">сумма</param>
    /// <returns>рубли и копейки</returns>
    Money operator-(const Money& other)const;
    /// <summary>
    /// перегруженный оператор сравнения
    /// </summary>
    /// <param name="other">сумма</param>
    /// <returns>рубли и копейки</returns>
    bool operator==(const Money& other)const;
    /// <summary>
    /// перегруженный оператор неравенства
    /// </summary>
    /// <param name="other">сумма</param>
    /// <returns>рубли и копейки</returns>
    bool operator!=(const Money& other)const;
    /// <summary>
    /// перегруженные оператор сравнения
    /// </summary>
    /// <param name="other">сумма</param>
    /// <returns>рубли и копейки</returns>
    bool operator<(const Money& other)const;
    /// <summary>
    /// перегруженный оператор сравнения
    /// </summary>
    /// <param name="other">сумма</param>
    /// <returns>рубли и копейки</returns>
    bool operator>(const Money& other)const;
    /// <summary>
    /// перегруженная операци ввода
    /// </summary>
    /// <param name="os">поток</param>
    /// <param name="money">сумма</param>
    /// <returns>рубли и копейки</returns>
    friend std::ostream& operator<<(std::ostream& os, const Money& money);

    /// <summary>
    /// перегруженная операция вывода
    /// </summary>
    /// <param name="is">поток</param>
    /// <param name="money">сумма</param>
    /// <returns>рубли и копейки</returns>
    friend std::istream& operator>>(std::istream& is, Money& money);
};


Money.cpp

#include "Money.h"

Money::Money() : rubles(new long(0)), kopecks(new unsigned char(0)) {}

Money::Money(long* rubles, unsigned char* kopecks) : rubles(rubles), kopecks(kopecks) {}

Money::Money(const Money& other) : rubles(new long(*other.rubles)), kopecks(new unsigned char(*other.kopecks)) {}

Money::~Money() {
    delete rubles;
    delete kopecks;
}

Money& Money::operator=(const Money& other) {
    if (this != &other) {
        *rubles = *other.rubles;
        *kopecks = *other.kopecks;
    }
    return *this;
}

Money Money::operator+(const Money& other) const {
    long sum_rubles = *rubles + *other.rubles;
    unsigned char sum_kopecks = *kopecks + *other.kopecks;
    if (sum_kopecks >= 100) {
        sum_rubles += 1;
        sum_kopecks -= 100;
    }
    return Money(new long(sum_rubles), new unsigned char(sum_kopecks));
}

Money Money::operator-(const Money& other) const {
    long diff_rubles = *rubles - *other.rubles;
    unsigned char diff_kopecks = *kopecks - *other.kopecks;
    if (diff_kopecks < 0) {
        diff_rubles -= 1;
        diff_kopecks += 100;
    }
    return Money(new long(diff_rubles), new unsigned char(diff_kopecks));
}

bool Money::operator==(const Money& other) const {
    return (*rubles == *other.rubles) && (*kopecks == *other.kopecks);
}

bool Money::operator!=(const Money& other) const {
    return !(*this == other);
}

bool Money::operator<(const Money& other) const {
    if (*rubles < *other.rubles) {
        return true;
    }
    else if (*rubles == *other.rubles) {
        return *kopecks < *other.kopecks;
    }
    return false;
}

bool Money::operator>(const Money& other) const {
    return !(*this < other) && (*this != other);
}

std::ostream& operator<<(std::ostream& os, const Money& money) {
    os << *money.rubles << " рублей " << static_cast<int>(*money.kopecks) << " копеек";
    return os;
}

std::istream& operator>>(std::istream& is, Money& money) {
    is >> *money.rubles >> *money.kopecks;
    return is;
}



main.cpp

#include "Money.h"
#include <iostream>
#include <windows.h>

int main() {

    SetConsoleOutputCP(1251);
    Money money1(new long(10), new unsigned char(50));
    Money money2(new long(5), new unsigned char(30));

    Money money3 = money1 + money2;
    Money money4 = money1 - money2;

    std::cout << "money1: " << money1 << std::endl;
    std::cout << "money2: " << money2 << std::endl;
    std::cout << "money1 + money2: " << money3 << std::endl;
    std::cout << "money1 - money2: " << money4 << std::endl;

    return 0;
}
