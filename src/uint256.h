#ifndef NEONCOIN_UINT256_H
#define NEONCOIN_UINT256_H

#include <array>
#include <string>
#include <cstdint>

class uint256
{
public:
    static constexpr size_t SIZE = 32;

    uint256();
    explicit uint256(const std::array<uint8_t, SIZE>& bytes);

    const uint8_t* data() const;
    uint8_t* data();

    bool operator==(const uint256& other) const;
    bool operator!=(const uint256& other) const;
    bool operator<(const uint256& other) const;

    std::string ToHex() const;
    static uint256 FromHex(const std::string& hex);

private:
    std::array<uint8_t, SIZE> m_bytes;
};


#endif // NEONCOIN_UINT256_H
