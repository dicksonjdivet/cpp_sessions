# C -> C++ Session

## Concurrency

### Introduction

Concurrency is one of the most powerful yet challenging aspects of modern programming. In C++11 and later, the language provides built-in support for concurrent and parallel programming through the `<thread>`, `<mutex>`, `<condition_variable>`, `<future>`, and `<atomic>` headers.

Understanding concurrency is essential for:
- Improving performance on multi-core processors
- Creating responsive applications
- Handling I/O operations efficiently
- Building scalable server applications

### Threads in C

Before C++11, threading required platform-specific APIs like POSIX threads (pthreads) on Linux/Unix or Windows threads on Windows.

```c
#include <pthread.h>
#include <stdio.h>

void* thread_function(void* arg) {
    int* value = (int*)arg;
    printf("Thread received value: %d\n", *value);
    return NULL;
}

int main() {
    pthread_t thread;
    int value = 42;
    
    // Create thread
    pthread_create(&thread, NULL, thread_function, &value);
    
    // Wait for thread to complete
    pthread_join(thread, NULL);
    
    return 0;
}
```

The main drawbacks of this approach:
- Platform-specific code
- Manual memory management
- No type safety (void pointers)
- Error-prone API

### std::thread (C++11)

C++11 introduced `std::thread` as a portable, type-safe way to create threads.

```c++
#include <thread>
#include <cstdio>

void thread_function(int value) {
    printf("Thread received value: %d\n", value);
}

int main() {
    // Create a thread that executes thread_function
    std::thread t(thread_function, 42);
    
    // Wait for the thread to complete
    t.join();
    
    return 0;
}
```

#### Using lambdas with threads

Lambdas work naturally with `std::thread`:

```c++
#include <thread>
#include <cstdio>

int main() {
    int value = 10;
    
    std::thread t([value]() {
        printf("Lambda received: %d\n", value);
    });
    
    t.join();
    
    return 0;
}
```

#### Using member functions

You can also run member functions in a thread:

```c++
#include <thread>
#include <cstdio>

class Worker {
public:
    void doWork(int iterations) {
        for (int i = 0; i < iterations; ++i) {
            printf("Working... %d\n", i);
        }
    }
};

int main() {
    Worker worker;
    
    // Pass: member function pointer, object pointer, arguments
    std::thread t(&Worker::doWork, &worker, 5);
    t.join();
    
    return 0;
}
```

### Thread lifecycle: join vs detach

A thread must be either joined or detached before the `std::thread` object is destroyed. Otherwise, the program will terminate.

#### join()

`join()` blocks the calling thread until the thread completes:

```c++
#include <thread>
#include <chrono>
#include <cstdio>

int main() {
    std::thread t([]() {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        printf("Thread finished\n");
    });
    
    printf("Waiting for thread...\n");
    t.join(); // Blocks until thread completes
    printf("Thread joined\n");
    
    return 0;
}
```

#### detach()

`detach()` separates the thread from the `std::thread` object, allowing it to run independently:

```c++
#include <thread>
#include <chrono>
#include <cstdio>

int main() {
    std::thread t([]() {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        printf("Detached thread finished\n");
    });
    
    t.detach(); // Thread runs independently
    
    printf("Main continuing...\n");
    
    // Warning: if main exits before the detached thread completes,
    // the behavior is undefined. Be careful with detached threads!
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    return 0;
}
```

### Race conditions and data races

When multiple threads access shared data, problems can occur:

```c++
#include <thread>
#include <cstdio>

int counter = 0;

void increment() {
    for (int i = 0; i < 100000; ++i) {
        counter++; // Data race! Not atomic
    }
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);
    
    t1.join();
    t2.join();
    
    // Expected: 200000, but result is unpredictable!
    printf("Counter: %d\n", counter);
    
    return 0;
}
```

The `counter++` operation is not atomic - it involves:
1. Read the value
2. Increment the value
3. Write the value back

Two threads can interleave these operations, causing lost updates.

### std::mutex

A mutex (mutual exclusion) protects shared data by allowing only one thread to access it at a time:

```c++
#include <thread>
#include <mutex>
#include <cstdio>

int counter = 0;
std::mutex counter_mutex;

void increment() {
    for (int i = 0; i < 100000; ++i) {
        counter_mutex.lock();
        counter++;
        counter_mutex.unlock();
    }
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);
    
    t1.join();
    t2.join();
    
    printf("Counter: %d\n", counter); // Always 200000
    
    return 0;
}
```

### RAII with std::lock_guard and std::unique_lock

Manually calling `lock()` and `unlock()` is error-prone. Use RAII wrappers instead:

#### std::lock_guard

```c++
#include <thread>
#include <mutex>
#include <cstdio>

int counter = 0;
std::mutex counter_mutex;

void increment() {
    for (int i = 0; i < 100000; ++i) {
        std::lock_guard<std::mutex> lock(counter_mutex);
        counter++;
        // Mutex automatically unlocked when lock goes out of scope
    }
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);
    
    t1.join();
    t2.join();
    
    printf("Counter: %d\n", counter);
    
    return 0;
}
```

#### std::unique_lock

`std::unique_lock` is more flexible - it can be unlocked and relocked, and supports deferred locking:

```c++
#include <thread>
#include <mutex>
#include <cstdio>

std::mutex mtx;

void flexible_function() {
    std::unique_lock<std::mutex> lock(mtx);
    // Do work with lock held
    
    lock.unlock();
    // Do work without lock
    
    lock.lock();
    // Do more work with lock held
}

// Deferred locking
void deferred_locking() {
    std::unique_lock<std::mutex> lock(mtx, std::defer_lock);
    // Lock not held yet
    
    // ... do some preparation ...
    
    lock.lock(); // Now acquire the lock
    // ... critical section ...
}
```

