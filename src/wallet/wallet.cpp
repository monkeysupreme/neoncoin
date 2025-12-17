//
// Created by caleb on 12/14/25.
//

#include "wallet.h"

#include <iomanip>
#include <sstream>

std::string CWallet::GetPublicKeyString() const
{
    std::stringstream ss;
    for (const uint8_t b : mPublicKey)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(b);
    }
    return ss.str();
}

std::string CWallet::GetPrivateKeyString() const
{
    std::stringstream ss;
    for (const uint8_t byte : mPrivateKey.GetPrivateKey())
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }
    return ss.str();
}

std::vector<uint8_t> CWallet::GetPublicKeyBytes() const
{
    return mPublicKey;
}

std::vector<uint8_t> CWallet::GetPrivateKeyBytes() const
{
    return mPrivateKey.GetPrivateKey();
}

void CWallet::Serialize(std::vector<uint8_t>& out) const
{
    neon::Serializer::WriteBytes(out, mPublicKey);
    neon::Serializer::WriteBytes(out, mPrivateKey.GetPrivateKey());
    neon::Serializer::WriteUint256(out, Address);
}

void CWallet::Deserialize(std::vector<uint8_t>& in, size_t& offset)
{
    mPublicKey = neon::Serializer::ReadBytes(in, offset);
    Address = neon::Serializer::ReadUint256(in, offset);
}