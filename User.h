#ifndef USER_H
#define USER_H

#include <string>

class User {
public :
    int id;
    std::string username;
    std::string password;
    std::string role;


public:
   // User(int i, const std::string& u, const std::string& p, const std::string& r);
    User(int id, const std::string& username, const std::string& password, const std::string& role);


    int getId() const;
    std::string getUsername() const;
    std::string getPassword() const;
    std::string getRole() const;

    void setUsername(const std::string& u);
    void setPassword(const std::string& p);
    void setRole(const std::string& r);
};

#endif
