#include "User.h"
#include "CryptoUtils.h"
#include "RoutingNumberGenerator.h"
#include <iostream>

UserCredentials User::createNewUser(const std::string& password, const std::string& pin) {
    std::string routingNumber = RoutingNumberGenerator::generateRoutingNumber();
    UserCredentials credentials;
    credentials.routing_number = routingNumber;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    unsigned char pub_key_raw[65];
    unsigned char priv_key_raw[32];
    CryptoUtils::hashPasswordPinRouting(password, pin, routingNumber, hash);
    EC_KEY* ec_key = CryptoUtils::createECKey(hash);
    size_t pub_len = CryptoUtils::savePublicKey(ec_key, pub_key_raw);
    size_t priv_len = CryptoUtils::savePrivateKey(ec_key, priv_key_raw);
    credentials.account_number = 0;
    for (int i = 0; i < 12; i++) {
        credentials.account_number = (credentials.account_number * 10) + (pub_key_raw[i] % 10);
    }
    credentials.public_key = std::vector<unsigned char>(pub_key_raw, pub_key_raw + pub_len);
    credentials.private_key = std::vector<unsigned char>(priv_key_raw, priv_key_raw + priv_len);
    // Cleanup resources
    EC_KEY_free(ec_key);
    return credentials;
}

UserCredentials User::verifyReturningUser(const std::string& password, const std::string& pin, const std::string& routing_number, const std::string& input_account_number) {
    UserCredentials credentials;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    unsigned char pub_key_raw[65];
    unsigned char priv_key_raw[32];
    CryptoUtils::hashPasswordPinRouting(password, pin, routing_number, hash);
    EC_KEY* ec_key = CryptoUtils::createECKey(hash);
    size_t pub_len = CryptoUtils::savePublicKey(ec_key, pub_key_raw);
    size_t priv_len = CryptoUtils::savePrivateKey(ec_key, priv_key_raw);
    credentials.routing_number = routing_number;
    credentials.account_number = 0;
    for (int i = 0; i < 12; i++) {
        credentials.account_number = (credentials.account_number * 10) + (pub_key_raw[i] % 10);
    }
    credentials.public_key = std::vector<unsigned char>(pub_key_raw, pub_key_raw + pub_len);
    credentials.private_key = std::vector<unsigned char>(priv_key_raw, priv_key_raw + priv_len);
    EC_KEY_free(ec_key);
    return credentials;
}
