#include "MyControllerTest.hpp"
#include <iostream>
#include <oatpp-test/UnitTest.hpp>
#include <oatpp/core/base/Environment.hpp>

void runTests() {
	OATPP_RUN_TEST(MyControllerTest);
}

int main() {
	oatpp::base::Environment::init();
	runTests();

	std::cout << std::endl << "Environment:" << std::endl;
	std::cout << "objectsCount = " << oatpp::base::Environment::getObjectsCount() << std::endl;
	std::cout << "objectsCreated = " << oatpp::base::Environment::getObjectsCreated() << std::endl << std::endl;

	OATPP_ASSERT(oatpp::base::Environment::getObjectsCount() == 0);
	oatpp::base::Environment::destroy();

	return 0;
}