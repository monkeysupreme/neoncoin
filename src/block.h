#ifndef NEONCOIN_BLOCK_H
#define NEONCOIN_BLOCK_H

#include "uint256.h"
#include "serializer.h"
#include "transaction.h"

#include <string>
#include <vector>

class CBlockHeader
{
public:
    int32_t Version;
    uint256 PrevBlockHash;
    uint256 MerkleRoot;
    uint32_t Time;
    uint32_t GasUsed;
    uint32_t GasLimit;

    CBlockHeader();

    void SetNull();

    std::string ToString();

    std::vector<uint8_t> Serialize() const;
};

class CBlock : public CBlockHeader
{
public:
    std::vector<CTransaction> Vtx;

    CBlock();

    std::vector<uint8_t> Serialize() const;
};

#endif // NEONCOIN_BLOCK_H
