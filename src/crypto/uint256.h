#ifndef NEONCOIN_UINT256_H
#define NEONCOIN_UINT256_H

#include <cstdint>
#include <cstddef>
#include <array>
#include <string>

class uint256
{
public:
    static constexpr size_t SIZE = 32;

    uint256();
    explicit uint256(const uint8_t* data);
    explicit uint256(const std::array<uint8_t, SIZE>& arr);

    uint8_t* begin();
    uint8_t* end();

    const uint8_t* begin() const;
    const uint8_t* end() const;

    uint8_t* data();
    const uint8_t* data() const;

    uint8_t& operator[](size_t i);
    const uint8_t& operator[](size_t i) const;

    bool operator==(const uint256& other) const;
    bool operator!=(const uint256& other) const;
    bool operator<(const uint256& other) const;

    std::string ToHex() const;
    static uint256 FromHex(const std::string& str);

private:
    uint8_t mData[SIZE];
};

#endif


