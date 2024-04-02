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
    int userInputSize = 0;
    Type currentType;

    Database *database = new Database;
    init(*database);

    while (true) {
        
        std::cout << "command (list, add, get, del, exit): ";
        std::cin >> userInputCommand;

        if (userInputCommand == "list") {
            list(*database);
        } else if (userInputCommand == "add") {
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
            } else if (userInputType == "double") {
                currentType = DOUBLE;
                double *value = new double;
                std::cin >> *value;
                Entry *entry = create(currentType, userInputKey, value);
                add(*database, entry);
            } else if (userInputType == "string") {
                currentType = STRING;
                std::string *value = new std::string;
                std::getline(std::cin >> std::ws, *value);
                Entry *entry = create(currentType, userInputKey, value);
                add(*database, entry);
            } else if (userInputType == "array") {
                bool isNested = false;
                currentType = ARRAY;
                std::cout << "type (int, double, string, array): ";
                std::cin >> userInputType;
                if (userInputType == "int") { currentType = INT; }
                if (userInputType == "double") { currentType = DOUBLE; }
                if (userInputType == "string") { currentType = STRING; }
                if (userInputType == "array") { currentType = ARRAY, isNested = true; }
                std::cout << "size: ";
                std::cin >> userInputSize;
                
                if (!isNested) { // 1-Dimensional
                    Array *array = new Array;
                    array->type = currentType; // Can't be ARRAY in this case.
                    array->size = userInputSize;

                    if (array->type == INT) {
                        int *arr = new int[array->size];
                        for (int i = 0; i < array->size; i++) {
                            std::cout << "item[" << i << "]: ";
                            std::cin >> arr[i];
                        }
                        array->items = arr;
                    } if (array->type == DOUBLE) {
                        double *arr = new double[array->size];
                        for (int i = 0; i < array->size; i++) {
                            std::cout << "item[" << i << "]: ";
                            std::cin >> arr[i];
                        }
                        array->items = arr;
                    } if (array->type == STRING) {
                        std::string *arr = new std::string[array->size];
                        for (int i = 0; i < array->size; i++) {
                            std::cout << "item[" << i << "]: ";
                            std::getline(std::cin >> std::ws, arr[i]);
                        }
                        array->items = arr;
                    }

                    add(*database, create(ARRAY, userInputKey, array));
                } else if (isNested) { // 2-Dimensional
                    Array *array = new Array;
                    array->type = ARRAY;
                    array->size = userInputSize;

                    Array **arr = new Array *[array->size];

                    array->items = arr;
                    add(*database, create(ARRAY, userInputKey, array));
                }
            }
        } else if (userInputCommand == "get") {
            std::cout << "key: ";
            std::cin >> userInputKey;
            
            if (get(*database, userInputKey) != nullptr) {
                printEntry(get(*database, userInputKey));
            } else {
                std::cout << "Not found. try anothey key." << std::endl;
            }
        } else if (userInputCommand == "del") {
            std::cout << "key: ";
            std::cin >> userInputKey;
            remove(*database, userInputKey);
        } else if (userInputCommand == "exit") {
            destroy(*database); // RUN THIS FIRST if you're running on potato PC.
            exit(0);
        } else {
            std::cout << "Invalid Command. try another." << std::endl;
        }
    }
}
