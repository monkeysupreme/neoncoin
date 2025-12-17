#ifndef NEONCOIN_BLOCK_H
#define NEONCOIN_BLOCK_H

#include "../crypto/uint256.h"
#include "../serializer.h"
#include "transaction.h"

#include <string>
#include <vector>

class CBlockHeader : public neon::Serializable
{
public:
    int32_t Version;
    uint256 PrevBlockHash;
    uint256 MerkleRoot;
    uint32_t Time;
    uint32_t GasUsed;
    uint32_t GasLimit;

    CBlockHeader();

    virtual void SetNull();

    std::string ToString() const;

    void Serialize(std::vector<uint8_t>& out) const override;
    void Deserialize(std::vector<uint8_t>& in, size_t& offset) override;
};

class CBlock : public CBlockHeader
{
public:
    std::vector<CTransaction> Vtx;
    uint256 Hash;

    explicit CBlock(const CBlockHeader& header);

    void SetNull() override;

    void Serialize(std::vector<uint8_t>& out) const override;
    void Deserialize(std::vector<uint8_t>& in, size_t& offset) override;
};

#endif // NEONCOIN_BLOCK_H
