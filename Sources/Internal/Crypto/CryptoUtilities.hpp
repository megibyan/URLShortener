/**
 * @author	Mikayel Egibyan <megibyan@gmail.com>
 * @file	CryptoUtilities.hpp
 * @brief	Utilities to perform URL encoding and decoding.
 **/

#ifndef CRYPTO_UTILITIES_HPP
#define CRYPTO_UTILITIES_HPP

#include <string>

#include "Base62/Base62.hpp"
#include "CRC32/CRC32.hpp"
#include "CryptoDecoder.hpp"
#include "CryptoEncoder.hpp"
#include "SHA256/SHA256.hpp"

namespace CryptoUtilities {
	/**
	 * @brief		Encodes a unique short version of a URL.
	 *				The logic pipeline looks like following:
	 *				URL -> SHA256 -> CRC32 -> Base62 -> CRC32
	 *
	 * @param[in]	urlLong - original URL
	 *
	 * @return		short URL
	 **/
	std::string urlLongToShort(const std::string& urlLong);

	/**
	 * @brief		Creates a unique ID for an encripted short URL.
	 *				The logic pipeline looks like following:
	 *				URL -> CRC32
	 *
	 * @param[in]	urlShort - short URL
	 *
	 * @return		id
	 **/
	uint64_t urlToID(const std::string& urlShort);
}

#endif /* CRYPTO_UTILITIES_HPP */
