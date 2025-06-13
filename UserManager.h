#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <vector>
#include <string>
#include "User.h"

class UserManager {
private:
    std::vector<User> users;
    std::string filePath = "C:/Users/HP/Documents/FlyTicketSystem/users.txt";

    void loadUsersFromFile(); // internal use

public:
    UserManager() = default;  // ✅ Add this line
    UserManager(const std::string& filePath);

    User* authenticate(const std::string& username, const std::string& password);
    const std::vector<User>& getUsers() const;
    void addUser(const User& user);
    void deleteUserById(int id);
    void updateUser(const User& user);
    User* getUserById(int id);
    int generateNewUserId() const;
  //  void saveUsersToFile() const;
    void saveUsersToFile() const;

};

#endif
