cmake_minimum_required(VERSION 3.16.3)
project(oat_test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(oatpp)
if (oatpp_FOUND)
	message(STATUS "Found oatpp in ${OATPP_BASE_DIR}")
endif(oatpp_FOUND)

add_executable(${PROJECT_NAME} src/App.cpp)
target_link_libraries(${PROJECT_NAME} oatpp::oatpp)

add_executable(${PROJECT_NAME}Tests test/Tests.cpp test/MyControllerTest.cpp)
target_link_libraries(${PROJECT_NAME}Tests oatpp::oatpp oatpp::oatpp-test)