### std::condition_variable

Condition variables allow threads to wait for a condition to become true:

```c++
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <cstdio>

std::mutex mtx;
std::condition_variable cv;
std::queue<int> data_queue;
bool finished = false;

void producer() {
    for (int i = 0; i < 10; ++i) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            data_queue.push(i);
            printf("Produced: %d\n", i);
        }
        cv.notify_one(); // Wake up one waiting consumer
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    {
        std::lock_guard<std::mutex> lock(mtx);
        finished = true;
    }
    cv.notify_all(); // Wake up all consumers
}

void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        
        // Wait until there's data or we're finished
        cv.wait(lock, []() {
            return !data_queue.empty() || finished;
        });
        
        while (!data_queue.empty()) {
            int value = data_queue.front();
            data_queue.pop();
            printf("Consumed: %d\n", value);
        }
        
        if (finished) break;
    }
}

int main() {
    std::thread prod(producer);
    std::thread cons(consumer);
    
    prod.join();
    cons.join();
    
    return 0;
}
```

The `wait` function:
1. Releases the mutex
2. Waits for notification
3. Reacquires the mutex when woken up
4. Checks the predicate to handle spurious wakeups

### std::atomic

For simple operations on primitive types, atomics are more efficient than mutexes:

```c++
#include <thread>
#include <atomic>
#include <cstdio>

std::atomic<int> counter{0};

void increment() {
    for (int i = 0; i < 100000; ++i) {
        counter++; // Atomic operation, no mutex needed
    }
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);
    
    t1.join();
    t2.join();
    
    printf("Counter: %d\n", counter.load()); // Always 200000
    
    return 0;
}
```

Common atomic operations:

```c++
std::atomic<int> value{0};

value.store(42);                    // Atomic write
int v = value.load();               // Atomic read
int old = value.exchange(100);      // Atomic swap, returns old value

// Compare-and-swap (CAS)
int expected = 100;
bool success = value.compare_exchange_strong(expected, 200);
// If value == expected, set value = 200 and return true
// Otherwise, set expected = value and return false

// Atomic arithmetic
value.fetch_add(10);    // Returns old value, adds 10
value.fetch_sub(5);     // Returns old value, subtracts 5
value++;                // Equivalent to fetch_add(1)
```

### std::future and std::async

`std::async` provides a high-level way to run tasks asynchronously and retrieve results:

```c++
#include <future>
#include <cstdio>

int compute(int x) {
    // Simulate expensive computation
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return x * x;
}

int main() {
    // Launch async task
    std::future<int> result = std::async(std::launch::async, compute, 42);
    
    printf("Computing...\n");
    
    // Do other work while computation runs...
    
    // Get result (blocks if not ready)
    int value = result.get();
    printf("Result: %d\n", value); // Output: Result: 1764
    
    return 0;
}
```

Launch policies:
- `std::launch::async` - Run in a new thread
- `std::launch::deferred` - Run lazily when `get()` is called
- Default - Implementation decides

### std::shared_mutex (C++17)

When you have many readers and few writers, `std::shared_mutex` allows multiple simultaneous readers:

```c++
#include <shared_mutex>
#include <thread>
#include <map>
#include <string>
#include <cstdio>

class ThreadSafeCache {
public:
    std::string get(int key) {
        // Shared lock - multiple readers allowed
        std::shared_lock<std::shared_mutex> lock(m_mutex);
        auto it = m_cache.find(key);
        return (it != m_cache.end()) ? it->second : "";
    }
    
    void set(int key, const std::string& value) {
        // Exclusive lock - only one writer
        std::unique_lock<std::shared_mutex> lock(m_mutex);
        m_cache[key] = value;
    }

private:
    std::map<int, std::string> m_cache;
    mutable std::shared_mutex m_mutex;
};
```
### Best practices

1. **Minimize shared state** - The less data shared between threads, the fewer synchronization issues.

2. **Prefer higher-level abstractions** - Use `std::async` and futures when possible instead of raw threads.

3. **Use RAII for locks** - Always use `lock_guard`, `unique_lock`, or `scoped_lock` instead of manual lock/unlock.

4. **Use atomics for simple operations** - For simple counters or flags, atomics are more efficient than mutexes.

5. **Avoid detached threads** - Prefer joining threads to ensure clean shutdown.

6. **Test thoroughly** - Concurrency bugs are often hard to reproduce. Use tools like ThreadSanitizer.

### Exercice 1: Thread-safe counter

Implement a `ThreadSafeCounter` class that:
- Has methods `increment()`, `decrement()`, and `getValue()`
- Is safe to use from multiple threads
- Use `std::mutex` and appropriate RAII lock guards

Test it by creating multiple threads that increment and decrement the counter concurrently.

### Exercice 2: Producer-Consumer queue

Implement a thread-safe `BlockingQueue<T>` class that:
- Has methods `push(T item)` and `T pop()`
- `pop()` blocks if the queue is empty until an item is available
- Uses `std::mutex` and `std::condition_variable`
- Optionally has a maximum capacity where `push()` blocks if full

Create a test program with multiple producer and consumer threads.

### Exercice 3: Parallel computation with std::async

Create a program that:
- Splits a large vector of numbers into chunks
- Computes the sum of each chunk in parallel using `std::async`
- Combines the results to get the total sum
- Compare the performance with a sequential implementation

Tips: Use `std::chrono` to measure execution time.
