#ifndef VK_GROUPS_H
#define VK_GROUPS_H

#include "method_utils/method_utils.hpp"


namespace vk {
namespace method {
/*!
 * @brief The groups methods representation.
 *
 * Please, inherit this class to add new methods.
 */
class vk_export groups {
public:
  std::int64_t get_by_id();
  simdjson::dom::object get_long_poll_server(std::string_view group_id);
private:
  method_utils method_util;
};
} // namespace method
} // namespace vk

#endif // VK_GROUPS_H
