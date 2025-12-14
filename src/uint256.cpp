#include "uint256.h"

#include <cstring>
#include <cryptopp/hex.h>
#include <cryptopp/filters.h>

uint256::uint256()
{
    m_bytes.fill(0);
}

uint256::uint256(const std::array<uint8_t, SIZE>& bytes)
    : m_bytes(bytes)
{
}

const uint8_t* uint256::data() const
{
    return m_bytes.data();
}

uint8_t* uint256::data()
{
    return m_bytes.data();
}

bool uint256::operator==(const uint256& other) const
{
    return m_bytes == other.m_bytes;
}

bool uint256::operator!=(const uint256& other) const
{
    return !(*this == other);
}

bool uint256::operator<(const uint256& other) const
{
    return std::memcmp(
        m_bytes.data(),
        other.m_bytes.data(),
        SIZE
    ) < 0;
}

std::string uint256::ToHex() const
{
    std::string encoded;
    CryptoPP::HexEncoder encoder(
        new CryptoPP::StringSink(encoded),
        false
    );

    encoder.Put(m_bytes.data(), SIZE);
    encoder.MessageEnd();

    return encoded;
}

uint256 uint256::FromHex(const std::string& hex)
{
    uint256 out;

    CryptoPP::HexDecoder decoder;
    decoder.Put(
        reinterpret_cast<const uint8_t*>(hex.data()),
        hex.size()
    );
    decoder.MessageEnd();

    decoder.Get(out.m_bytes.data(), SIZE);

    return out;
}
