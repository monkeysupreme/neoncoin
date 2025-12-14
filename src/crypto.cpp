#include "crypto.h"

namespace neon
{

CKeccak256::CKeccak256()
{
}

std::vector<unsigned char> CKeccak256::Hash(const unsigned char* data, size_t len)
{
    std::vector<unsigned char> digest(HASHSIZE);

    mKeccak.Restart();
    mKeccak.Update(data, len);
    mKeccak.Final(digest.data());

    return digest;
}


std::vector<unsigned char> CKeccak256::Hash(const std::string& data)
{
    return Hash(reinterpret_cast<const unsigned char*>(data.data()), data.size());
}

std::string CKeccak256::HashHex(const std::string& data)
{
    const auto digest = Hash(data);

    static const char* hex_chars = "0123456789abcdef";
    std::string hex;
    hex.reserve(digest.size() * 2);

    for (unsigned char byte : digest)
    {
        hex.push_back(hex_chars[(byte >> 4) & 0x0F]);
        hex.push_back(hex_chars[byte & 0x0F]);
    }

    return hex;
}

uint256 CKeccak256::Hash256(const std::string& data)
{
    auto bytes = Hash(data);

    std::array<uint8_t, uint256::SIZE> arr;
    std::copy(bytes.begin(), bytes.end(), arr.begin());

    return uint256(arr);
}


} // namespace neon
