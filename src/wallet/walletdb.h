#ifndef NEONCOIN_WALLETDB_H
#define NEONCOIN_WALLETDB_H

#include "db.h"
#include "wallet.h"
#include <string>

namespace neon
{

class CWalletDB
{
public:
    explicit CWalletDB(const std::string& path) : mDB(new CDatabase(path))
    {
    }

    void Dump(const CWallet& wallet) const;
    CWallet Load(const std::vector<uint8_t>& public_key);

private:
    CDatabase* mDB;
};

} // namespace neon

#endif // NEONCOIN_WALLETDB_H