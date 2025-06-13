#include "UserManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

UserManager::UserManager(const std::string& filePath) : filePath(filePath) {
    loadUsersFromFile();
}

void UserManager::loadUsersFromFile() {
    users.clear(); // avoid duplicating
    std::ifstream file(filePath);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int id;
        std::string username, password, role;
        if (iss >> id >> username >> password >> role) {
            users.emplace_back(id, username, password, role);
            std::cout << "Loaded user: " << username << ", " << password << ", " << role << std::endl;
        }
    }
}

void UserManager::saveUsersToFile() const {
    std::ofstream file(filePath, std::ios::trunc);
    for (const auto& user : users) {
        file << user.getId() << " " << user.getUsername() << " "
             << user.getPassword() << " " << user.getRole() << "\n";
    }
}

User* UserManager::authenticate(const std::string& username, const std::string& password) {
    std::cout << "[DEBUG] Authenticating: " << username << ", " << password << std::endl;

    for (User& user : users) {
        if (user.getUsername() == username && user.getPassword() == password) {
            return &user;
        }
    }
    return nullptr;
}

const std::vector<User>& UserManager::getUsers() const {
    return users;
}

void UserManager::addUser(const User& user) {
    users.push_back(user);
    saveUsersToFile();
}

void UserManager::deleteUserById(int id) {
    users.erase(
        std::remove_if(users.begin(), users.end(),
            [id](const User& u) { return u.getId() == id; }
        ),
        users.end()
    );
    saveUsersToFile();
}

void UserManager::updateUser(const User& updatedUser) {
    for (auto& user : users) {
        if (user.getId() == updatedUser.getId()) {
            user = updatedUser;
            break;
        }
    }
    saveUsersToFile();
}

User* UserManager::getUserById(int id) {
    for (auto& user : users) {
        if (user.getId() == id) {
            return &user;
        }
    }
    return nullptr;
}

int UserManager::generateNewUserId() const {
    int maxId = 0;
    for (const auto& user : users) {
        if (user.getId() > maxId) {
            maxId = user.getId();
        }
    }
    return maxId + 1;
}
