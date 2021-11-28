/**
 * @author	Mikayel Egibyan <megibyan@gmail.com>
 * @file	CryptoDecoder.hpp
 * @brief	Base class for decoders.
 **/

#ifndef CRYPTODECODER_HPP
#define CRYPTODECODER_HPP

template<typename inputType, typename outputType> class CryptoDecoder {
public:
	/* Default constructor */
	explicit CryptoDecoder() = default;

	/* Must override encoder */
	virtual outputType decode(inputType) = 0;
};

#endif /* CRYPTODECODER_HPP */
