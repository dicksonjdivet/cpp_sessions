#include <cstdio>
#include <thread>
#include <mutex>
#include <vector>

// TODO: Implement a ThreadSafeCounter class
// - Has methods increment(), decrement(), and getValue()
// - Is safe to use from multiple threads
// - Use std::mutex and appropriate RAII lock guards (std::lock_guard or std::unique_lock)

class ThreadSafeCounter {
public:
    ThreadSafeCounter() : m_value(0) {}

    void increment() {
        // TODO: Implement thread-safe increment
    }

    void decrement() {
        // TODO: Implement thread-safe decrement
    }

    int getValue() const {
        // TODO: Implement thread-safe getValue
        return 0;
    }

private:
    int m_value;
    // TODO: Add a mutex member
};

int main()
{
    ThreadSafeCounter counter;

    const int numThreads = 4;
    const int incrementsPerThread = 10000;

    std::vector<std::thread> threads;

    // Create threads that increment the counter
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back([&counter, incrementsPerThread]() {
            for (int j = 0; j < incrementsPerThread; ++j) {
                counter.increment();
            }
        });
    }

    // Create threads that decrement the counter
    for (int i = 0; i < numThreads / 2; ++i) {
        threads.emplace_back([&counter, incrementsPerThread]() {
            for (int j = 0; j < incrementsPerThread; ++j) {
                counter.decrement();
            }
        });
    }

    // Wait for all threads to finish
    for (auto& t : threads) {
        t.join();
    }

    // Expected value: numThreads * incrementsPerThread - (numThreads/2) * incrementsPerThread
    // = 4 * 10000 - 2 * 10000 = 20000
    int expected = numThreads * incrementsPerThread - (numThreads / 2) * incrementsPerThread;
    int actual = counter.getValue();

    printf("Expected: %d\n", expected);
    printf("Actual:   %d\n", actual);

    if (expected == actual) {
        printf("SUCCESS: Counter is thread-safe!\n");
    } else {
        printf("FAILURE: Counter has race conditions!\n");
    }

    return 0;
}
