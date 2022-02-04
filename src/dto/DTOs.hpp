#pragma once

#include <oatpp/core/data/mapping/ObjectMapper.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

class MessageDto : public oatpp::DTO {
	DTO_INIT(MessageDto, DTO);
	
	DTO_FIELD(Int32, statusCode);
	DTO_FIELD(String, message);
};

#include OATPP_CODEGEN_END(DTO)