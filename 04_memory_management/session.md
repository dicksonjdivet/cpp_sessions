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

But the keywords `new` and `delete` brings conceptually:

```c++
new expression:
    operator new  -> allocate memory
    constructor   -> initialize object

delete expression:
    destructor    -> cleanup object
    operator delete -> free memory
```

```
Exercice: leak detector !
```