#include "ThreadPool.hpp"

ThreadPool::ThreadPool(size_t thread_count) : stop(false) {
    for (size_t i = 0; i < thread_count; ++i) {
        workers.emplace_back([this]() {
            this->workerLoop();
        });
    }
}

ThreadPool::~ThreadPool() {
    stop = true;
    condition.notify_all();

    for (std::thread &worker : workers) {
        if (worker.joinable())
            worker.join();
    }
}

void ThreadPool::workerLoop() {
    while (!stop) {
        std::function<void()> task;

        {
            std::unique_lock<std::mutex> lock(queue_mutex);

            condition.wait(lock, [this]() {
                return stop || !tasks.empty();
            });

            if (stop && tasks.empty())
                return;

            task = std::move(tasks.front());
            tasks.pop();
        }

        task(); // Execute the task
    }
}
