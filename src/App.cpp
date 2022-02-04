#include "AppComponent.hpp"
#include <memory>
#include <oatpp/core/Types.hpp>
#include <oatpp/core/base/Environment.hpp>
#include <oatpp/core/macro/component.hpp>
#include <oatpp/network/Address.hpp>
#include <oatpp/network/ConnectionHandler.hpp>
#include <oatpp/network/ConnectionProvider.hpp>
#include <oatpp/network/Server.hpp>
#include <oatpp/network/tcp/server/ConnectionProvider.hpp>
#include <oatpp/web/server/HttpConnectionHandler.hpp>
#include <oatpp/web/server/HttpRouter.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include "dto/DTOs.hpp"
#include <oatpp/core/macro/component.hpp>
#include <oatpp/web/server/HttpRequestHandler.hpp>
#include <memory>
#include "./controller/MyController.hpp"

void run() {
	AppComponent component;

	OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);

	auto myController = std::make_shared<MyController>();
	router->addController(myController);
	
	OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler);
	OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider);

	oatpp::network::Server server(connectionProvider, connectionHandler);
	OATPP_LOGI("OAT_Test", "Server running on port %s", connectionProvider->getProperty("port").getData());
	server.run();
}

int main() {
  oatpp::base::Environment::init();
  run();
  oatpp::base::Environment::destroy();

  return 0;
}
