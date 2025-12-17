#include "crypto.h"

#include <cryptopp/asn.h>
#include <cryptopp/oids.h>

namespace neon
{

using ECDSA256 = CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::Keccak_256>;

CKeccak256::CKeccak256()
{
}

std::vector<unsigned char> CKeccak256::Hash(const unsigned char* data, size_t len)
{
    std::vector<unsigned char> digest(HASHSIZE);

    mKeccak.Restart();
    mKeccak.Update(data, len);
    mKeccak.Final(digest.data());

    return digest;
}


std::vector<unsigned char> CKeccak256::Hash(const std::string& data)
{
    return Hash(reinterpret_cast<const unsigned char*>(data.data()), data.size());
}

std::string CKeccak256::HashHex(const std::string& data)
{
    const auto digest = Hash(data);

    static const char* hex_chars = "0123456789abcdef";
    std::string hex;
    hex.reserve(digest.size() * 2);

    for (unsigned char byte : digest)
    {
        hex.push_back(hex_chars[(byte >> 4) & 0x0F]);
        hex.push_back(hex_chars[byte & 0x0F]);
    }

    return hex;
}

uint256 CKeccak256::Hash256(const std::string& data)
{
    auto bytes = Hash(data);

    std::array<uint8_t, uint256::SIZE> arr;
    std::copy(bytes.begin(), bytes.end(), arr.begin());

    return uint256(arr.data());
}

CPrivateKey::CPrivateKey()
{
    CryptoPP::AutoSeededRandomPool rng;
    mPrivateKey.Initialize(rng, CryptoPP::ASN1::secp256k1());
}

CPrivateKey::CPrivateKey(const std::vector<uint8_t>& raw)
{
    LoadFromBytes(raw);
}

void CPrivateKey::LoadFromBytes(const std::vector<uint8_t>& raw)
{
    CryptoPP::Integer x(raw.data(), raw.size());
    mPrivateKey.Initialize(CryptoPP::ASN1::secp256k1(), x);
}

std::vector<uint8_t> CPrivateKey::GetPrivateKey() const
{
    CryptoPP::Integer x = mPrivateKey.GetPrivateExponent();
    std::vector<uint8_t> out(x.MinEncodedSize());
    x.Encode(out.data(), out.size());
    return out;
}

std::vector<uint8_t> CPrivateKey::GetPublicKey(bool compressed) const
{
    ECDSA256::PublicKey pubKey;
    mPrivateKey.MakePublicKey(pubKey);

    CryptoPP::ECP::Point q = pubKey.GetPublicElement();

    size_t size = compressed ? 33 : 65;
    std::vector<uint8_t> out(size);

    pubKey.GetGroupParameters().GetCurve().EncodePoint(
        out.data(),
        q,
        compressed
    );

    return out;
}

std::vector<uint8_t> CPrivateKey::Sign(const std::vector<uint8_t>& msg) const
{
    CryptoPP::AutoSeededRandomPool rng;
    ECDSA256::Signer signer(mPrivateKey);

    size_t sigLen = signer.MaxSignatureLength();
    std::vector<uint8_t> signature(sigLen);

    sigLen = signer.SignMessage(
        rng,
        msg.data(),
        msg.size(),
        signature.data()
    );

    signature.resize(sigLen);
    return signature;
}

} // namespace neon
