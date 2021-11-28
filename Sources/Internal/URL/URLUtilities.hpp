/**
 * @author	Mikayel Egibyan <megibyan@gmail.com>
 * @file	URLUtilities.hpp
 * @brief	Utilities to parse and process URLs.
 **/

#ifndef URL_UTILITIES_HPP
#define URL_UTILITIES_HPP

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <string>

namespace URLUtilities {
	/**
	 * @brief	Structure to hold the information about the URL before and after shortening.
	 **/
	struct JSONStruct {
		uint64_t id;
		std::string urlShort;
		std::string urlLong;
	};

	/**
	 * @brief		Create a string preserving the JSON structure.
	 *
	 * @param[in]	json - JSONStruct input
	 *
	 * @return		string version of json
	 **/
	std::string stringToJSON(JSONStruct const& json);

	/**
	 * @brief			Split a string using a specified delimiter.
	 *
	 * @param[in]		s - input string
	 * @param[in]		delim - split delimiter
	 * @param[in, out]	elems - vector of split results
	 **/
	void stringSplit(const std::string& s, char delim, std::vector<std::string>& elems);

	/**
	 * @brief			Split a string using a specified delimiter.
	 *
	 * @param[in]		s - input string
	 * @param[in]		delim - split delimiter (defaults to '/')
	 *
	 * @return			vector of split results
	 **/
	std::vector<std::string> stringSplit(const std::string& s, char delim = '/');
} /* namespace Utilities */

#endif /* URL_UTILITIES_HPP */
