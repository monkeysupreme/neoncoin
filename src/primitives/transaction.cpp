#include "transaction.h"
#include "../crypto/crypto.h"

void STxInput::Serialize(std::vector<uint8_t>& out) const
{
    neon::Serializer::WriteBytes(out, sScriptSig);
    neon::Serializer::WriteUint64(out, sSequence);
}

void STxInput::Deserialize(std::vector<uint8_t>& in, size_t& offset)
{
    sScriptSig = neon::Serializer::ReadBytes(in, offset);
    sSequence = neon::Serializer::ReadUint64(in, offset);
}

void STxOutput::Serialize(std::vector<uint8_t>& out) const
{
    neon::Serializer::WriteUint64(out, sValue);
    neon::Serializer::WriteBytes(out, sScriptPubKey);
}

void STxOutput::Deserialize(std::vector<uint8_t>& in, size_t& offset)
{
    sScriptPubKey = neon::Serializer::ReadBytes(in, offset);
    sValue = neon::Serializer::ReadUint64(in, offset);
}

uint256 CTransaction::GetTxID() const
{
    neon::CKeccak256 hasher;

    std::vector<uint8_t> out;
    Serialize(out);

    return hasher.Hash256(std::string(out.begin(), out.end()));
}

size_t CTransaction::GetTotalSize()
{
    std::vector<uint8_t> out;
    Serialize(out);
    return out.size();
}

void CTransaction::Serialize(std::vector<uint8_t>& out) const
{
    neon::Serializer::WriteUint64(out, Version);
    for (const auto& txin : Vin)
    {
        txin.Serialize(out);
    }
    for (const auto& txout : Vout)
    {
        txout.Serialize(out);
    }
}

void CTransaction::Deserialize(std::vector<uint8_t>& in, size_t& offset)
{
    Version = neon::Serializer::ReadUint64(in, offset);
    for (auto& txin : Vin)
    {
        txin.Deserialize(in, offset);
    }
    for (auto& txout : Vout)
    {
        txout.Deserialize(in, offset);
    }
}