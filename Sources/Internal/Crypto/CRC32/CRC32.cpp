#include "CRC32.hpp"

#include <zconf.h>
#include <zlib.h>

uint64_t CRC32::encode(std::string value) {
	uint64_t encoding {};
	size_t byteArrayLength = value.length();

	std::unique_ptr<unsigned char[]> byteArray(new unsigned char[byteArrayLength]);
	memcpy(byteArray.get(), value.data(), value.length());

	encoding = crc32(0L, Z_NULL, 0);

	for (size_t i = 0; i < byteArrayLength; ++i) {
		encoding = crc32(static_cast<uint64_t>(encoding), byteArray.get() + i, static_cast<uInt>(1));
	}

	return encoding;
}
