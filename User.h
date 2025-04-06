#ifndef USER_H
#define USER_H

#include <string>

struct UserCredentials {
    std::string routing_number;
    unsigned long account_number;
    std::vector<unsigned char> public_key;
    std::vector<unsigned char> private_key;
};

class User {
public:
    static UserCredentials createNewUser(const std::string& password, const std::string& pin, const std::string& routing_number);
    static UserCredentials verifyReturningUser(const std::string& password, const std::string& pin, const std::string& routing_number, const std::string& input_account_number);
};

#endif // USER_H
