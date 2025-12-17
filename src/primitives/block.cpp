#include "block.h"

#include <sstream>

CBlockHeader::CBlockHeader()
{
    SetNull();
}

void CBlockHeader::SetNull()
{
    Version = 0;
    PrevBlockHash = uint256();
    MerkleRoot = uint256();
    Time = 0;
    GasUsed = 0;
    GasLimit = 0;
}

std::string CBlockHeader::ToString() const
{
    std::stringstream ss;

    ss << "CBlockHeader(";
    ss << "Version: " << Version << ", ";
    ss << "PrevBlockHash: " << PrevBlockHash.ToHex() << ", ";
    ss << "MerkleRoot: " << MerkleRoot.ToHex() << ", ";
    ss << "Time: " << Time << ", ";
    ss << "GasUsed: " << GasUsed << ", ";
    ss << "GasLimit: " << GasLimit;
    ss << ")";

    return ss.str();
}

void CBlockHeader::Serialize(std::vector<uint8_t>& out) const
{
    neon::Serializer::WriteUint64(out, Version);
    neon::Serializer::WriteUint256(out, PrevBlockHash);
    neon::Serializer::WriteUint256(out, MerkleRoot);
    neon::Serializer::WriteUint64(out, Time);
    neon::Serializer::WriteUint64(out, GasUsed);
    neon::Serializer::WriteUint64(out, GasLimit);
}

void CBlockHeader::Deserialize(std::vector<uint8_t>& in, size_t& offset)
{
    Version = neon::Serializer::ReadUint64(in, offset);
    PrevBlockHash = neon::Serializer::ReadUint256(in, offset);
    MerkleRoot = neon::Serializer::ReadUint256(in, offset);
    Time = neon::Serializer::ReadUint64(in, offset);
    GasUsed = neon::Serializer::ReadUint64(in, offset);
    GasLimit = neon::Serializer::ReadUint64(in, offset);
}

CBlock::CBlock(const CBlockHeader& header)
{
    SetNull();
    *(static_cast<CBlockHeader*>(this)) = header;
}

void CBlock::Serialize(std::vector<uint8_t>& out) const
{
    CBlockHeader::Serialize(out);
    for (const auto& tx : Vtx)
    {
        tx.Serialize(out);
    }
    neon::Serializer::WriteUint256(out, Hash);
}

void CBlock::Deserialize(std::vector<uint8_t>& in, size_t& offset)
{
    CBlockHeader::Deserialize(in, offset);
    for (auto& tx : Vtx)
    {
        tx.Deserialize(in, offset);
    }
    Hash = neon::Serializer::ReadUint256(in, offset);
}

void CBlock::SetNull()
{
    CBlockHeader::SetNull();
    Vtx.clear();
    Hash = uint256();
}



