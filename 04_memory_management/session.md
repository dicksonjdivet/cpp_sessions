# C -> C++ Session

## Memory management

### Operator new and delete

In C++ you can create an object on the heap using the operator `new`.

```c++
class Car {
...
};

int main()
{
    // This will allocate an object car on the heap
    Car* car = new Car();
    return 0;
    // Warning memory leak here !
}
```

To delete an object you will have to call the `delete` operator.

```c++
int main()
{
    // This will allocate an object car on the heap and call the Car constructor
    Car* car = new Car();


    // Call the Car destructor and release the memory
    delete car;

    // No memory leak
    return 0;
}
```

Both operators corresponds to the following implementation:

```c++
#include <cstdlib>
#include <new>
#include <iostream>

// Allocate raw memory
// In C++ it is possible to override both operators !
void* operator new(std::size_t size) {
    if (void* ptr = std::malloc(size)) {
        return ptr;
    }
    throw std::bad_alloc();
}

// Deallocate raw memory
void operator delete(void* ptr) noexcept {
    std::free(ptr);
}

```

The keywords `new` and `delete` brings conceptually:

```c++
new expression:
    operator new  -> allocate memory
    constructor   -> initialize object

delete expression:
    destructor    -> cleanup object
    operator delete -> free memory
```

If multiple objects are allocated you can use `new[]` and `delete[]`:

```c++
int main()
{
    // Allocate an array of 10 Car objects on the heap
    Car* cars = new Car[10];
    // Do something with cars
    // Release the array of Car objects
    delete[] cars;
    return 0;
}
```

### Smart pointers

Since C++11 it is possible to use smart pointers to manage memory automatically.

There are three main types of smart pointers in C++: `std::unique_ptr`, `std::shared_ptr`, and `std::weak_ptr`.

With those we retrieve our concept of RAII (Resource Acquisition Is Initialization) from C++ where we don't have to manually manage memory.

#### Unique pointer

```c++
#include <memory> // For std::unique_ptr

int main()
{
    // Create a unique pointer to a Car object
    // std::unique_ptr<Car> carPtr = std::unique_ptr<Car>(new Car());
    std::unique_ptr<Car> carPtr = std::make_unique<Car>(); // Since C++14

    // Use the carPtr as a regular pointer
    carPtr->drive();

    // No need to manually delete the Car object
    // It will be automatically deleted when carPtr goes out of scope
    return 0;
}
```

Unique pointers cannot be copied. The ownership is detained by a single object or scope.

```c++
class Car {
public:

private:
    std::unique_ptr<Engine> engine; // Unique ownership of Engine
};

int main()
{
    Car car1;
    // Car car2 = car1; // Error: cannot copy
    // Because the engine unique_ptr cannot be copied

    return 0;
}
```

#### Shared pointer

Shared

```c++
#include <memory> // For std::shared_ptr

class Database {
public:
    void query() {
        // Perform database query
    }
};

class Application
{
public:
    Application(std::shared_ptr<Database> db) : database(db) {}

    void run() {
        database->query();
    }
private:
    std::shared_ptr<Database> database; // Shared ownership of Database
};

int main()
{
    // Create a shared pointer to a Database object
    std::shared_ptr<Database> dbPtr = std::make_shared<Database>();

    // Create multiple Application instances sharing the same Database
    Application app1(dbPtr);
    Application app2(dbPtr);

    app1.run();
    app2.run();

    // No need to manually delete the Database object
    // It will be automatically deleted when the last shared_ptr goes out of scope
    return 0;
}
```

Opposite to unique pointers, shared pointers can be copied. The ownership is shared between multiple objects or scopes.

#### Weak pointer

Weak pointers are used to break circular references in shared pointers.
They allow you to have a non-owning reference to an object managed by a shared pointer.

```c++
#include <memory> // For std::weak_ptr and std::shared_ptr

class Node {
public:
    Node(std::shared_ptr<Node> parentNode) : parent(parentNode) {}

    void setChild(std::shared_ptr<Node> childNode) {
        child = childNode;
    }
private:
    std::weak_ptr<Node> parent; // Non-owning reference to parent Node
    std::shared_ptr<Node> child;  // Owning reference to child Node
};

int main()
{
    // Create a shared pointer to a Node object
    std::shared_ptr<Node> rootNode = std::make_shared<Node>(nullptr);

    // Create a child Node with a weak reference to the parent
    std::shared_ptr<Node> childNode = std::make_shared<Node>(rootNode);

    rootNode->setChild(childNode);

    return 0;
}
```

### Ownership transfer: move semantics

In C++11 it is possible to transfer ownership of an object using move semantics with `std::move`.
After copy constructor and copy assignment operator, C++11 introduced move constructor and move assignment operator.

#### Move constructor

```c++

class Car {
public:
    Car() : engine(std::make_unique<Engine>()) {}
    // Move constructor
    Car(Car&& other) noexcept : engine(std::move(other.engine)) {
        other.engine = nullptr; // Leave other in a valid state
    }
private:
    std::unique_ptr<Engine> engine; // Unique ownership of Engine
};

int main()
{
    Car car1;
    Car car2 = std::move(car1); // Transfer ownership from car1 to car

    // Now car1's engine is nullptr
    return 0;
}
```

#### Move assignment operator

```c++
class Car {
public:
    Car() : engine(std::make_unique<Engine>()) {}
    // Move assignment operator
    Car& operator=(Car&& other) noexcept {
        if (this != &other) {
            engine = std::move(other.engine);
            other.engine = nullptr; // Leave other in a valid state
        }
        return *this;
    }
private:
    std::unique_ptr<Engine> engine; // Unique ownership of Engine
};

int main()
{
    Car car1;
    Car car2;
    car2 = std::move(car1); // Transfer ownership from car1 to car2

    // Now car1's engine is nullptr
    return 0;
}
```

This can be useful to avoid unnecessary copies and improve performance when dealing with large objects.

```c++

#include <string>

int main()
{
    std::string str1 = "Hello, World!";
    std::string str2 = std::move(str1); // Transfer ownership of str1 to str2

    // Now str1 is in a valid but unspecified state
    return 0;
}
```

The compiler will implicitly declare a move constructor and move assignment operator only if:

- No user-declared copy constructor

- No user-declared copy assignment operator

- No user-declared destructor


### Exercice 1: leak detector

Implement a simple memory leak detector by overriding the global `new` and `delete`, `new[]` and `delete[]` operators.

- Use a static variable to keep track of the number of allocations and deallocations.

- Print the size of the leak (allocations - deallocations) at the end of the program.

Tips: Embed the size of each allocation during the `new` and `new[]` operators and use it during the `delete` and `delete[]` operators to keep track of the total leaked memory size.

### Exercise 2: smart pointer

Implement a class named `UniqueGPIO` that uses a regular pointer to manage a `GPIO` object.
- Implement the constructor, destructor, move constructor, and move assignment operator for `UniqueGPIO`.