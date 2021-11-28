/**
 * @author	Mikayel Egibyan <megibyan@gmail.com>
 * @file	CRC32.hpp
 * @brief	Encoder for CRC32.
 * @sa		https://en.wikipedia.org/wiki/Cyclic_redundancy_check
 **/

#ifndef CRC32_HPP
#define CRC32_HPP

#include <string>

#include "CryptoEncoder.hpp"

class CRC32 : CryptoEncoder<std::string, uint64_t> {
public:
	/* Default constructor */
	explicit CRC32() = default;

	/**
	 * @brief		Computes cyclic redundancy checksum of a string.
	 *
	 * @param[in]	value - string value
	 *
	 * @return		CRC32 encoding of value
	 **/
	uint64_t encode(std::string value) override;
};

#endif /* CRC32_HPP */
