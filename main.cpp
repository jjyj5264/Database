#include "database.h"
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>

int main() {
    std::string userInputCommand = "";
    std::string userInputKey = "";
    std::string userInputType = "";
    Type currentType;

    Database *database = new Database;
    std::cout << "Database *database = new Database;" << std::endl;
    init(*database);

    while (true) {
        
        std::cout << "command (list, add, get, del, exit): ";
        std::cin >> userInputCommand;

        if (userInputCommand == "list") { // ●
            list(*database);

        } else if (userInputCommand == "add") { // ○
            // 1. handle user input.
            // 2. create Entry with *create()
            // 3. and add()

            // Set key & type
            std::cout << "key: ";
            std::cin >> userInputKey;
            std::cout << "type (int, double, string, array): ";
            std::cin >> userInputType;

            // Create Entry
            std::cout << "value: ";
            if (userInputType == "int") {
                currentType = INT;
                int *value = new int;
                std::cin >> *value; // Due to value is a pointer, *value means the actual value of data which *value points.
                Entry *entry = create(currentType, userInputKey, value);
                add(*database, entry);
                std::cout << "add() int" << std::endl;
            } else if (userInputType == "double") {
                currentType = DOUBLE;
                double *value = new double;
                std::cin >> *value;
                Entry *entry = create(currentType, userInputKey, value);
                add(*database, entry);
                std::cout << "add() double" << std::endl;
            } else if (userInputType == "string") {
                currentType = STRING;
                std::string *value = new std::string;
                std::getline(std::cin >> std::ws, *value);
                Entry *entry = create(currentType, userInputKey, value);
                add(*database, entry);
                std::cout << "add() std::string" << std::endl;
            } else if (userInputType == "array") {
                // ?
                std::cout << "add() ARRAY" << std::endl;
            }
            

        } else if (userInputCommand == "get") { // ●
            std::cout << "key: ";
            std::cin >> userInputKey;
            
            if (get(*database, userInputKey) != nullptr) {
                printEntry(get(*database, userInputKey));
            } else {
                std::cout << "Not found. try anothey key." << std::endl;
            }

        } else if (userInputCommand == "del") { // ●
            std::cout << "key: ";
            std::cin >> userInputKey;
            remove(*database, userInputKey);

        } else if (userInputCommand == "exit") { // ●
            destroy(*database); // RUN THIS FIRST if you're running on potato PC.
            exit(0);
        } else {
            std::cout << "Invalid Command. try another." << std::endl;
        }
    }
}
