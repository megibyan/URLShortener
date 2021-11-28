#include "URL.hpp"

#include <boost/algorithm/string.hpp>
#include <vector>

#include "CryptoUtilities.hpp"

std::string URL::encode(const std::string& urlLong) {
	URLUtilities::JSONStruct urlJSON {};

	try {
		const auto urlShort = CryptoUtilities::urlLongToShort(urlLong);
		const auto urlID = CryptoUtilities::urlToID(urlShort);

		const auto it = urls.find(urlID);
		if (it == urls.end()) {
			urlJSON = {urlID, urlShort, urlLong};
			urls.insert(std::make_pair(urlID, urlJSON));
		} else {
			urlJSON = urls[urlID];
		}
	} catch (...) {
		BOOST_THROW_EXCEPTION(std::runtime_error("Encryption failed."));
	}

	return URLUtilities::stringToJSON(urlJSON);
}

std::string URL::decode(const std::string& urlShortIn) {
	try {
		auto urlShort = urlShortIn;
		boost::erase_all(urlShort, "\"");
		const auto splitURL = URLUtilities::stringSplit(urlShort, '/');
		if (!splitURL.empty()) {
			const auto urlSplit = splitURL.back();
			const auto urlID = CryptoUtilities::urlToID(urlSplit);

			const auto it = urls.find(urlID);
			if (it != urls.end()) {
				URLUtilities::JSONStruct urlJSON = urls[urlID];
				return URLUtilities::stringToJSON(urlJSON);
			}
		}
	} catch (...) {
		BOOST_THROW_EXCEPTION(std::runtime_error("Something unhandled failed."));
	}

	BOOST_THROW_EXCEPTION(std::range_error("Long URL for the specified short version doesn't exist."));
}
