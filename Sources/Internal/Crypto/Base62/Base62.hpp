/**
 * @author	Mikayel Egibyan <megibyan@gmail.com>
 * @file	Base62.hpp
 * @brief	Encoder and decoder for Base62.
 * @sa		https://en.wikipedia.org/wiki/Base62
 **/

#ifndef BASE62_HPP
#define BASE62_HPP

#include <string>

#include "CryptoDecoder.hpp"
#include "CryptoEncoder.hpp"

class Base62 : CryptoEncoder<uint64_t, std::string>, CryptoDecoder<std::string, uint64_t> {
public:
	/* Default constructor */
	explicit Base62() = default;

	/**
	 * @brief		Encodes a string to Base62.
	 *
	 * @param[in]	value - string value
	 *
	 * @return		base62 encoding of value
	 **/
	std::string encode(uint64_t decoding) override;

	/**
	 * @brief		Decode a string from Base62.
	 *
	 * @param[in]	encoding - base62 encoding
	 *
	 * @return		string decoding of encoding
	 **/
	uint64_t decode(std::string encoding) override;

private:
	/* Character set for 62 base encoding. */
	const std::string characterSet = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
};

#endif /* BASE62_HPP */
