#ifndef NEONCOIN_CRYPTO_H
#define NEONCOIN_CRYPTO_H

#include "uint256.h"

#include <vector>
#include <cryptopp/keccak.h>

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

} // namespace neon

#endif // NEONCOIN_CRYPTO_H
