#ifndef CRYPTOUTILS_H
#define CRYPTOUTILS_H

#include <string>
#include <openssl/ecdsa.h>
#include <openssl/sha.h>

class CryptoUtils {
public:
    static void hashPasswordPinRouting(const std::string& password, const std::string& pin, const std::string& routing_number, unsigned char* output);
    static EC_KEY* createECKey(const unsigned char* hash);
    static size_t savePublicKey(EC_KEY* ec_key, unsigned char* pub_key_raw);
    static size_t savePrivateKey(EC_KEY* ec_key, unsigned char* priv_key_raw);
};

#endif // CRYPTOUTILS_H
