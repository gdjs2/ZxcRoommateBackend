#pragma once

#include <memory>
#include <oatpp/core/data/mapping/ObjectMapper.hpp>
#include <oatpp/core/macro/component.hpp>
#include <oatpp/network/ConnectionHandler.hpp>
#include <oatpp/network/ConnectionProvider.hpp>
#include <oatpp/network/virtual_/Interface.hpp>
#include <oatpp/network/virtual_/server/ConnectionProvider.hpp>
#include <oatpp/network/virtual_/client/ConnectionProvider.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp/web/server/HttpConnectionHandler.hpp>
#include <oatpp/web/server/HttpRouter.hpp>

class TestComponent {
public:
	OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::virtual_::Interface>, virtualInterface)([] {
		return oatpp::network::virtual_::Interface::obtainShared("virtualhost");
	}());

	OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, serverConnectionProvider)([] {
		OATPP_COMPONENT(std::shared_ptr<oatpp::network::virtual_::Interface>, interface);
		return oatpp::network::virtual_::server::ConnectionProvider::createShared(interface);
	}());

	OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ClientConnectionProvider>, clientConnectionProvider)([] {
		OATPP_COMPONENT(std::shared_ptr<oatpp::network::virtual_::Interface>, interface);
		return oatpp::network::virtual_::client::ConnectionProvider::createShared(interface);
	}());

	OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter)([] {
		return oatpp::web::server::HttpRouter::createShared();
	}());

	OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, serverConnectionHander)([] {
		OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);
		return oatpp::web::server::HttpConnectionHandler::createShared(router);
	}());

	OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, apiObjectMapper)([] {
		return oatpp::parser::json::mapping::ObjectMapper::createShared();
	}());
};