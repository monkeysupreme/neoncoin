#ifndef NEONCOIN_CRYPTO_H
#define NEONCOIN_CRYPTO_H

#include "uint256.h"

#include <cryptopp/asn.h>
#include <cryptopp/eccrypto.h>
#include <cryptopp/keccak.h>
#include <cryptopp/osrng.h>
#include <cryptopp/secblock.h>
#include <vector>
#include <array>

namespace neon
{

class CKeccak256
{
public:
    static constexpr size_t HASHSIZE = 32;

    CKeccak256();

    std::vector<unsigned char> Hash(const unsigned char* data, size_t len);

    std::vector<unsigned char> Hash(const std::string& data);

    std::string HashHex(const std::string& data);

    uint256 Hash256(const std::string& data);

private:
    CryptoPP::Keccak_256 mKeccak;
};

class CPrivateKey
{
public:
    CPrivateKey();
    explicit CPrivateKey(const std::vector<uint8_t>& raw);

    std::vector<unsigned char> GetPrivateKey() const;
    std::vector<unsigned char> GetPublicKey(bool compressed = true) const;

    std::vector<unsigned char> Sign(const std::vector<uint8_t>& msg) const;

private:
    CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::Keccak_256>::PrivateKey mPrivateKey;

    void LoadFromBytes(const std::vector<uint8_t>& raw);
};

} // namespace neon

#endif // NEONCOIN_CRYPTO_H
