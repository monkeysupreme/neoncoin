#include "wallet/wallet.h"
#include "wallet/walletdb.h"

#include <iomanip>
#include <iostream>
int main()
{
    const auto wallet = CWallet();

    auto walletdb = neon::CWalletDB("wallets.db");
    walletdb.Dump(wallet);

    auto loaded = walletdb.Load(wallet.GetPublicKeyBytes());

    std::cout << loaded.GetPrivateKeyString() << '\n';
}
