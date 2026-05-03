#ifndef INVENTORY_MANAGER_HPP
#define INVENTORY_MANAGER_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

const std::string DATABASE_FILE = "Inventory.csv";

// Data structure to represent a Product as an object instead of a string
struct Product {
    std::string name;
    int stock;
    double price;
};

class ProductManager {
private:
    // HELPER: Loads the entire CSV into a vector of Product objects
    std::vector<Product> loadDatabase() {
        std::vector<Product> products;
        std::ifstream readFile(DATABASE_FILE);
        std::string line;

        while (std::getline(readFile, line)) {
            if (line.empty()) continue;
            
            std::stringstream ss(line);
            std::string name, s_stock, s_price;

            if (std::getline(ss, name, ',') &&
                std::getline(ss, s_stock, ',') &&
                std::getline(ss, s_price, ',')) {
                try {
                    products.push_back({name, std::stoi(s_stock), std::stod(s_price)});
                } catch (...) { continue; } // Skip corrupted lines
            }
        }
        readFile.close();
        return products;
    }

    // HELPER: Saves the vector of Products back to the CSV
    bool saveDatabase(const std::vector<Product>& products) {
        std::ofstream writeFile(DATABASE_FILE, std::ios::trunc); 
        if (!writeFile.is_open()) return false;

        for (const auto& p : products) {
            writeFile << p.name << "," << p.stock << "," << p.price << "\n";
        }
        writeFile.close();
        return true;
    }

public:
    // Create new product using the append method for efficiency[cite: 1]
    bool insertNewProduct(std::string name, int stock, double price) {
        std::ofstream updateFile(DATABASE_FILE, std::ios::app);
        if (updateFile.is_open()) {
            updateFile << name << "," << stock << "," << price << "\n";
            return true;
        }
        return false;
    }

    bool findAndDeleteProduct(std::string name) {
        auto products = loadDatabase();
        bool found = false;

        for (auto it = products.begin(); it != products.end(); ++it) {
            if (it->name == name) { // Exact matching[cite: 1]
                products.erase(it);
                found = true;
                break;
            }
        }
        return found ? saveDatabase(products) : false;
    }

    bool findAndUpdateProduct(std::string name, int newStock, double newPrice) {
        auto products = loadDatabase();
        for (auto& p : products) {
            if (p.name == name) {
                p.stock = newStock;
                p.price = newPrice;
                return saveDatabase(products);
            }
        }
        return false;
    }

    bool checkIfProductExists(std::string name) {
        auto products = loadDatabase();
        for (const auto& p : products) {
            if (p.name == name) return true;
        }
        return false;
    }

    bool checkIfStockIsLow(std::string name, int threshold) {
        auto products = loadDatabase();
        for (const auto& p : products) {
            if (p.name == name) return p.stock < threshold;
        }
        return false;
    }

    bool checkIfDatabaseIsEmpty() {
        return loadDatabase().empty(); // Simple and clean[cite: 1]
    }

    // Constructor handles initial setup[cite: 1]
    ProductManager() {
        std::ifstream check(DATABASE_FILE);
        if (!check.is_open()) {
            std::cout << "Database not found. Creating..." << std::endl;
            std::ofstream create(DATABASE_FILE);
        }
    }
};

#endif