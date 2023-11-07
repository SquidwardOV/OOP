body.h

#pragma once

class Body {
public:
    virtual double getSurfaceArea() = 0;
    virtual double getVolume() = 0;
};


ball.h

  #include "body.h"

class Ball : public Body {
public:
    Ball();
    Ball(double radius);
    double getSurfaceArea() override;
    double getVolume() override;

private:
    double radius;
};


ball.cpp

#include "ball.h"
#include <cmath>
#include <iostream>

Ball::Ball() {
    radius = 0;
}

Ball::Ball(double radius) : radius(radius) {}

double Ball::getSurfaceArea() {
    return 4 * 3.14 * (radius * radius);
}

double Ball::getVolume() {
    double a = 4;
    return double(a / 3) * 3.14 * pow(radius, 3);
}



parallelepiped.h

#include "body.h"

class Parallelepiped : public Body {
public:
    Parallelepiped();
    Parallelepiped(double length, double width, double height);
    double getSurfaceArea() override;
    double getVolume() override;
  
private:
    double length;
    double width;
    double height;
};


parallelepiped.cpp

  #include "parallelepiped.h"

Parallelepiped::Parallelepiped() : length(0), width(0), height(0) {};
Parallelepiped::Parallelepiped(double length, double width, double height)
    : length(length), width(width), height(height) {}

double Parallelepiped::getSurfaceArea() {
    return 2 * (length * width + length * height + width * height);
}

double Parallelepiped::getVolume() {
    return length * width * height;
}


main.cpp

#include "parallelepiped.h"
#include "ball.h"
#include <iostream>
#include <windows.h>

void print(Body* b)
{
    std::cout << "Площадь: " << b->getSurfaceArea() << std::endl;
    std::cout << "Объём: " << b->getVolume() << std::endl;
}

int main() {
    SetConsoleOutputCP(1251);
    Parallelepiped p(2.0, 3.0, 4.0);
    print(&p);
   

    Ball b(5);
    print(&b);

    return 0;
}
