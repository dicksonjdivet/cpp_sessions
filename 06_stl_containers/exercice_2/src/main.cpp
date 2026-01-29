#include <chrono>
#include <cstdio>

#include <list>
#include <vector>

void compute_list()
{
    // Simulate some work with a list
}

void compute_vector()
{
    // Simulate some work with a vector
}

void chronometer(const char* name, void (*func)())
{
    auto start = std::chrono::high_resolution_clock::now();

    func();

    auto end =   std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    printf("Duration of %s: %lld microseconds\n", name, duration);
}

int main()
{
    chronometer("List", compute_list);

    chronometer("Vector", compute_vector);

    return 0;
}

