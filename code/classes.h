//
// Created by Ryzen on 21. 6. 2025.
//

#ifndef HEADER_H
#define HEADER_H

#include <unordered_map>
#include <string>
#include <iostream>

class User {
private:
    std::string login;          //meno
    std::string password;       //heslo
    std::string note;           //Poznamka
    std::string key;            //indetifikacia usera na vyhladavanie

public:
    //Constructors
    User() = default;
    User(const std::string& login, const std::string& password, const std::string& note, const std::string& key);

    //getters
    std::string getLogin() const;
    std::string getPassword() const;
    std::string getNote() const;
    std::string getKey() const;

    //setters
    void setLogin(const std::string& newLogin);
    void setPassword(const std::string& newPassword);
    void setNote(const std::string& newNote);
    void setKey(const std::string& newKey);

    //methods
    void displayUserInfo() const;
    std::string toString() const;
    static User fromString(const std::string& str);
};

class Database {
private:
    std::unordered_map<std::string, User> users;
    std::string filename;

public:
    Database(const std::string& filename = "users.txt");
    ~Database();

    //errors
    void userNotFound(const std::string& key);
    void userAlreadyExists(const std::string& key);

    //users managment
    bool addUser(const std::string& login, const std::string& password, const std::string& note, const std::string& key);
    bool deleteUser(const std::string& key);
    User* findUser(const std::string& key);
    bool editUserNote(const std::string& key, const std::string& newNote);
    void clear();

    //database methods
    void displayAllUsers() const;
    size_t getUserCount() const;

    //file handling
    void saveToFile() const;
    void loadFromFile();



};

class DbInterface {
private:
    Database& db;

    void displayMenu();
    void addUserInterface();
    void findUserInterface();
    void editNoteInterface();
    void deleteUserInterface();

public:
    DbInterface(Database& db);
    void run();
};

#endif //HEADER_H
