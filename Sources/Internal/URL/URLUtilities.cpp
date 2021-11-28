#include "URLUtilities.hpp"

#include <boost/algorithm/string.hpp>
#include <sstream>

namespace URLUtilities {
	std::string stringToJSON(JSONStruct const& json) {
		boost::property_tree::ptree stringOut;
		stringOut.put("URL.ID", json.id);
		stringOut.put("URL.LongURL", json.urlLong);
		stringOut.put("URL.ShortURL", "https://url.short/" + json.urlShort);

		std::ostringstream streamOut;
		boost::property_tree::write_json(streamOut, stringOut, false);

		std::string res = streamOut.str();
		boost::erase_all(res, "\\");

		return res;
	}

	void stringSplit(const std::string& s, char delim, std::vector<std::string>& elems) {
		std::stringstream ss(s);
		std::string item {};
		while (getline(ss, item, delim)) {
			elems.push_back(std::move(item));
		}
	}

	std::vector<std::string> stringSplit(const std::string& s, char delim) {
		std::vector<std::string> elems {};
		stringSplit(s, delim, elems);

		return elems;
	}
} /* namespace URLUtilities */
