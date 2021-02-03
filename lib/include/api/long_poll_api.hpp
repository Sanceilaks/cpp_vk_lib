#ifndef VK_LONG_POLL_API_H
#define VK_LONG_POLL_API_H

#include "lib/include/api/base_object.hpp"
#include "lib/include/events/common_event.hpp"
#include "lib/include/processing/thread_pool.hpp"


namespace vk
{
struct VK_EXPORT long_poll_data
{
    std::string key;
    std::string server;
    std::string ts;
};

class VK_EXPORT long_poll_api : private base_object
{
public:
    using events_t = std::vector<std::unique_ptr<event::common>>;

    long_poll_api();
    long_poll_data server();
    events_t listen(const long_poll_data& data, std::size_t timeout = 60) const;

    template <typename Function>
    void queue(Function&& function);
    void run(const std::size_t num_threads = std::thread::hardware_concurrency());

private:
    std::string _group_id;
    processing::thread_pool thread_pool;
};
} // namespace vk

template <typename Function>
void vk::long_poll_api::queue(Function&& function)
{
    thread_pool.queue(std::move(function));
}

#endif // VK_LONG_POLL_API_H