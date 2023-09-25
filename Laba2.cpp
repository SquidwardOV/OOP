Money.h

#include <iostream>

class Money {
private:
    long rubles;
    unsigned char kopecks;

public:
    Money();
    Money(long rubles, unsigned char kopecks);
    Money(const Money& other);
    ~Money();

    Money& operator=(const Money& other);

    Money operator+(const Money& other) const;
    Money operator-(const Money& other) const;

    bool operator==(const Money& other) const;
    bool operator!=(const Money& other) const;
    bool operator<(const Money& other) const;
    bool operator>(const Money& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Money& money);
    friend std::istream& operator>>(std::istream& is, Money& money);
};


Money.cpp

  #include "money.h"

Money::Money() : rubles(0), kopecks(0) {}

Money::Money(long rubles, unsigned char kopecks) : rubles(rubles), kopecks(kopecks) {}

Money::Money(const Money& other) : rubles(other.rubles), kopecks(other.kopecks) {}

Money::~Money() {}

Money& Money::operator=(const Money& other) {
    if (this != &other) {
        rubles = other.rubles;
        kopecks = other.kopecks;
    }
    return *this;
}

Money Money::operator+(const Money& other) const {
    long sum_rubles = rubles + other.rubles;
    unsigned char sum_kopecks = kopecks + other.kopecks;
    if (sum_kopecks >= 100) {
        sum_rubles += 1;
        sum_kopecks -= 100;
    }
    return Money(sum_rubles, sum_kopecks);
}

Money Money::operator-(const Money& other) const {
    long diff_rubles = rubles - other.rubles;
    unsigned char diff_kopecks = kopecks - other.kopecks;
    if (diff_kopecks < 0) {
        diff_rubles -= 1;
        diff_kopecks += 100;
    }
    return Money(diff_rubles, diff_kopecks);
}

bool Money::operator==(const Money& other) const {
    return (rubles == other.rubles) && (kopecks == other.kopecks);
}

bool Money::operator!=(const Money& other) const {
    return !(*this == other);
}

bool Money::operator<(const Money& other) const {
    if (rubles < other.rubles) {
        return true;
    }
    else if (rubles == other.rubles) {
        return kopecks < other.kopecks;
    }
    return false;
}

bool Money::operator>(const Money& other) const {
    return !(*this < other) && (*this != other);
}

std::ostream& operator<<(std::ostream& os, const Money& money) {
    os << money.rubles << " рублей " << static_cast<int>(money.kopecks) << " копеек";
    return os;
}

std::istream& operator>>(std::istream& is, Money& money) {
    is >> money.rubles >> money.kopecks;
    return is;
}



main.cpp

  #include "Money.h"
#include <iostream>
#include <windows.h>

int main() {

    SetConsoleOutputCP(1251);
    Money money1(10, 50);
    Money money2(5, 30);

    Money money3 = money1 + money2;
    Money money4 = money1 - money2;

    std::cout << "money1: " << money1 << std::endl;
    std::cout << "money2: " << money2 << std::endl;
    std::cout << "money1 + money2: " << money3 << std::endl;
    std::cout << "money1 - money2: " << money4 << std::endl;

    return 0;
}