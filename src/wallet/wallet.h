//
// Created by caleb on 12/14/25.
//

#ifndef NEONCOIN_WALLET_H
#define NEONCOIN_WALLET_H

#include "../crypto/crypto.h"
#include "../serializer.h"
#include "../crypto/crypto.h"

class CWallet : public neon::Serializable
{
public:
    uint256 Address;

    CWallet()
    {
        neon::CKeccak256 keccak;
        Address = keccak.Hash256(GetPublicKeyString());
        mPrivateKey = neon::CPrivateKey();
        mPublicKey = mPrivateKey.GetPublicKey(true);
    }

    std::string GetPublicKeyString() const;
    std::string GetPrivateKeyString() const;

    std::vector<uint8_t> GetPublicKeyBytes() const;
    std::vector<uint8_t> GetPrivateKeyBytes() const;

    void Serialize(std::vector<uint8_t>& out) const override;
    void Deserialize(std::vector<uint8_t>& in, size_t& offset) override;

private:
    neon::CPrivateKey mPrivateKey;
    std::vector<unsigned char> mPublicKey;
};

#endif //NEONCOIN_WALLET_H
