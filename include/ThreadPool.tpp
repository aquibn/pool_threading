#ifndef THREADPOOL_TPP
#define THREADPOOL_TPP

#include "ThreadPool.hpp"

#include <type_traits>

template<typename F, typename... Args>
auto ThreadPool::enqueue(F&& f, Args&&... args)
    -> std::future<typename std::invoke_result<F, Args...>::type>
{
    using return_type = typename std::invoke_result<F, Args...>::type;

    auto task = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...)
    );

    std::future<return_type> result = task->get_future();

    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        if (stop)
            throw std::runtime_error("enqueue on stopped ThreadPool");

        tasks.emplace([task]() {
            (*task)();
        });
    }

    condition.notify_one();
    return result;
}

#endif // THREADPOOL_TPP
