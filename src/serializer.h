#ifndef NEONCOIN_SERIALIZE_H
#define NEONCOIN_SERIALIZE_H

#include "uint256.h"
#include <cstdint>
#include <string>
#include <vector>

namespace neon
{

class Serializer
{
public:
    static void WriteUint64(std::vector<uint8_t>& out, uint64_t v);
    static uint64_t ReadUint64(const std::vector<uint8_t>& in, size_t& offset);

    static void WriteString(std::vector<uint8_t>& out, const std::string& str);
    static std::string ReadString(const std::vector<uint8_t>& in, size_t& offset);

    static void WriteUint256(std::vector<uint8_t>& out, const uint256& v);
    static uint256 ReadUint256(const std::vector<uint8_t>& in, size_t& offset);
};

} // namespace neon

#endif // NEONCOIN_SERIALIZE_H
