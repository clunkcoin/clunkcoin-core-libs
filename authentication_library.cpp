#ifdef _WIN32
    #define EXPORT_API __declspec(dllexport)
#else
    #define EXPORT_API __attribute__((visibility("default")))
#endif

#include "User.h"
#include "RoutingNumberGenerator.h"

extern "C" {
    // API functions that will be exported
    EXPORT_API UserCredentials createNewUser(const char* password, const char* pin, const char* routingNumber) {
        return User::createNewUser(password, pin, routingNumber);
    }

    EXPORT_API UserCredentials verifyReturningUser(const char* password, const char* pin, const char* routingNumber, const char* inputAccountNumber) {
        return User::verifyReturningUser(password, pin, routingNumber, inputAccountNumber);
    }
}
