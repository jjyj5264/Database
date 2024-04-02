#include "database.h"
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>

int main() {
    std::string userInputCommand = "";
    std::string userInputKey = "";
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
            // 3. add()

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
        }
    }
}
