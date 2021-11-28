/**
 * @author	Mikayel Egibyan <megibyan@gmail.com>
 * @file	Service.hpp
 * @brief	Endpoint provider.
 **/

#ifndef SERVICE_HPP
#define SERVICE_HPP

#include <string>

#include "URL.hpp"
#include "served/multiplexer.hpp"
#include "served/net/server.hpp"

class Service {
public:
	/* Default constructor */
	Service() = delete;
	explicit Service(served::multiplexer mux) : mux(mux) {};

	/**
	 * @brief		Converts long URL to short URL.
	 *
	 * @return		short URL
	 *
	 * @throws		202 - failed to convert
	 **/
	auto encode() {
		return [&](served::response& response, const served::request& request) {
			try {
				const auto result = url.encode(request.body());
				response.set_body(result);
			} catch (...) {
				served::response::stock_reply(202, response);
			}
		};
	}

	/**
	 * @brief		Converts short URL to long URL.
	 *
	 * @return		long URL
	 *
	 * @throws		202 - failed to convert
	 * @throws		404 - no valid conversion found
	 **/
	auto decode() {
		return [&](served::response& response, const served::request& request) {
			try {
				const auto result = url.decode(request.body());
				response.set_body(result);
			} catch (const std::exception& ex) {
				served::response::stock_reply(404, response);
			} catch (...) {
				served::response::stock_reply(202, response);
			}
		};
	}

	/**
	 * @brief		Initialize the service.
	 **/
	void init();

	/**
	 * @brief		Start the service.
	 **/
	void start();

private:
	served::multiplexer mux;
	URL url;

	/* Endpoints */
	const std::string encodeEP = "/encode";
	const std::string decodeEP = "/decode";

	/* Configurations */
	const std::string ip = "localhost";
	const std::string port = "8080";
	const uint8_t threadCount = 10;
};

#endif /* SERVICE_HPP */
