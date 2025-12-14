#include "transaction.h"
#include "crypto.h"

std::vector<uint8_t> STxInput::Serialize() const
{
    std::vector<uint8_t> out;

    neon::Serializer::WriteUint256(out, sPrevOut.sTxID);
    neon::Serializer::WriteUint64(out, sPrevOut.sIndex);

    neon::Serializer::WriteUint64(out, sScriptSig.size());
    out.insert(out.end(), sScriptSig.begin(), sScriptSig.end());

    neon::Serializer::WriteUint64(out, sSequence);

    return out;
}

std::vector<uint8_t> STxOutput::Serialize() const
{
    std::vector<uint8_t> out;

    neon::Serializer::WriteUint64(out, sValue);
    neon::Serializer::WriteUint64(out, sScriptPubKey.size());
    out.insert(out.end(), sScriptPubKey.begin(), sScriptPubKey.end());

    return out;
}

std::vector<uint8_t> CTransaction::Serialize() const
{
    std::vector<uint8_t> out;

    neon::Serializer::WriteUint64(out, Version);
    neon::Serializer::WriteUint64(out, Vin.size());

    for (const auto& in : Vin)
    {
        auto bytes = in.Serialize();
        out.insert(out.end(), bytes.begin(), bytes.end());
    }

    neon::Serializer::WriteUint64(out, Vout.size());
    for (const auto& outp : Vout)
    {
        auto bytes = outp.Serialize();
        out.insert(out.end(), bytes.begin(), bytes.end());
    }

    return out;
}

uint256 CTransaction::GetTxID() const
{
    neon::CKeccak256 hasher;
    auto bytes = Serialize();

    return hasher.Hash256(std::string(bytes.begin(), bytes.end()));
}

size_t CTransaction::GetTotalSize()
{
    return Serialize().size();
}
