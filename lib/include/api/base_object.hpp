#ifndef VK_BASE_OBJECT_H
#define VK_BASE_OBJECT_H

#include <map>
#include <string>
#include <memory>

#include "simdjson.h"
#include "simdjson/portability.h"

#include "net/network_client.hpp"


namespace vk
{
class VK_EXPORT base_object
{
protected:
    explicit base_object() noexcept;
    virtual ~base_object() = default;

    std::map<std::string, std::string> user_params(std::map<std::string, std::string>&& params) const;
    std::map<std::string, std::string> group_params(std::map<std::string, std::string>&& params) const;
    simdjson::dom::object call_and_parse(std::string_view method, std::map<std::string, std::string>&& params);
    std::string call        (std::string_view method, const std::map<std::string, std::string>& params) const;
    std::string append_url  (std::string_view method) const;
    bool error_returned     (const simdjson::dom::object& response, std::int64_t error_code);

    static inline std::int64_t chat_id_constant = 2000000000;
    static inline constexpr const char api_v[] = "5.124";
    static inline std::string access_token;
    static inline std::string user_token;

    network_client net_client;
    simdjson::dom::parser parser;
};
} // namespace vk

#endif // VK_BASE_OBJECT_H
