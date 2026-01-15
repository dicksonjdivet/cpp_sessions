#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <utility>

struct Point {
    Point() : x(0), y(0) {}
    Point(int xVal, int yVal) : x(xVal), y(yVal) {}
	int x;
	int y;
};

struct Person {
public:
    char name[50];
    int age;
    Person(const char* n, int a) : age(a) {
        strncpy(name, n, sizeof(name));
        name[sizeof(name) - 1] = '\0'; // Ensure null-termination
    }
};

int main()
{
	// Test with int
	// UniquePtr<int> intPtr(new int(42));
	// printf("Value: %d\n", *intPtr);

	// // Test with struct
	// UniquePtr<Point> pointPtr(new Point{10, 20});
	// printf("Point: (%d, %d)\n", pointPtr->x, pointPtr->y);

	// // Test move constructor
	// UniquePtr<int> movedPtr(std::move(intPtr));
	// printf("Moved value: %d\n", *movedPtr);
	// printf("Original ptr after move: %p\n", (void*)intPtr.get());

	// // Test move assignment
	// UniquePtr<int> anotherPtr(new int(100));
	// anotherPtr = std::move(movedPtr);
	// printf("After move assignment: %d\n", *anotherPtr);

	// // Test release
	// int* rawPtr = anotherPtr.release();
	// printf("Released value: %d\n", *rawPtr);
	// printf("Ptr after release: %p\n", (void*)anotherPtr.get());
	// delete rawPtr;

	// // Test reset
	// UniquePtr<int> resetPtr(new int(200));
	// resetPtr.reset(new int(300));
	// printf("After reset: %d\n", *resetPtr);

    // Exercice 3: make_unique UNCOMMENT WHEN EXERCICE 2 AND 3 ARE DONE

    // Test make_unique with no arguments
	// UniquePtr<int> intPtr = make_unique<int>();
	// printf("Default int value: %d\n", *intPtr);

	// Test make_unique with single argument
	// UniquePtr<int> intPtr2 = make_unique<int>(42);
	// printf("Int value: %d\n", *intPtr2);

	// Test make_unique with Point (two arguments)
	// UniquePtr<Point> pointPtr = make_unique<Point>(10, 20);
	// printf("Point: (%d, %d)\n", pointPtr->x, pointPtr->y);

	// Test make_unique with Person (two arguments of different types)
	// UniquePtr<Person> personPtr = make_unique<Person>("Alice", 30);
	// printf("Person: %s, %d years old\n", personPtr->name, personPtr->age);

	return 0;
}
