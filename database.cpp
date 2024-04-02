#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "database.h"

// enum Type { INT, DOUBLE, STRING, ARRAY };

// struct Array {
//   int size;
//   Type type;
//   void *items;
// };

// struct Entry {
//   Type type;
//   std::string key;
//   void *value;
// };

// struct Database {
//   Entry **entries; // Entry pointer array
//   int size; // The number of entries.
//   int capacity; // The 'maximum number of entries' that the program can hold.
// };

/**
 * 1. We have to know the type, key(string), and value.
 * 2. Assume that wrong type cannot pass through.
*/
Entry *create(Type type, std::string key, void *value) {
    Entry *entry = new Entry;
    entry->type = type;
    entry->key = key;
    entry->value = value;

    return entry;
}

/**
 * WIP
*/
void init(Database &database) { // Don't run this multiple times.
    database.size = 0; // Size means the number of entries.
    database.capacity = 10; // Capacity means the 'maximum number of entries' that the program can hold.
    database.entries = new Entry *[database.capacity]; // Makes 'Entry pointer array' with size of database.capacity.
}

/**
 * WIP
*/
void add(Database &database, Entry *entry) {
    // When it's too big.
    if (database.size == database.capacity) {
        database.capacity *= 2; // Fix this.
        Entry **tmpEntries = new Entry *[database.capacity]; // A new array with *Entry.

        for (int i = 0; i < database.size; i++) { // Copy and paste.
            tmpEntries[i] = database.entries[i];
        }
        
        delete[] database.entries; // Remove the former obsolete *Entry array.
        database.entries = tmpEntries; // Replace with the new one.
    }

    // Add new entry.
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
    std::cout << "size: " << database.size << std::endl;
    std::cout << "void list();" << std::endl;
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
        // Do something...
        break;
    }
    std::cout << "void printEntry();" << std::endl;

    std::cout << std::endl;
}