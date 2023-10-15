Money.h

  #include <iostream>

class Money {
private:
    long* rubles;
    unsigned char* kopecks;

public:
    /// <summary>
    /// Конструктор по умолчанию
    /// </summary>
    Money();
    /// <summary>
    /// конструктор копирования
    /// </summary>
    /// <param name="other">сумма</param>
    Money(const Money& other);
    /// <summary>
    /// без сылочный конструктор
    /// </summary>
    /// <param name="r">рубли</param>
    /// <param name="k">копейки</param>
    Money(long r, unsigned char k);
    ~Money();
    /// <summary>
    /// Перегруженный оператор присваивания
    /// </summary>
    /// <param name="other">сумма</param>
    /// <returns>рубли и копейки</returns>
    long& GetRubles() { return *rubles; }
    unsigned char& GetKopecks() { return *kopecks; }
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
    /// <summary>
    /// функция умножения объекта типа Money на скаляр
    /// </summary>
    /// <param name="scal">скаляр</param>
    /// <returns>результат умножения рублей и копеек на скаляр</returns>
    Money MultiplyByScalar(double& scal);
};

Money.cpp

#include <iostream>
#include "Money.h"

Money::Money() : rubles(new long(0)), kopecks(new unsigned char(0)) {}
Money::Money(long r, unsigned char k) : rubles(new long(r)), kopecks(new unsigned char(k)) {}
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

    long result = long(*rubles * 100 + int(*kopecks)) + long(*other.rubles * 100 + int(*other.kopecks));
    long r = 0;
    unsigned char k = 0;
    while (result >= 100) {
        r += 1;
        result -= 100;
    }
    k = result;
    return Money(r, k);
}

Money Money::operator-(const Money& other) const {
    long result = long(*rubles * 100 + int(*kopecks)) - long(*other.rubles * 100 + int(*other.kopecks));
    long r = 0;
    unsigned char k = 0;
    while (result >= 100) {
        r += 1;
        result -= 100;
    }
    k = result;
    return Money(r, k);
}

bool Money::operator==(const Money& other) const {
    return *rubles == *other.rubles && *kopecks == *other.kopecks;
}

bool Money::operator!=(const Money& other) const {
    return !(*this == other);
}

bool Money::operator<(const Money& other) const {
    if (*rubles < *other.rubles) {
        return true;
    }
    else if (*rubles > *other.rubles) {
        return false;
    }
    else {
        return *kopecks < *other.kopecks;
    }
}

bool Money::operator>(const Money& other) const {
    return !(*this < other || *this == other);
}

std::ostream& operator<<(std::ostream& os, const Money& money) {
    os << *money.rubles << "," << static_cast<int>(*money.kopecks);
    return os;
}

std::istream& operator>>(std::istream& is, Money& money) {
    char comma;
    is >> *money.rubles >> comma >> *money.kopecks;
    return is;
}

Money Money::MultiplyByScalar(double& scal) {
    long allKop = long(*rubles * 100 + int(*kopecks));
    allKop *= scal;
    *rubles = 0;
    *kopecks = 0;
    while (allKop >= 100) {
        *rubles += 1;
        allKop -= 100;
    }
    *kopecks = allKop;
    return *this;
}


Payment.h

  #include <string>
#include "Money.h"

class Payment {
private:
    std::string fullname;
    Money* salary;
    int* employmentYear;
    double* bonusPercentage;
    double* incomeTax;
    int* workedDays;
    int* workingDays;
    Money* earnings;
    Money* deductions;

public:
    /// <summary>
    /// конструктор 
    /// </summary>
    /// <param name="name">Имя сотрудника</param>
    /// <param name="salary">оклад</param>
    /// <param name="year">Год</param>
    /// <param name="bonusPercentage">Процент надбавки</param>
    /// <param name="incomeTax">Подоходный налог</param>
    /// <param name="workedDays">Отработанные дни</param>
    /// <param name="workingDays">Рабочие дни</param>
    /// <param name="employmentYear">Год поступления на работу</param>
    Payment(const std::string name, Money salary, int year, double bonusPercentage, double incomeTax,
        int workedDays, int workingDays, int employmentYear);
    /// <summary>
    /// Конструктор по умолчанию
    /// </summary>
    Payment();
    /// <summary>
    /// Вычисление начислений
    /// </summary>
    /// <returns>размер начислений</returns>
    Money calculateEarnings();
    /// <summary>
    /// Вычислений удержаний
    /// </summary>
    /// <returns>размер удержаний</returns>
    Money calculateDeductions();
    /// <summary>
    /// Вычисление начислений с учётом вычетов
    /// </summary>
    /// <returns></returns>
    Money calculateNetPayment();
    /// <summary>
    /// Вычисление опыта работы
    /// </summary>
    /// <returns>опыт работы</returns>
    int calculateExperience();
    ~Payment();
};


Payment.cpp

  
#include "Payment.h"

Payment::Payment(const std::string name, Money salary, int year, double bonusPercentage, double incomeTax,
    int workedDays, int workingDays, int employmentYear)
{
    this->salary = new Money(salary);
    this->bonusPercentage = new double(bonusPercentage);
    this->incomeTax = new double(incomeTax);
    this->workedDays = new int(workedDays);
    this->workingDays = new int(workingDays);
    this->deductions = new Money();
    this->earnings = new Money();
    this->employmentYear = new int(employmentYear);

}

Payment::Payment() {
    this->salary = new Money();
    this->bonusPercentage = new double(0.0);
    this->incomeTax = new double();
    this->workedDays = new int(0);
    this->workingDays = new int(0);
    this->deductions = new Money();
    this->earnings = new Money();
    this->employmentYear = new int(0);
}

Money Payment::calculateEarnings()
{
    double res = int(*workedDays / *workingDays);
    Money baseEarnings = salary->MultiplyByScalar(res);
    Money bE(baseEarnings);
    Money bonus;
    bonus = bE.MultiplyByScalar(*bonusPercentage);
    *earnings = baseEarnings + bonus;
    return *earnings;
}

Money Payment::calculateDeductions()
{
    double res = 0.01;
    Money er(*earnings);
    Money er2(*earnings);
    Money pensionFund = er.MultiplyByScalar(res);
    er = (er2 - pensionFund);
    Money tax = er.MultiplyByScalar(*incomeTax);
    *deductions = pensionFund + tax;
    return *deductions;
}

Money Payment::calculateNetPayment()
{
    return (*earnings - *deductions);
}

int Payment::calculateExperience()
{
    int currentYear = 2023;  
    return currentYear - *employmentYear;
}
Payment::~Payment() {
    delete salary;
    delete employmentYear;
    delete bonusPercentage;
    delete incomeTax;
    delete workedDays;
    delete workingDays;
    delete earnings;
    delete deductions;
}

main.cpp

  #include "Payment.h"
#include <Windows.h>
#include <iostream>

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Money salary(long(30000), unsigned char(0));
    Money bonusPer(10000, 0);
    Payment employee("Иванов Иван Иванович", salary, 2018, 0.1, 0.13, 24, 22, 2018);
    Money earnings = employee.calculateEarnings();
    Money deductions = employee.calculateDeductions();
    Money netPayment = employee.calculateNetPayment();
    int experience = employee.calculateExperience();

    std::cout << "Начисленная сумма: " << earnings << std::endl;
    std::cout << "Удержанная сумма: " << deductions << std::endl;
    std::cout << "Сумма, выдаваемая на руки: " << netPayment << std::endl;
    std::cout << "Стаж: " << experience << " лет" << std::endl;

    return 0;
}
