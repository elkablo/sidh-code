#include <cstring>
#include <openssl/sha.h>

#include <pqc_mac_hmac_sha.hpp>

namespace pqc
{

hmac_sha256::operator enum pqc_mac() const
{
	return PQC_MAC_HMAC_SHA256;
}

size_t hmac_sha256::size() const
{
	return 32;
}

void hmac_sha256::key(const void *keyv, size_t len)
{
	uint64_t key[8];
	if (len > 64) {
		SHA256_CTX ctx;

		SHA256_Init(&ctx);
		SHA256_Update(&ctx, keyv, len);
		SHA256_Final(reinterpret_cast<unsigned char *>(key), &ctx);

		len = 32;
	} else {
		::memcpy(key, keyv, len);
	}

	if (len < 64) {
		::memset(&reinterpret_cast<uint8_t *>(key)[len], 0, 64-len);
	}

	for (int i = 0; i < 8; ++i) {
		o_pad_[i] = key[i] ^ 0x5c5c5c5c5c5c5c5cULL;
		i_pad_[i] = key[i] ^ 0x3636363636363636ULL;
	}
}

void hmac_sha256::compute(void *digest, const void *input, size_t len)
{
	SHA256_CTX ctx;

	SHA256_Init(&ctx);
	SHA256_Update(&ctx, reinterpret_cast<const void *>(i_pad_), 64);
	SHA256_Update(&ctx, input, len);
	SHA256_Final(reinterpret_cast<unsigned char *>(digest), &ctx);

	SHA256_Init(&ctx);
	SHA256_Update(&ctx, reinterpret_cast<const void *>(o_pad_), 64);
	SHA256_Update(&ctx, digest, 32);
	SHA256_Final(reinterpret_cast<unsigned char *>(digest), &ctx);
}

hmac_sha512::operator enum pqc_mac() const
{
	return PQC_MAC_HMAC_SHA512;
}

size_t hmac_sha512::size() const
{
	return 64;
}

void hmac_sha512::key(const void *keyv, size_t len)
{
	uint64_t key[16];
	if (len > 128) {
		SHA512_CTX ctx;

		SHA512_Init(&ctx);
		SHA512_Update(&ctx, keyv, len);
		SHA512_Final(reinterpret_cast<unsigned char *>(key), &ctx);

		len = 64;
	} else {
		::memcpy(key, keyv, len);
	}

	if (len < 128) {
		::memset(&reinterpret_cast<uint8_t *>(key)[len], 0, 128-len);
	}

	for (int i = 0; i < 16; ++i) {
		o_pad_[i] = key[i] ^ 0x5c5c5c5c5c5c5c5cULL;
		i_pad_[i] = key[i] ^ 0x3636363636363636ULL;
	}
}

void hmac_sha512::compute(void *digest, const void *input, size_t len)
{
	SHA512_CTX ctx;

	SHA512_Init(&ctx);
	SHA512_Update(&ctx, reinterpret_cast<const void *>(i_pad_), 128);
	SHA512_Update(&ctx, input, len);
	SHA512_Final(reinterpret_cast<unsigned char *>(digest), &ctx);

	SHA512_Init(&ctx);
	SHA512_Update(&ctx, reinterpret_cast<const void *>(o_pad_), 128);
	SHA512_Update(&ctx, digest, 64);
	SHA512_Final(reinterpret_cast<unsigned char *>(digest), &ctx);
}

}
