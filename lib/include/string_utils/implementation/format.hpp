#ifndef STRING_UTIL_FORMAT_IMPL_H
#define STRING_UTIL_FORMAT_IMPL_H

#include <deque>
#include <array>
#include <sstream>
#include <any>

#include "misc/cppdefs.hpp"


namespace vk {
namespace string_utils {
template <typename... Args>
std::string format(std::string_view data, Args&&... args);
} // namespace string_util
} // namespace vk

namespace vk {
namespace string_utils {

template <typename... Args> struct vk_hidden format_implementation {
private:
  static std::string create(std::string_view data, Args&&... args) {
    if (data.empty())
      return {};
    std::string formatted;
    std::ostringstream output_stream;
    auto pack_one = [&output_stream](auto&& argument) {
      output_stream.str("");
      output_stream.clear();
      output_stream << std::forward<decltype(argument)>(argument);
      return output_stream.rdbuf()->str();
    };
    std::array<std::string, sizeof...(Args)> elements{pack_one(args)...};
    std::size_t curr = 0;
    for (std::size_t i = 0; i < data.size(); i++) {
      // If we're have '{}' token, insert parameter at this place.
      if (data[i] == '{' && data[i + 1] == '}') {
        formatted += elements[curr++];
      // Add all characters from source string except '{}' token.
      } else if (data[i - 1] != '{' || data[i] != '}') {
        formatted += data[i];
      }
    }
    return formatted;
  }

  template <typename... _Args>
  friend std::string vk::string_utils::format(std::string_view data, _Args&&... args);
};
} // namespace string_util
} // namespace vk

#endif // STRING_UTIL_FORMAT_IMPL_H
