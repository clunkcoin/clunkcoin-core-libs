#ifdef _WIN32
    #define EXPORT_API __declspec(dllexport)
#else
    #define EXPORT_API __attribute__((visibility("default")))
#endif

#include "User.h"
#include "RoutingNumberGenerator.h"

// C-style struct for crossing DLL boundary
typedef struct {
    char routing_number[256];
    unsigned long account_number;
    unsigned char public_key[65];  // Size based on uncompressed public key
    unsigned char private_key[32]; // Size based on private key
    size_t public_key_len;
    size_t private_key_len;
    char error[512];
    bool success;
} ExportedCredentials;

extern "C" {
    // API functions that will be exported
    EXPORT_API ExportedCredentials createNewUser(const char* password, const char* pin) {
        ExportedCredentials result = {0}; // Zero-initialize the struct
        
        try {
            UserCredentials creds = User::createNewUser(password, pin);
            strncpy(result.routing_number, creds.routing_number.c_str(), sizeof(result.routing_number) - 1);
            result.account_number = creds.account_number;
            
            // Copy public key
            result.public_key_len = creds.public_key.size();
            memcpy(result.public_key, creds.public_key.data(), result.public_key_len);
            
            // Copy private key
            result.private_key_len = creds.private_key.size();
            memcpy(result.private_key, creds.private_key.data(), result.private_key_len);
            
            result.success = true;
        } catch (const std::exception& e) {
            strncpy(result.error, e.what(), sizeof(result.error) - 1);
            result.success = false;
        }
        
        return result;
    }

    EXPORT_API ExportedCredentials verifyReturningUser(const char* password, const char* pin, 
                                                      const char* routingNumber, const char* inputAccountNumber) {
        ExportedCredentials result = {0}; // Zero-initialize the struct
        
        try {
            UserCredentials creds = User::verifyReturningUser(password, pin, routingNumber, inputAccountNumber);
            strncpy(result.routing_number, creds.routing_number.c_str(), sizeof(result.routing_number) - 1);
            result.account_number = creds.account_number;
            
            // Copy public key
            result.public_key_len = creds.public_key.size();
            memcpy(result.public_key, creds.public_key.data(), result.public_key_len);
            
            // Copy private key
            result.private_key_len = creds.private_key.size();
            memcpy(result.private_key, creds.private_key.data(), result.private_key_len);
            
            result.success = true;
        } catch (const std::exception& e) {
            strncpy(result.error, e.what(), sizeof(result.error) - 1);
            result.success = false;
        }
        
        return result;
    }
}
