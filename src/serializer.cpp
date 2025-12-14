#include "serializer.h"

namespace neon
{

void Serializer::WriteUint64(std::vector<uint8_t>& out, uint64_t v)
{
    for (int i = 0; i < 8; ++i)
    {
        out.push_back(static_cast<uint8_t>(v & 0xff));
        v >>= 8;
    }
}

uint64_t Serializer::ReadUint64(const std::vector<uint8_t>& in, size_t& offset)
{
    uint64_t v = 0;

    for (int i = 0; i < 8; ++i)
    {
        v |= static_cast<uint64_t>(in[offset++]) << (8 * i);
    }

    return v;
}

void Serializer::WriteString(std::vector<uint8_t>& out, const std::string& str)
{
    WriteUint64(out, str.size());
    out.insert(out.end(), str.begin(), str.end());
}

std::string Serializer::ReadString(const std::vector<uint8_t>& in, size_t& offset)
{
    uint64_t size = ReadUint64(in, offset);
    std::string str(in.begin() + offset, in.begin() + offset + size);
    offset += size;
    return str;
}

void Serializer::WriteUint256(std::vector<uint8_t>& out, const uint256& v)
{
    const uint8_t* data = v.data();
    out.insert(out.end(), data, data + uint256::SIZE);
}

uint256 Serializer::ReadUint256(const std::vector<uint8_t>& in, size_t& offset)
{
    std::array<uint8_t, uint256::SIZE> buf;
    for (size_t i = 0; i < uint256::SIZE; ++i)
    {
        buf[i] = in[offset++];
    }
    return uint256(buf);
}

} // namespace neon
