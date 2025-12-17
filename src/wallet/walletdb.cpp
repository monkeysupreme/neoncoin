#include "walletdb.h"

namespace neon
{

void CWalletDB::Dump(const CWallet& wallet) const
{
    if (mDB == nullptr)
        throw std::runtime_error("CWalletDB::Dump mDB is nullptr");

    mDB->Write(wallet.GetPublicKeyBytes(), wallet.ToBytes());
}

CWallet CWalletDB::Load(const std::vector<uint8_t>& public_key)
{
    if (mDB == nullptr)
        throw std::runtime_error("CWalletDB::Load mDB is nullptr");

    std::vector<uint8_t> wallet_bytes;
    if (!mDB->Read(public_key, wallet_bytes))
        throw std::runtime_error("CWalletDB::Load wallet not found");

    CWallet wallet;
    size_t offset = 0;
    wallet.Deserialize(wallet_bytes, offset);

    return wallet;
}


} // namespace neon