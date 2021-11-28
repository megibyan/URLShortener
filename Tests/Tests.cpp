#define BOOST_TEST_MODULE BASIC_TESTS

#include "../Sources/Internal/Crypto/Base62/Base62.hpp"
#include "../Sources/Internal/Crypto/SHA256/SHA256.hpp"
#include "../Sources/Internal/Crypto/CRC32/CRC32.hpp"
#include "../Sources/Internal/URL/URL.hpp"

#include <unistd.h>

#include <chrono>
#include <ctime>
#include <random>
#include <string>

#include <boost/test/unit_test.hpp>
#include <string>

namespace Helpers {
	namespace {
		inline uint64_t generateRandomNumber() {
			std::random_device rd;
			std::mt19937::result_type seed =
				rd() ^
				((std::mt19937::result_type)std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count() +
				 (std::mt19937::result_type)std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch())
					 .count());

			std::mt19937 gen(seed);
			std::uniform_int_distribution<unsigned> distrib(1, 6);

			return static_cast<uint64_t>(distrib(gen));
		}

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

BOOST_AUTO_TEST_CASE(CRC32_ENCODER_RANDOM_TEST_SUCCESS) {
	CRC32 crc32;
	const auto randomStr = Helpers::generateRandomString();
	const auto res = crc32.encode(randomStr);
	BOOST_CHECK(res > 0);
}

BOOST_AUTO_TEST_CASE(Base62_DECODER_RANDOM_TEST_SUCCESS) {
	Base62 base62;
	const auto randomStr = Helpers::generateRandomString();
	const auto res = base62.decode(randomStr);
	BOOST_CHECK(res > 0);
}

BOOST_AUTO_TEST_CASE(Base62_ENCODER_RANDOM_TEST_SUCCESS) {
	Base62 base62;
	const auto randomNum = Helpers::generateRandomNumber();
	const auto res = base62.encode(randomNum);
	BOOST_CHECK(!res.empty());
}

BOOST_AUTO_TEST_CASE(Base62_BACKWARD_TEST_SUCCESS) {
	Base62 base62;
	bool conversionSuccess = true;

	for (int i = 0; i < 1e5; ++i) {
		const auto randomNum = Helpers::generateRandomNumber();
		const auto enc = base62.encode(randomNum);
		const auto dec = base62.decode(enc);
		conversionSuccess = dec == randomNum;
		if (!conversionSuccess) {
			break;
		}
	}

	BOOST_CHECK(conversionSuccess);
}

BOOST_AUTO_TEST_CASE(SHA256_ENCODER_RANDOM_TEST_SUCCESS) {
	SHA256 sha256;
	const auto randomStr = Helpers::generateRandomString();
	const auto res = sha256.encode(randomStr);
	BOOST_CHECK(!res.empty());
}

BOOST_AUTO_TEST_CASE(URL_ENCODER_RANDOM_TEST_SUCCESS) {
	URL url;
	const auto randomStr = Helpers::generateRandomString();
	const auto res = url.encode(randomStr);
	BOOST_CHECK(!res.empty());
}

BOOST_AUTO_TEST_CASE(URL_DECODER_RANDOM_TEST_SUCCESS) {
	URL url;
	const auto randomStr = Helpers::generateRandomString();
	
	BOOST_CHECK_THROW(url.decode(randomStr), boost::wrapexcept<std::range_error>);
}

BOOST_AUTO_TEST_CASE(URL_BACKWARD_TEST_SUCCESS) {
	URL url;
	bool conversionSuccess = true;

	for (int i = 0; i < 1e5; ++i) {
		const auto randomStr = Helpers::generateRandomString();
		const auto enc = url.encode(randomStr);
		const auto dec = url.encode(randomStr);
		conversionSuccess = enc == dec;
		if (!conversionSuccess) {
			break;
		}
	}

	BOOST_CHECK(conversionSuccess);
}
