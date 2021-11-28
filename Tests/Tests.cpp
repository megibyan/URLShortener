#define BOOST_TEST_MODULE BASIC_TESTS

#include "../Sources/Internal/Crypto/SHA256/SHA256.hpp"

#include <unistd.h>

#include <random>
#include <string>

#include <boost/test/unit_test.hpp>
#include <string>

namespace Helpers {
	namespace {
		inline std::string generateRandomString() {
			static const char base62CharSet[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
			std::string randomString;
			randomString.reserve(20);

			for (int i = 0; i < 20; ++i) {
				randomString += base62CharSet[rand() % (sizeof(base62CharSet) - 1)];
			}

			return randomString;
		}
	} /* namespace */
} /* namespace Helpers */

BOOST_AUTO_TEST_CASE(SHA256_ENCODER_RANDOM_TEST_SUCCESS) {
	SHA256 sha256;
	const auto randomStr = Helpers::generateRandomString();
	const auto res = sha256.encode(randomStr);
	BOOST_CHECK(!res.empty());
}
