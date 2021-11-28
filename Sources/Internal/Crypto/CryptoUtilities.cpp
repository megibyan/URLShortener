#include "CryptoUtilities.hpp"

namespace CryptoUtilities {
	std::string urlLongToShort(const std::string& urlLong) {
		SHA256 sha256;
		const auto sha256Result = sha256.encode(urlLong);

		CRC32 crc32;
		const auto crc32Result = crc32.encode(sha256Result);

		/*
			Base62 is a bijective algorithm, so we can use it to encrypt something we can decrypt
		*/
		Base62 base62;

		return base62.encode(crc32Result);
	}

	uint64_t urlToID(const std::string& urlShort) {
		CRC32 crc32;

		return crc32.encode(urlShort);
	}
} /* namespace CryptoUtilities */
