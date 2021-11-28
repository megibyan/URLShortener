/**
 * @author	Mikayel Egibyan <megibyan@gmail.com>
 * @file	SHA256.hpp
 * @brief	Encoder for SHA256.
 * @sa		https://en.wikipedia.org/wiki/SHA-2
 **/

#ifndef SHA256_HPP
#define SHA256_HPP

#include <string>

#include "CryptoEncoder.hpp"

class SHA256 : CryptoEncoder<std::string, std::string> {
public:
	/* Default constructor */
	explicit SHA256() = default;

	/**
	 * @brief		Encodes a string to SHA256.
	 *
	 * @param[in]	value - string value
	 *
	 * @return		SHA256 encoding of value
	 **/
	std::string encode(std::string value) override;
};

#endif /* SHA256_HPP */
