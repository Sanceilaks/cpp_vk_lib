#include "methods/video.hpp"


vk::attachment::attachments_t vk::method::video::search(std::string_view query, std::int64_t count) {
  return common_search("video.search", query, count);
}

void vk::method::video::save_by_link(std::string_view url) {
  std::string response = method_util.call("video.save", method_util.user_args({{"link", url.data()}}));
}
