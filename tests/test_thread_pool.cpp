#include <iostream>
#include <cassert>
#include <chrono>
#include <thread>
#include "../include/ThreadPool.hpp"

int add(int a, int b) {
    return a + b;
}

void test_basic_task_execution() {
    ThreadPool pool(2);

    // Enqueue a task and get the result
    auto future = pool.enqueue(add, 3, 4);
    int result = future.get();

    std::cout << "Test add(3, 4) == 7 -> ";
    assert(result == 7);
    std::cout << "PASSED\n";
}

void test_multiple_tasks() {
    ThreadPool pool(4);

    std::vector<std::future<int>> futures;
    for (int i = 0; i < 10; ++i) {
        futures.push_back(pool.enqueue([i]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            return i * i;
        }));
    }

    std::cout << "Test 10 tasks with squares -> ";
    for (int i = 0; i < 10; ++i) {
        assert(futures[i].get() == i * i);
    }
    std::cout << "PASSED\n";
}

int main() {
    std::cout << "Running ThreadPool Tests...\n";
    test_basic_task_execution();
    test_multiple_tasks();
    std::cout << "All tests PASSED ✅\n";
    return 0;
}
