#include "SHA256.hpp"

#include "base64.h"
#include "filters.h"
#include "sha.h"
#include "sha256_armv4.h"

std::string SHA256::encode(std::string value) {
	CryptoPP::SHA256 sha256Hash {};
	std::string encoding {};

	CryptoPP::StringSource encode(value, true, new CryptoPP::HashFilter(sha256Hash, new CryptoPP::Base64Encoder(new CryptoPP::StringSink(encoding))));

	return encoding;
}
