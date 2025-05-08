#include <iostream>
#include <chrono>
#include "ThreadPool.hpp"

void exampleTask(int id) {
    std::cout << "Task " << id << " is starting on thread " 
              << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Task " << id << " is finished." << std::endl;
}

int main() {
    ThreadPool pool(4); // Create a thread pool with 4 worker threads

    // Enqueue several tasks
    for (int i = 1; i <= 8; ++i) {
        pool.enqueue(exampleTask, i);
    }

    // Sleep to allow all tasks to finish
    std::this_thread::sleep_for(std::chrono::seconds(5));

    std::cout << "Main thread done." << std::endl;
    return 0;
}
