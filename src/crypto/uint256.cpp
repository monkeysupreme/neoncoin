#include "crypto/uint256.h"

#include <cstring>
#include <stdexcept>

uint256::uint256()
{
    std::memset(mData, 0, SIZE);
}

uint256::uint256(const uint8_t* data)
{
    std::memcpy(mData, data, SIZE);
}

uint256::uint256(const std::array<uint8_t, SIZE>& arr)
{
    std::memcpy(mData, arr.data(), SIZE);
}

uint8_t* uint256::begin()
{
    return mData;
}

uint8_t* uint256::end()
{
    return mData + SIZE;
}

const uint8_t* uint256::begin() const
{
    return mData;
}

const uint8_t* uint256::end() const
{
    return mData + SIZE;
}

uint8_t* uint256::data()
{
    return mData;
}

const uint8_t* uint256::data() const
{
    return mData;
}

uint8_t& uint256::operator[](size_t i)
{
    return mData[i];
}

const uint8_t& uint256::operator[](size_t i) const
{
    return mData[i];
}

bool uint256::operator==(const uint256& other) const
{
    return std::memcmp(mData, other.mData, SIZE) == 0;
}

bool uint256::operator!=(const uint256& other) const
{
    return !(*this == other);
}

bool uint256::operator<(const uint256& other) const
{
    return std::memcmp(mData, other.mData, SIZE) < 0;
}

std::string uint256::ToHex() const
{
    static const char* hex = "0123456789abcdef";
    std::string out(SIZE * 2, '0');

    for (size_t i = 0; i < SIZE; ++i) {
        uint8_t b = mData[i];
        out[2 * i]     = hex[b >> 4];
        out[2 * i + 1] = hex[b & 0x0f];
    }

    return out;
}

uint256 uint256::FromHex(const std::string& str)
{
    if (str.size() != SIZE * 2)
        throw std::runtime_error("uint256::FromHex invalid length");

    auto hexval = [](char c) -> uint8_t {
        if ('0' <= c && c <= '9') return c - '0';
        if ('a' <= c && c <= 'f') return c - 'a' + 10;
        if ('A' <= c && c <= 'F') return c - 'A' + 10;
        throw std::runtime_error("uint256::FromHex invalid char");
    };

    uint256 v;
    for (size_t i = 0; i < SIZE; ++i) {
        v.mData[i] =
            (hexval(str[2 * i]) << 4) |
             hexval(str[2 * i + 1]);
    }

    return v;
}
