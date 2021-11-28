#include "Service.hpp"

void Service::start() {
	served::net::server server(ip, port, mux);
	server.run(threadCount);
};

void Service::init() {
	mux.handle(encodeEP).post(encode());
	mux.handle(decodeEP).post(decode());
};
