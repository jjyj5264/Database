#ifndef DATABASE_H
#define DATABASE_H

#include <string>

enum Type { INT, DOUBLE, STRING, ARRAY };

struct Array {
  int size;
  Type type;
  void *items;
};

struct Entry {
  Type type;
  std::string key;
  void *value;
};

struct Database {
  Entry **entries; // Entry pointer array
  int size; // The number of entries.
  int capacity; // The 'maximum number of entries' that the program can hold.
};

// 엔트리를 생성한다.
Entry *create(Type type, std::string key, void *value); // Notice the 'value' argument.

// 데이터베이스를 초기화한다.
void init(Database &database);

// 데이터베이스에 엔트리를 추가한다.
void add(Database &database, Entry *entry);

// 데이터베이스에서 키에 해당하는 엔트리를 찾는다.
Entry *get(Database &database, std::string &key);

// 데이터베이스에서 키에 해당하는 엔트리를 제거한다.
void remove(Database &database, std::string &key);

// 데이터베이스를 해제한다.
void destroy(Database &database);

// 내가만든것들*원래있던거아님*이거관리해줘야함
void list(Database &database);
void printEntry(Entry *entry);

#endif