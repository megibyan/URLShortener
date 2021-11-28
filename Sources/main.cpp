/**
 * @author	Mikayel Egibyan <megibyan@gmail.com>
 **/

#include "Service.hpp"
#include "served/multiplexer.hpp"

int main() {
	served::multiplexer mux;
	Service service(mux);

	service.init();
	service.start();

	return EXIT_SUCCESS;
}
