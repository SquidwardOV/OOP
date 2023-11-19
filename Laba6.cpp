list.h

  // List.h
#pragma once

#include <iostream>

template <typename T>
class List {
private:
    struct Node {
        T data;
        Node* next;

        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;

public:
    List() : head(nullptr) {}

    ~List() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    
    void insert(const T& value, Node* position) {
        if (position == nullptr) {
            if (head == nullptr) {
                Node* newNode = new Node(value);
                newNode->next = head;
                head = newNode;
            }
            else {
                Node* newNode = new Node(value);
                Node* temp = head;
                while (temp->next != nullptr) {
                    temp = temp->next;
                }
                temp->next = newNode;
            }

        }
        else {
            Node* newNode = new Node(value);
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Удаление элемента по итератору
    void erase(Node* position) {
        if (head == nullptr || position == nullptr) {
            return;
        }

        if (position == head) {
            head = head->next;
            delete position;
        }
        else {
            Node* temp = head;
            while (temp->next != position) {
                temp = temp->next;
            }

            temp->next = position->next;
            delete position;
        }
    }

    void merge(const List& other) {
        Node* temp = other.head;
        Node* mainListtemp = head;
        while (mainListtemp->next != nullptr) {
            mainListtemp = mainListtemp->next;
        }
        while (temp != nullptr) {
            mainListtemp->next = new Node(temp->data);
            mainListtemp = mainListtemp->next;
            temp = temp->next;
        }
    }

    // Слияние упорядоченных списков
    void mergeSorted(const List& other) {
        Node* temp = other.head;
        Node* mainListtemp = head;
        while (mainListtemp->next != nullptr) {
            mainListtemp = mainListtemp->next;
        }
        while (temp != nullptr) {
            mainListtemp->next = new Node(temp->data);
            mainListtemp = mainListtemp->next;
            temp = temp->next;
        }
        temp = head;
        if (head->next != nullptr) {
            mainListtemp = head->next;
            while (temp->next != nullptr) {
                while (mainListtemp != nullptr)
                {
                    if (mainListtemp->data < temp->data) {
                        T date = mainListtemp->data;
                        mainListtemp->data = temp->data;
                        temp->data = date;
                    }
                    mainListtemp = mainListtemp->next;
                }
                temp = temp->next;
                mainListtemp = temp;
            }

        }
        else {

        }


    }

    // Перегрузка оператора вывода
    friend std::ostream& operator<<(std::ostream& os, const List<T>& list) {
        Node* temp = list.head;
        while (temp != nullptr) {
            os << temp->data << " ";
            temp = temp->next;
        }
        return os;
    }

    // Перегрузка оператора ввода
    friend std::istream& operator>>(std::istream& is, List<T>& list) {
        T value;
        while (is >> value) {
            list.insert(value, nullptr);
        }
        return is;
    }

    // Итераторы
    class Iterator {
    public:
        Node* current;

        Iterator(Node* node) : current(node) {}

        T& operator*() const {
            return current->data;
        }

        Iterator& operator++() {
            current = current->next;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };

    Iterator begin() const {
        return Iterator(head);
    }

    Iterator end() const {
        return Iterator(nullptr);
    }
    
    void insert(const T& value, Iterator position) {
        if (position.current == nullptr) {
            Node* newNode = new Node(value);
            newNode->next = head;
            head = newNode;
        }
        else {
            Node* newNode = new Node(value);
            newNode->next = position.current->next;
            position.current->next = newNode;
        }
    }

    // Удаление элемента по итератору
    void erase(Iterator position) {
        if (head == nullptr || position.current == nullptr) {
            return;
        }

        if (position.current == head) {
            head = head->next;
            delete position.current;
        }
        else {
            Node* temp = head;
            while (temp->next != position.current) {
                temp = temp->next;
            }

            temp->next = position.current->next;
            delete position.current;
        }
    }
};



main.cpp


  #include <iostream>
#include "list.h"
#include <windows.h>

int main() {
    SetConsoleOutputCP(1251);
    List<int> myList;

    // Ввод элементов списка с клавиатуры
    std::cout << "Введите элементы списка (окончание ввода - любой не числовой символ): ";
    std::cin >> myList;

    std::cout << "Список: " << myList << std::endl;

    // Проверка работы итераторов
    std::cout << "Элементы списка с использованием итератора: ";
    for (auto it = myList.begin(); it != myList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Добавление элемента по итератору
    auto it = myList.begin();
    ++it;  // Переходим ко второму элементу
    myList.insert(100, it);
    std::cout << "Список после добавления элемента: " << myList << std::endl;

    // Удаление элемента по итератору
    ++it;  // Переходим к третьему элементу
    myList.erase(it);
    std::cout << "Список после удаления элемента: " << myList << std::endl;

    // Создание второго списка
    List<int> otherList;
    otherList.insert(500, nullptr);
    otherList.insert(600, nullptr);
    otherList.insert(700, nullptr);

    std::cout << "Список 2: " << otherList << std::endl;

    // Слияние двух списков
    myList.merge(otherList);
    std::cout << "Список после слияния с другим списком: " << myList << std::endl;

    // Создание третьего списка
    List<int> sortedList;
    sortedList.insert(1, nullptr);
    sortedList.insert(3, nullptr);
    sortedList.insert(5, nullptr);

    // Слияние двух упорядоченных списков
    myList.mergeSorted(sortedList);
    std::cout << "Список после слияния с упорядоченным списком: " << myList << std::endl;

    return 0;
}


