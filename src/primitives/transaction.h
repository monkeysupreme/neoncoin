#ifndef NEONCOIN_TRANSACTION_H
#define NEONCOIN_TRANSACTION_H

#include "../crypto/uint256.h"
#include "../serializer.h"

#include <vector>

struct STxOutPoint
{
    uint256 sTxID;
    uint32_t sIndex;
};

struct STxInput : neon::Serializable
{
    STxOutPoint sPrevOut;
    std::vector<uint8_t> sScriptSig;
    uint32_t sSequence;

    void Serialize(std::vector<uint8_t>& out) const override;
    void Deserialize(std::vector<uint8_t>& in, size_t& offset) override;
};

struct STxOutput : neon::Serializable
{
    uint64_t sValue;
    std::vector<uint8_t> sScriptPubKey;

    void Serialize(std::vector<uint8_t>& out) const override;
    void Deserialize(std::vector<uint8_t>& in, size_t& offset) override;
};

class CTransaction : public neon::Serializable
{
public:
    uint32_t Version;
    std::vector<STxInput> Vin;
    std::vector<STxOutput> Vout;

    uint256 GetTxID() const;

    size_t GetTotalSize();

    void Serialize(std::vector<uint8_t>& out) const override;
    void Deserialize(std::vector<uint8_t>& in, size_t& offset) override;
};

#endif // NEONCOIN_TRANSACTION_H
