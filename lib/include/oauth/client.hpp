#ifndef VK_OAUTH_H
#define VK_OAUTH_H

#include "simdjson.h"

#include "net/network_client.hpp"
#include "processing/exception.hpp"


namespace vk
{
namespace oauth
{
enum class device : std::uint8_t
{
    android = (1 << 0),
    iphone  = (1 << 1),
    windows = (1 << 2)
};

class VK_EXPORT client
{
public:
    explicit client(std::string_view username_, std::string_view password_, device client_type_);
    std::pair<std::string_view, std::int64_t> pull();

private:
    bool error_returned(const simdjson::dom::object& response, std::string_view error_desc)
    {
        return response.begin().key() == "error" && response["error"].get_string().take_value() == error_desc;
    }

    static inline const std::string_view oauth_link = "https://oauth.vk.com/";
    static inline const std::string_view android_app_client_secret = "hHbZxrka2uZ6jB1inYsH";
    static inline const std::string_view iphone_app_client_secret  = "VeWdmVclDCtn6ihuP1nt";
    static inline const std::string_view windows_app_client_secret = "AlVXZFMUqyrnABp8ncuU";

    static inline const std::int32_t android_app_client_id = 2274003;
    static inline const std::int32_t windows_app_client_id = 3697615;
    static inline const std::int32_t iphone_app_client_id  = 3140623;

    std::string target_client_secret;
    std::int64_t target_client_id;

    device client_type;

    const std::string username;
    const std::string password;
    simdjson::dom::parser parser;
    network_client net_client;
};
} // namespace oauth
} // namespace vk

#endif // VK_OAUTH_H