#include "FileName.h"
// function to run the code

int main() {
	Net net;
	try {
		net.run();
	}
	catch (const std::exception& e) {
		std::cerr << "An error occurred: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return 0;
}