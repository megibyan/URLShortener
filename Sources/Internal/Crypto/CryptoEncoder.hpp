/**
 * @author	Mikayel Egibyan <megibyan@gmail.com>
 * @file	CryptoEncoder.hpp
 * @brief	Base class for encoders.
 **/

#ifndef CRYPTO_HPP
#define CRYPTO_HPP

template<typename inputType, typename outputType> class CryptoEncoder {
public:
	/* Default constructor */
	explicit CryptoEncoder() = default;

	/* Must override encoder */
	virtual outputType encode(inputType) = 0;
};

#endif /* CRYPTO_HPP */
