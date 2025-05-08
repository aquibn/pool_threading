#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <atomic>
#include <type_traits>

class ThreadPool {
public:
    explicit ThreadPool(size_t thread_count);  // Constructor
    ~ThreadPool();                              // Destructor

    // Enqueue a new task into the thread pool
    template<typename F, typename... Args>
    auto enqueue(F&& f, Args&&... args)
        #if __cplusplus >= 201703L
                -> std::future<typename std::invoke_result<F, Args...>::type>;
        #else
                -> std::future<typename std::result_of<F(Args...)>::type>;
        #endif

private:
    // Worker threads
    std::vector<std::thread> workers;

    // Task queue
    std::queue<std::function<void()>> tasks;

    // Synchronization
    std::mutex queue_mutex;
    std::condition_variable condition;
    std::atomic<bool> stop;

    // Worker thread main function
    void workerLoop();
};

#include "ThreadPool.tpp"  // Template implementation

#endif // THREADPOOL_HPP
