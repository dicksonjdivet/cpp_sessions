#include <cstdio>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <chrono>

// TODO: Implement a BlockingQueue<T> template class
// - Has methods push(T item) and T pop()
// - pop() blocks if the queue is empty until an item is available
// - Uses std::mutex and std::condition_variable
// - Bonus: Add a maximum capacity where push() blocks if full

template <typename T>
class BlockingQueue {
public:
    BlockingQueue(size_t maxCapacity = 0) : m_maxCapacity(maxCapacity) {}

    void push(T item) {
        // TODO: Implement thread-safe push
        // If maxCapacity > 0, block if queue is full
    }

    T pop() {
        // TODO: Implement thread-safe pop
        // Block if queue is empty until an item is available
        return T{};
    }

    size_t size() const {
        // TODO: Implement thread-safe size
        return 0;
    }

    bool empty() const {
        // TODO: Implement thread-safe empty check
        return true;
    }

private:
    std::queue<T> m_queue;
    size_t m_maxCapacity; // 0 means unlimited
    // TODO: Add mutex and condition_variable members
};

void producer(BlockingQueue<int>& queue, int id, int count) {
    for (int i = 0; i < count; ++i) {
        int value = id * 1000 + i;
        queue.push(value);
        printf("Producer %d: pushed %d\n", id, value);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    printf("Producer %d: finished\n", id);
}

void consumer(BlockingQueue<int>& queue, int id, int count) {
    for (int i = 0; i < count; ++i) {
        int value = queue.pop();
        printf("Consumer %d: popped %d\n", id, value);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    printf("Consumer %d: finished\n", id);
}

int main()
{
    // Create a blocking queue with max capacity of 5
    BlockingQueue<int> queue(5);

    const int numProducers = 2;
    const int numConsumers = 2;
    const int itemsPerProducer = 10;

    // Total items produced = numProducers * itemsPerProducer = 20
    // Each consumer will consume half of that
    const int itemsPerConsumer = (numProducers * itemsPerProducer) / numConsumers;

    std::vector<std::thread> threads;

    // Start producers
    for (int i = 0; i < numProducers; ++i) {
        threads.emplace_back(producer, std::ref(queue), i + 1, itemsPerProducer);
    }

    // Start consumers
    for (int i = 0; i < numConsumers; ++i) {
        threads.emplace_back(consumer, std::ref(queue), i + 1, itemsPerConsumer);
    }

    // Wait for all threads to finish
    for (auto& t : threads) {
        t.join();
    }

    printf("\nAll producers and consumers finished!\n");
    printf("Queue size at end: %zu (should be 0)\n", queue.size());

    return 0;
}
