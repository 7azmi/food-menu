#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

class MenuItem {
public:
    std::string name;
    std::string category;
    double price;

    MenuItem(std::string name, std::string category, double price) : name(name), category(category), price(price) {

    }
};

class FoodOrderingSystem {
private:
    std::vector<MenuItem> menu;

public:
    void loadMenuItems(const std::string& filename) {
        std::ifstream file(filename);
        std::string line, name, category;
        double price;

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::getline(ss, name, ',');
            std::getline(ss, category, ',');
            ss >> price;
            menu.push_back(MenuItem(name, category, price));
        }
    }

    void printMenu() const {
        for (const auto& item : menu) {
            std::cout << "Name: " << item.name << ", Category: " << item.category << ", Price: $" << item.price << std::endl;
        }
    }


    void sortMenuByName() {
        std::sort(menu.begin(), menu.end(), [](const MenuItem& a, const MenuItem& b) {
            return a.name < b.name;
        });
    }

    void sortMenuByPrice() {
        std::sort(menu.begin(), menu.end(), [](const MenuItem& a, const MenuItem& b) {
            return a.price < b.price;
        });
    }

    void searchMenuByName(const std::string& searchName) {
        bool found = false;
        for (const auto& item : menu) {
            if (item.name.find(searchName) != std::string::npos) {
                std::cout << "Found: " << item.name << ", Category: " << item.category << ", Price: $" << item.price << std::endl;
                found = true;
            }
        }
        if (!found) {
            std::cout << "No items found with name: " << searchName << std::endl;
        }
    }

    void searchMenuByCategory(const std::string& searchCategory) {
        bool found = false;
        for (const auto& item : menu) {
            if (item.category == searchCategory) {
                std::cout << "Found: " << item.name << ", Category: " << item.category << ", Price: $" << item.price << std::endl;
                found = true;
            }
        }
        if (!found) {
            std::cout << "No items found in category: " << searchCategory << std::endl;
        }
    }

};


int main() {
    FoodOrderingSystem system;
    system.loadMenuItems("menu.txt"); // Load menu items from the file

    int choice;
    std::string input;

    do {
        std::cout << "\nFood Ordering System Menu\n";
        std::cout << "1. Print Menu\n";
        std::cout << "2. Sort Menu by Name\n";
        std::cout << "3. Sort Menu by Price\n";
        std::cout << "4. Search Menu by Name\n";
        std::cout << "5. Search Menu by Category\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                system.printMenu();
                break;
            case 2:
                system.sortMenuByName();
                system.printMenu();
                break;
            case 3:
                system.sortMenuByPrice();
                system.printMenu();
                break;
            case 4:
                std::cout << "Enter name to search: ";
                std::cin.ignore(); // Clear newline left in the buffer
                std::getline(std::cin, input);
                system.searchMenuByName(input);
                break;
            case 5:
                std::cout << "Enter category to search: ";
                std::cin.ignore(); // Clear newline left in the buffer
                std::getline(std::cin, input);
                system.searchMenuByCategory(input);
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