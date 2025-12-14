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

std::string CBlockHeader::ToString()
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

std::vector<uint8_t> CBlockHeader::Serialize() const
{
    std::vector<uint8_t> serialized;

    neon::Serializer::WriteUint64(serialized, static_cast<uint64_t>(Version));
    neon::Serializer::WriteUint256(serialized, PrevBlockHash);
    neon::Serializer::WriteUint256(serialized, MerkleRoot);
    neon::Serializer::WriteUint64(serialized, static_cast<uint64_t>(Time));
    neon::Serializer::WriteUint64(serialized, static_cast<uint64_t>(GasUsed));
    neon::Serializer::WriteUint64(serialized, static_cast<uint64_t>(GasLimit));

    return serialized;
}
