//
// Created by Ryzen on 21. 6. 2025.
//

#include "classes.h"
#include <iostream>
#include <sstream>

#include <fstream>
//User
User::User(const std::string& login, const std::string& password, const std::string& note, const std::string& key)
    : login(login), password(password), note(note), key(key) {}

//User gettery
std::string User::getLogin() const {
    return login;
}

std::string User::getPassword() const {
    return password;
}

std::string User::getNote() const {
    return note;
}

std::string User::getKey() const {
    return key;
}

//User settery
void User::setLogin(const std::string& newLogin) {
    login = newLogin;
}

void User::setPassword(const std::string& newPassword) {
    password = newPassword;
}

void User::setNote(const std::string& newNote) {
    note = newNote;
}

void User::setKey(const std::string& newKey) {
    key = newKey;
}

void User::displayUserInfo() const {
    std::cout << "Key: " << key << std::endl;
    std::cout << "Login: " << login << std::endl;
    std::cout << "Note: " << note << std::endl;
    std::cout << "----------------------------" << std::endl;
}

std::string User::toString() const {
    return key + "|" + login + "|" + password + "|" + note + "|";
}

User User::fromString(const std::string& str) {
    std::stringstream ss(str);
    std::string login, password, note, key;

    std::getline(ss, key, '|');
    std::getline(ss, login, '|');
    std::getline(ss, password, '|');
    std::getline(ss, note, '|');

    return User(login,  password, note, key);
}

//Database
Database::Database(const std::string& filename) : filename(filename) {
    loadFromFile();
}
Database::~Database() {
    saveToFile();
}

//errors:
void Database::userNotFound(const std::string& key) {
    std::cout << "ERROR: User with key '" << key << "' not found!" << std::endl;
}

void Database::userAlreadyExists(const std::string& key) {
    std::cout << "ERROR: User with key '" << key << "' already exists!" << std::endl;
}

//users management

//Add user
bool Database::addUser(const std::string& login, const std::string& password, const std::string& note, const std::string& key) {


    if (users.find(key) != users.end()) {
        userAlreadyExists(key);
        return false;
    }

    users[key] = User(login, password, note, key);
    std::cout << "User added successfully." << std::endl;
    return true;
}

//find user by key
User* Database::findUser(const std::string& key) {
    auto it = users.find(key);
    if (it != users.end()) {
        return &it->second;
    } else {
        userNotFound(key);
        return nullptr;
    }
}

//edit note
bool Database::editUserNote(const std::string& key, const std::string& newNote) {
    User *user = findUser(key);
    if (user != nullptr) {
        user->setNote(newNote);
        std::cout << "Note updated successfully." << std::endl;
        return true;
    } else {

        return false;
    }
}

void Database::clear() {
    users.clear();
    std::cout << "All users have been removed from the database." << std::endl;
}

//delete user
bool Database::deleteUser(const std::string& key) {
    auto it = users.find(key);
    if (it != users.end()) {
        users.erase(it);
        std::cout << "User with key '" << key << "' deleted successfully." << std::endl;
        return true;
    } else {
        userNotFound(key);
        return false;
    }
}

//display all users
void Database::displayAllUsers() const {
    if (users.empty()) {
        std::cout << "No users found!" << std::endl;
        return;
    }

    std::cout << "All users from database:" << std::endl;
    std::cout << "-----------------------" << std::endl;
    for (const auto& pair : users) {
        pair.second.displayUserInfo();
    }
}

size_t Database::getUserCount() const {
    return users.size();
}

void Database::saveToFile() const {
    std::ofstream file(filename);

    if (!file) {
        std::cout << "ERROR: could not open file for writing!" << std::endl;
        return;
    }

    for (const auto& pair : users) {
        file << pair.second.toString() << std::endl;
    }
    file.close();
}

void Database::loadFromFile() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            User user = User::fromString(line);
            users[user.getKey()] = user;
        }
    }
    file.close();
}

//database interface

DbInterface::DbInterface(Database& db) : db(db) {}

// Main loop
void DbInterface::run() {
    std::cout << "=== SIMPLE USER DATABASE ===" << std::endl;
    std::cout << db.getUserCount() << " loaded users" << std::endl;

    int choice;
    do {
        displayMenu();
        std::cout << "Chose action: ";
        std::cin >> choice;
        std::cin.ignore(); //clear buffer

        switch (choice) {
            case 1:
                addUserInterface();
                break;
            case 2:
                findUserInterface();
                break;
            case 3:
                editNoteInterface();
                break;
            case 4:
                deleteUserInterface();
                break;
            case 5:
                db.displayAllUsers();
                break;
            case 6:
                db.clear();
                break;
            case 0:
                std::cout << "Saving database..." << std::endl;
                break;
            default:
                std::cout << "Choice invalid, please try again" << std::endl;
        }

        if (choice != 0) {
            std::cout << "\npress enter to continue...";
            std::cin.get();
        }

    } while (choice != 0);
}

// Show the main menu
void DbInterface::displayMenu() {
    std::cout << "\n=== MENU ===" << std::endl;
    std::cout << "1. Add user" << std::endl;
    std::cout << "2. Find user" << std::endl;
    std::cout << "3. Edit note" << std::endl;
    std::cout << "4. Delete user" << std::endl;
    std::cout << "5. Display all users" << std::endl;
    std::cout << "6. Clear database" << std::endl;
    std::cout << "0. Quit" << std::endl;
}

// interface for user
void DbInterface::addUserInterface() {
    std::string login, password, note, key;

    std::cout << "Enter key: ";
    std::getline(std::cin, key);

    std::cout << "Enter Login: ";
    std::getline(std::cin, login);

    std::cout << "Enter Password: ";
    std::getline(std::cin, password);

    std::cout << "Enter note: ";
    std::getline(std::cin, note);

    db.addUser(login, password, note, key);
}

// interface to find user
void DbInterface::findUserInterface() {
    std::string key;
    std::cout << "Enter key: ";
    std::getline(std::cin, key);

    User* user = db.findUser(key);
    if (user != nullptr) {
        std::cout << "User found:" << std::endl;
        user->displayUserInfo();
    } else {
        std::cout << "User with key '" << key << "' not found." << std::endl;
    }
}

// Interface to edit note
void DbInterface::editNoteInterface() {
    std::string key, newNote;
    std::cout << "Enter user key: ";
    std::getline(std::cin, key);

    std::cout << "Enter new note: ";
    std::getline(std::cin, newNote);

    db.editUserNote(key, newNote);
}

// interface to delete user
void DbInterface::deleteUserInterface() {
    std::string key;
    std::cout << "Enter user key to delete the user: ";
    std::getline(std::cin, key);

    std::cout << "Are u sure u want to delete the user '" << key << "'? (y/n): ";
    std::string confirmation;
    std::getline(std::cin, confirmation);

    if (confirmation == "y" || confirmation == "Y") {
        db.deleteUser(key);
    } else {
        std::cout << "Operation terminated." << std::endl;
    }
}