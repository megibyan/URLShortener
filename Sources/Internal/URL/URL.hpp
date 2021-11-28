/**
 * @author	Mikayel Egibyan <megibyan@gmail.com>
 * @file	URL.hpp
 * @brief	URL class.
 **/

#ifndef URL_HPP
#define URL_HPP

#include <string>
#include <unordered_map>

#include "URLUtilities.hpp"

class URL {
public:
	/* Default constructor */
	explicit URL() = default;

	/**
	 * @brief		Encodes a URL to the shorter unique version of itself.
	 *
	 * @param[in]	urlLong - original URL
	 *
	 * @return		{"URL": {"ID": id, "LongURL": urlLong, "ShortURL": urlShort}}
	 *
	 * @throws		std::runtime_error - encryption failed
	 **/
	std::string encode(const std::string& urlLong);

	/**
	 * @brief		Decodes a short URL to the original version of itself
	 *
	 * @param[in]	urlShort - short URL
	 *
	 * @return		{"URL": {"ID": id, "LongURL": urlLong, "ShortURL": urlShort}}
	 *
	 * @throws		std::runtime_error - something unhandled failed
	 * @throws		std::range_error - long URL for the specified short version doesn't exist
	 **/
	std::string decode(const std::string& urlShort);

private:
	/* In-memory storage */
	std::unordered_map<uint64_t, URLUtilities::JSONStruct> urls;
};

#endif /* URL_HPP */
