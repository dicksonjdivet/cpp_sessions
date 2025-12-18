#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <exception>

static std::size_t HEAP_MEMORY_COUNTER = 0;

void* operator new(std::size_t size) {

}

// Deallocate raw memory
void operator delete(void* ptr) noexcept {

}

void* operator new[](std::size_t size) {

}

void operator delete[](void* ptr) noexcept {

}

class Wheel
{
public:
	int diameter;
};

class Engine
{
public:
	int horsepower;
};

class Car {
public:
	Wheel* wheels;
	Engine* engine;

	Car() {
		wheels = new Wheel[4];
		engine = new Engine();
	}

	~Car() {
		delete[] wheels;
		delete engine;
	}
};

int main()
{
	Car* car = new Car();
	//printf("Heap memory used: %zu bytes\n", HEAP_MEMORY_COUNTER);

	delete car;

	//printf("Heap memory used after deleting car: %zu bytes\n", HEAP_MEMORY_COUNTER);
	return 0;
}
