Car.h

#include <string>

class Car {
private:
    std::string* brand;
    int* numCylinders;
    int* power;

public:
    Car(std::string brand, int numCylinders, int power);
    ~Car();
    std::string* getBrand();
    int* getPower();
    void setPower(int newPower);
    void updatePower(int powerIncrease);
};

сar.cpp
  
#include "Car.h"

Car::Car(std::string brand, int numCylinders, int power) {
    this->brand = new std::string(brand);
    this->numCylinders = new int(numCylinders);
    this->power = new int(power);
}

Car::~Car() {
    delete brand;
    delete numCylinders;
    delete power;
}

std::string* Car::getBrand() {
    return brand;
}

int* Car::getPower() {
    return power;
}

void Car::setPower(int newPower) {
    *power = newPower;
}

void Car::updatePower(int powerIncrease) {
    *power += powerIncrease;
}



Lorry.h

  #include "Car.h"

class Lorry : public Car {
private:
    int* cargoCapacity;

public:
    Lorry(std::string brand, int numCylinders, int power, int cargoCapacity);
    ~Lorry();
    int* getCargoCapacity();
    void setBrand(std::string newBrand);
    void updateCargoCapacity(int capacityIncrease);
};


Lorry.cpp

  #include "Lorry.h"

Lorry::Lorry(std::string brand, int numCylinders, int power, int cargoCapacity) : Car(brand, numCylinders, power) {
    this->cargoCapacity = new int(cargoCapacity);
}

Lorry::~Lorry() {
    delete cargoCapacity;
}

int* Lorry::getCargoCapacity() {
    return cargoCapacity;
}

void Lorry::setBrand(std::string newBrand) {
    *this->getBrand() = newBrand;
}

void Lorry::updateCargoCapacity(int capacityIncrease) {
    *cargoCapacity += capacityIncrease;
}



main.cpp

  #include <iostream>
#include "Lorry.h"
#include <windows.h>

int main() {
    SetConsoleOutputCP(1251);
    Lorry lorry("Volvo", 6, 500, 2000);
    std::cout << "До переобозначения:" << std::endl;
    std::cout << "Марка грузовика: " << *lorry.getBrand() << std::endl;
    std::cout << "Мощность грузовика: " << *lorry.getPower() << std::endl;
    std::cout << "Грузоподъёмность грузовика: " << *lorry.getCargoCapacity() << std::endl;
    std::cout << std::endl;

    lorry.setPower(600);
    lorry.updateCargoCapacity(500);
    std::cout << "После переобозначения: " << std::endl;
    std::cout << "Марка грузовика: " << *lorry.getBrand() << std::endl;
    std::cout << "Мощность грузовика: " << *lorry.getPower() << std::endl;
    std::cout << "Грузоподъёмность грузовика: " << *lorry.getCargoCapacity() << std::endl;

    std::cout << std::endl;

    Car car("Mercedes", 12, 800);
    std::cout << "До переобозначения:" << std::endl;
    std::cout << "Марка машины: " << *car.getBrand() << std::endl;
    std::cout << "Мощность машины: " << *car.getPower() << std::endl;
    std::cout << std::endl;
    car.updatePower(50);
    
    std::cout << "После чиповки двигателя:" << std::endl;
    std::cout << "Марка машины: " << *car.getBrand() << std::endl;
    std::cout << "Мощность машины: " << *car.getPower() << std::endl;

    return 0;
}
  
