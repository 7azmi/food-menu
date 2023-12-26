#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class MenuItem {
public:
    std::string name;
    std::string category;
    double price;

    MenuItem(std::string name = "", std::string category = "", double price = 0.0) : name(name), category(category), price(price) {}
};

class MenuItemNode {
public:
    MenuItem data;
    MenuItemNode* next;

    MenuItemNode(MenuItem data) : data(data), next(nullptr) {}
};

class FoodOrderingSystem {
private:
    MenuItemNode* head;

public:
    FoodOrderingSystem() : head(nullptr) {}

    ~FoodOrderingSystem() {
        MenuItemNode* current = head;
        while (current != nullptr) {
            MenuItemNode* next = current->next;
            delete current;
            current = next;
        }
    }

    void loadMenuItems(const std::string& filename) {
        std::ifstream file(filename);
        std::string line, name, category;
        double price;

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::getline(ss, name, ',');
            std::getline(ss, category, ',');
            ss >> price;
            addMenuItem(MenuItem(name, category, price));
        }
    }

    void addMenuItem(const MenuItem& item) {
        MenuItemNode* newNode = new MenuItemNode(item);
        if (!head) {
            head = newNode;
        } else {
            MenuItemNode* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    void deleteMenuItem(const std::string& name) {
        MenuItemNode* current = head;
        MenuItemNode* prev = nullptr;

        while (current != nullptr) {
            if (current->data.name == name) {
                if (prev == nullptr) {
                    head = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
        std::cout << "Item not found: " << name << std::endl;
    }

    void searchMenuItem(const std::string& searchName) {
        MenuItemNode* current = head;
        bool found = false;
        while (current != nullptr) {
            if (current->data.name.find(searchName) != std::string::npos) {
                std::cout << "Found: " << current->data.name << ", Category: " << current->data.category << ", Price: $" << current->data.price << std::endl;
                found = true;
            }
            current = current->next;
        }
        if (!found) {
            std::cout << "No items found with name: " << searchName << std::endl;
        }
    }

    void printMenu() const {
        MenuItemNode* current = head;
        while (current != nullptr) {
            std::cout << "Name: " << current->data.name << ", Category: " << current->data.category << ", Price: $" << current->data.price << std::endl;
            current = current->next;
        }
    }
};



int main() {
    FoodOrderingSystem system;

    system.loadMenuItems("menu.txt");

    int choice;
    std::string inputName, inputCategory;
    double inputPrice;

    do {
        std::cout << "\nFood Ordering System Menu\n";
        std::cout << "1. Add Menu Item\n";
        std::cout << "2. Delete Menu Item\n";
        std::cout << "3. Search Menu by Name\n";
        std::cout << "4. Print Menu\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter name: ";
                std::cin.ignore();
                std::getline(std::cin, inputName);
                std::cout << "Enter category: ";
                std::getline(std::cin, inputCategory);
                std::cout << "Enter price: ";
                std::cin >> inputPrice;
                system.addMenuItem(MenuItem(inputName, inputCategory, inputPrice));
                break;
            case 2:
                std::cout << "Enter name of item to delete: ";
                std::cin.ignore();
                std::getline(std::cin, inputName);
                system.deleteMenuItem(inputName);
                break;
            case 3:
                std::cout << "Enter name to search: ";
                std::cin.ignore();
                std::getline(std::cin, inputName);
                system.searchMenuItem(inputName);
                break;
            case 4:
                system.printMenu();
                break;
            case 0:
                std::cout << "Exiting the program.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}