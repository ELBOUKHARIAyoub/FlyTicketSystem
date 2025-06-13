#include "User.h"

User::User(int i, const std::string& u, const std::string& p, const std::string& r)
    : id(i), username(u), password(p), role(r) {}

int User::getId() const {
    return id;
}

std::string User::getUsername() const {
    return username;
}

std::string User::getPassword() const {
    return password;
}

std::string User::getRole() const {
    return role;
}

void User::setUsername(const std::string& u) {
    username = u;
}

void User::setPassword(const std::string& p) {
    password = p;
}

void User::setRole(const std::string& r) {
    role = r;
}
