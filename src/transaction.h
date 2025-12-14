#ifndef NEONCOIN_TRANSACTION_H
#define NEONCOIN_TRANSACTION_H

#include "serializer.h"
#include "uint256.h"

#include <vector>

struct STxOutPoint
{
    uint256 sTxID;
    uint32_t sIndex;
};

struct STxInput
{
    STxOutPoint sPrevOut;
    std::vector<uint8_t> sScriptSig;
    uint32_t sSequence;

    std::vector<uint8_t> Serialize() const;
};

struct STxOutput
{
    uint64_t sValue;
    std::vector<uint8_t> sScriptPubKey;

    std::vector<uint8_t> Serialize() const;
};

class CTransaction
{
public:
    uint32_t Version;
    std::vector<STxInput> Vin;
    std::vector<STxOutput> Vout;

    std::vector<uint8_t> Serialize() const;

    uint256 GetTxID() const;

    size_t GetTotalSize();
};

#endif // NEONCOIN_TRANSACTION_H
