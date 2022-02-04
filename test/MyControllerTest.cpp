#include "MyControllerTest.hpp"
#include "app/TestComponent.hpp"
#include <chrono>
#include <memory>
#include <oatpp-test/web/ClientServerTestRunner.hpp>
#include <oatpp/core/Types.hpp>
#include <oatpp/core/base/Environment.hpp>
#include <oatpp/core/data/mapping/ObjectMapper.hpp>
#include <oatpp/core/macro/component.hpp>
#include <oatpp/network/ConnectionProvider.hpp>
#include "../src/controller/MyController.hpp"
#include <oatpp/web/client/HttpRequestExecutor.hpp>
#include <thread>
#include "app/MyApiTestClient.hpp"

void MyControllerTest::onRun() {
	TestComponent component;
	oatpp::test::web::ClientServerTestRunner runner;
	runner.addController(std::make_shared<MyController>());

	runner.run([this, &runner] {
		OATPP_COMPONENT(std::shared_ptr<oatpp::network::ClientConnectionProvider>, clientConnectionProvider);
		OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper);
		
		auto requestExecutor = oatpp::web::client::HttpRequestExecutor::createShared(clientConnectionProvider);

		auto client = MyApiTestClient::createShared(requestExecutor, objectMapper);

		auto response = client->getHello();
		OATPP_ASSERT(response->getStatusCode() == 200);
		auto message = response->readBodyToDto<oatpp::Object<MessageDto>>(objectMapper.get());
		OATPP_ASSERT(message);
		OATPP_ASSERT(message->statusCode.getValue(-1) == 200);
		OATPP_ASSERT(message->message == "Hello World!");
	}, std::chrono::minutes(10));

	std::this_thread::sleep_for(std::chrono::seconds(1));
}