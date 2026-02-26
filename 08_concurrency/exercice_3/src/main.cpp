#include <cstdio>
#include <vector>
#include <numeric>
#include <chrono>
#include <future>
#include <thread>

// Helper function to measure execution time
template <typename Func>
long long measureTime(Func&& func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

// TODO: Implement sequential sum
// Compute the sum of all elements in the vector sequentially
long long sequentialSum(const std::vector<int>& data) {
    // TODO: Implement
    return 0;
}

// TODO: Implement parallel sum using std::async
// - Split the vector into chunks (one per available hardware thread)
// - Compute the sum of each chunk in parallel using std::async
// - Combine the results to get the total sum
// Tips: Use std::thread::hardware_concurrency() to get the number of threads
long long parallelSum(const std::vector<int>& data) {
    // TODO: Implement
    return 0;
}

// Helper function to compute sum of a range
long long sumRange(const std::vector<int>& data, size_t start, size_t end) {
    long long sum = 0;
    for (size_t i = start; i < end; ++i) {
        sum += data[i];
    }
    return sum;
}

int main()
{
    // Create a large vector of numbers
    const size_t dataSize = 100'000'000; // 100 million elements
    printf("Creating vector with %zu elements...\n", dataSize);

    std::vector<int> data(dataSize);
    
    // Fill with values 1 to dataSize
    for (size_t i = 0; i < dataSize; ++i) {
        data[i] = static_cast<int>(i + 1);
    }

    printf("Vector created. Starting benchmarks...\n\n");

    // Compute expected sum using formula: n * (n + 1) / 2
    long long expectedSum = static_cast<long long>(dataSize) * (dataSize + 1) / 2;
    printf("Expected sum (using formula): %lld\n\n", expectedSum);

    // Benchmark sequential sum
    long long seqResult = 0;
    long long seqTime = measureTime([&]() {
        seqResult = sequentialSum(data);
    });

    printf("Sequential sum:\n");
    printf("  Result: %lld\n", seqResult);
    printf("  Time:   %lld µs (%.3f ms)\n", seqTime, seqTime / 1000.0);
    printf("  Status: %s\n\n", seqResult == expectedSum ? "CORRECT" : "INCORRECT");

    // Benchmark parallel sum
    long long parResult = 0;
    long long parTime = measureTime([&]() {
        parResult = parallelSum(data);
    });

    printf("Parallel sum:\n");
    printf("  Result: %lld\n", parResult);
    printf("  Time:   %lld µs (%.3f ms)\n", parTime, parTime / 1000.0);
    printf("  Status: %s\n\n", parResult == expectedSum ? "CORRECT" : "INCORRECT");

    // Compare performance
    if (seqTime > 0 && parTime > 0) {
        double speedup = static_cast<double>(seqTime) / parTime;
        printf("Performance comparison:\n");
        printf("  Hardware threads available: %u\n", std::thread::hardware_concurrency());
        printf("  Speedup: %.2fx\n", speedup);
        
        if (speedup > 1.0) {
            printf("  Parallel version is %.1f%% faster!\n", (speedup - 1.0) * 100);
        } else {
            printf("  Sequential version is faster (parallel overhead too high for this workload)\n");
        }
    }

    return 0;
}
