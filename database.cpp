#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "database.h"

Entry *create(Type type, std::string key, void *value) {
    Entry *entry = new Entry;
    entry->type = type;
    entry->key = key;
    entry->value = value;

    return entry;
}

void init(Database &database) { // Don't run this multiple times.
    database.size = 0; // Size means the number of entries.
    database.capacity = 10; // Capacity means the 'maximum number of entries' that the program can hold.
    database.entries = new Entry *[database.capacity]; // Makes 'Entry Pointer Array' with size of database.capacity.
}

void add(Database &database, Entry *entry) {
    // Check if the key already exists.
    // Replacing does not costs any size or capacity. so, we don't have to check the capacity.
    for (int i = 0; i < database.size; i++) {
        if (database.entries[i]->key == entry->key) {
            // If the key exists, replace the entry.
            delete database.entries[i];
            database.entries[i] = entry;
            return; // Works same as 'break'.
        }
    }
    
    // If capacity is running out, we have to double it.
    if (database.size == database.capacity) {
        database.capacity *= 2; // database.capacity++; is VERY INEFFICIENT. DO NOT RUN THIS OFTEN.
        Entry **tmpEntries = new Entry *[database.capacity]; // A new Entry array.

        for (int i = 0; i < database.size; i++) { // Copy and paste.
            tmpEntries[i] = database.entries[i];
        }
        
        delete[] database.entries; // Remove the former obsolete *Entry array.
        database.entries = tmpEntries; // Replace with the new one.
    }

    // Add new entry & size + 1
    database.entries[database.size++] = entry;
}

Entry *get(Database &database, std::string &key) {
    for (int i = 0; i < database.size; i++) {
        if (database.entries[i]->key == key) {
            return database.entries[i]; // Return that entry.
        }
    }
    
    return nullptr; // We have to print "not found"
}

void remove(Database &database, std::string &key) {
    for (int i = 0; i < database.size; i++) {
        if (database.entries[i]->key == key) { // Found him?
            delete database.entries[i]; // Free. *IMPORTANT : RUN THIS FIRST BEFORE SHIFTING*
            database.entries[i] = database.entries[--database.size]; // SHIFTING. *VERY IMPORTANT : NOT SAME AS 'database.size--'*.

            return; // Works same as 'break'.
        }
    }

    std::cout << "Not found. try anothey key." << std::endl;
}

void destroy(Database &database) { // Call this before you run exit(0)!!!
    for (int i = 0; i < database.size; i++) { // If the size equals to 0; do nothing.
        delete database.entries[i]; // Free every Entry pointers.
    }

    delete[] database.entries; // Free 'database.entries' itself.
}

void list(Database &database) {
    for (int i = 0; i < database.size; i++) { // If the size equals to 0; runs printEntry 0 times.
        printEntry(database.entries[i]);
    }
    // std::cout << "size: " << database.size << std::endl;
}

void printArray(Array *array) {
    std::cout << "[";

    for (int i = 0; i < array->size; i++) {
        switch (array->type) {
        case INT:
            std::cout << ((int *)array->items)[i];
            break;
        case DOUBLE:
            std::cout << ((double *)array->items)[i];
            break;
        case STRING:
            std::cout << "\"" << ((std::string *)array->items)[i] << "\"";
            break;
        case ARRAY:
            /**
             * array: array points the 'Array instance'.
             * items: in this case, items points 'array of Array structure'.
             * [i]: i-th Array pointer.
             * ((Array **)array->items)[i]: casts array->items to array of Array pointer. and calls i-th index.
            */
            printArray(((Array **)array->items)[i]); // Recursive call.
            break;
        }

        if (i < array->size - 1) {
            std::cout << ", ";
        }
    }
    
    std::cout << "]";
}

void printEntry(Entry *entry) {
    std::cout << entry->key + ": ";

    switch (entry->type) {
    case INT:
        std::cout << *(int *)entry->value;
        break;
    case DOUBLE:
        std::cout << *(double *)entry->value;
        break;
    case STRING:
        std::cout << "\"" << *(std::string *)entry->value << "\"";
        break;
    case ARRAY:
        printArray((Array *)entry->value);
        break;
    }

    std::cout << std::endl;
}