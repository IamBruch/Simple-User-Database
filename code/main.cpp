#include "classes.h"
#include <iostream>
#include <vector>
#include <filesystem>

void addTestUsers(Database& db) {
    std::cout << "Adding 20 test users to database..." << std::endl;

    // Definícia testovacích používateľov
    std::vector<std::vector<std::string>> testUsers = {
        {"admin", "admin123", "System administrator account", "admin001"},
        {"john.doe", "password1", "Sales department manager", "emp001"},
        {"jane.smith", "secure456", "Marketing specialist", "emp002"},
    };

    int successCount = 0;
    int errorCount = 0;

    for (const auto& userData : testUsers) {
        const std::string& login = userData[0];
        const std::string& password = userData[1];
        const std::string& note = userData[2];
        const std::string& key = userData[3];

        if (db.addUser(login, password, note, key)) {
            successCount++;
        } else {
            errorCount++;
        }
    }

    std::cout << "\nTest user creation completed:" << std::endl;
    std::cout << "Successfully added: " << successCount << " users" << std::endl;
    std::cout << "Errors encountered: " << errorCount << " users" << std::endl;
    std::cout << "Total users in database: " << db.getUserCount() << std::endl;
    std::cout << "Press Enter to continue to main menu...";
    std::cin.get();
}

int main() {
    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
    Database db("users.txt");
    //uncomment to add test users
    addTestUsers(db);
    db.saveToFile();

    DbInterface interface(db);
    interface.run();
    return 0;

}