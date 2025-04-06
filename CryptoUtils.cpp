#include "CryptoUtils.h"
#include <openssl/sha.h>
#include <openssl/ec.h>
#include <openssl/evp.h>
#include <openssl/bn.h>
#include <openssl/obj_mac.h>
#include <iostream>

void CryptoUtils::hashPasswordPinRouting(const std::string& password, const std::string& pin, const std::string& routing_number, unsigned char* output) {
    std::string combined = password + pin + routing_number;
    SHA256(reinterpret_cast<const unsigned char*>(combined.c_str()), combined.size(), output);
}

EC_KEY* CryptoUtils::createECKey(const unsigned char* hash) {
    EC_GROUP* ec_group = EC_GROUP_new_by_curve_name(NID_X9_62_prime256v1);
    EC_KEY* ec_key = EC_KEY_new();
    EC_KEY_set_group(ec_key, ec_group);

    BIGNUM* priv_key = BN_bin2bn(hash, SHA256_DIGEST_LENGTH, nullptr);
    EC_KEY_set_private_key(ec_key, priv_key);

    EC_POINT* pub_key = EC_POINT_new(ec_group);
    EC_POINT_mul(ec_group, pub_key, priv_key, nullptr, nullptr, nullptr);
    EC_KEY_set_public_key(ec_key, pub_key);

    BN_free(priv_key);
    EC_POINT_free(pub_key);
    EC_GROUP_free(ec_group);

    return ec_key;
}

size_t CryptoUtils::savePublicKey(EC_KEY* ec_key, unsigned char* pub_key_raw) {
    const EC_GROUP* ec_group = EC_KEY_get0_group(ec_key);
    return EC_POINT_point2oct(ec_group, EC_KEY_get0_public_key(ec_key), POINT_CONVERSION_UNCOMPRESSED, pub_key_raw, 65, nullptr);
}

size_t CryptoUtils::savePrivateKey(EC_KEY* ec_key, unsigned char* priv_key_raw) {
    const BIGNUM* priv_key = EC_KEY_get0_private_key(ec_key);
    return BN_bn2bin(priv_key, priv_key_raw);
}
