# C -> C++ Session

## STL Containers

### Introduction

In C++ there is a lot of tools available with the language.

The standard library is the C++ library that is "most of the time" shipped with a compiler version.

Standard library tools are always namespaced with "std".
Inside the standard library you will encounter things such as:
- streams (file and console I/O)
- math functions
- strings
- time and date functions
- dynamic memory management
- algorithms
- containers
- iterators
- functionals
- and more...

In this session we will focus on STL containers.

### What is a container ?

A container is a type that stores and manages a collection of objects of the same type and provides a standard way to access and iterate over them.

We are now going to see the most common types of containers in C++, we will compare their performance in terms of complexity (Big O notation).

### Array container

C++ Arrays are fixed-sized containers.
Like their C companions all objects are contiguous in memory !
Meaning that their size is determined at compile time !

```c++

// Including array container type in C++
#include <array>

int main()
{
    // Initialization with {} brackets
    std::array<int, 4> my_int_array = {
        1, 2, 3, 4
    };

    // Not forced to do the sizeof(array) /sizeof(array[0]) C trick !
    printf("Array is of size: %d\n", my_int_array.size());

    my_int_array[0] = 3; // Access like normal array

    return 0;
}
```

Question: Now that you know a bit more about templates, what would be the template signature of array here ?

#### Performances

- Access O(1)
- Search O(n)
- No insertion/deletion possible

### Vector

It is one of the most used STL containers.
C++ vectors are dynamic-sized containers.
In the background and by default this container will use heap allocated memory !

It is possible to feed custom allocators but this is not the subject of this session :).

Like arrays all elements are contiguous in memory.

```c++

#include <vector>

int main() {
    std::vector<int> my_vector; // Default initialization, no object

    printf("%d\n", my_vector.size()); // 0 elements here !

    my_vector.push_back(3); // We are inserting an element at the end of the container

    printf("%d\n", my_vector[0]); // 3

    return 0;
}
```

#### Performances

- Access O(1)
- Insertion/Deletion at end O(1) amortized
- Insertion/Deletion at beginning or middle O(n)
- Search O(n)

> **What does "amortized" mean?**
> 
> When you `push_back` and the vector has available capacity, insertion is O(1).
> However, if the vector is full, it must:
> 1. Allocate a new buffer (typically 2x the current capacity)
> 2. Copy or move ALL existing elements to the new buffer
> 3. Deallocate the old buffer
> 
> This reallocation is O(n)! But since capacity doubles each time, reallocations become increasingly rare. Over n insertions, the total cost averages to O(1) per insertion.

### List

A list is a doubly-linked list container.
Unlike vectors and arrays, elements are NOT contiguous in memory.
Each element (node) contains pointers to the previous and next elements.

This makes insertion and deletion very efficient anywhere in the list, but random access is slow.

```c++

#include <list>

int main() {
    std::list<int> my_list = {1, 2, 3};

    my_list.push_back(4);   // Insert at end
    my_list.push_front(0);  // Insert at beginning

    // Iterate through the list
    for (int value : my_list) {
        printf("%d ", value); // 0 1 2 3 4
    }

    // Old C++ style iteration
    for (std::list<int>::iterator it = my_list.begin(); it != my_list.end(); ++it) {
        printf("%d ", *it);
    }

    my_list.remove(2); // Remove all elements with value 2

    return 0;
}
```

#### Performances

- Access O(n) - no random access!
- Insertion/Deletion O(1) if you have an iterator to the position
- Search O(n)

### Forward List

A forward list is a singly-linked list container.
Like list, elements are NOT contiguous in memory.
Each element only contains a pointer to the next element (no previous pointer).

This makes it more memory efficient than `std::list` but you can only traverse forward.

```c++

#include <forward_list>

int main() {
    std::forward_list<int> my_flist = {1, 2, 3};

    my_flist.push_front(0);  // Insert at beginning (no push_back!)

    // Insert after a specific position
    auto it = my_flist.begin();
    my_flist.insert_after(it, 10); // Inserts 10 after the first element

    for (int value : my_flist) {
        printf("%d ", value); // 0 10 1 2 3
    }

    return 0;
}
```

#### Performances

- Access O(n) - no random access!
- Insertion/Deletion O(1) if you have an iterator
- Search O(n)
- More memory efficient than std::list

### Deque (Double-Ended Queue)

A deque allows fast insertion and deletion at both ends.
Elements are stored in chunks of contiguous memory, but the chunks themselves are not contiguous.

It provides random access like vector but with efficient operations at both ends.

```c++

#include <deque>

int main() {
    std::deque<int> my_deque = {2, 3, 4};

    my_deque.push_back(5);   // Insert at end
    my_deque.push_front(1);  // Insert at beginning

    printf("%d\n", my_deque[0]); // 1 - random access like vector!
    printf("%d\n", my_deque.front()); // 1
    printf("%d\n", my_deque.back());  // 5

    my_deque.pop_front(); // Remove first element
    my_deque.pop_back();  // Remove last element

    return 0;
}
```

#### Performances

- Access O(1)
- Insertion/Deletion at both ends O(1)
- Insertion/Deletion in middle O(n)
- Search O(n)

### Set

A set is an ordered container that stores unique elements.
Elements are automatically sorted (by default in ascending order).
Internally implemented as a balanced binary search tree (usually red-black tree).

```c++

#include <set>

int main() {
    std::set<int> my_set = {3, 1, 4, 1, 5}; // Duplicates are ignored!

    printf("Size: %d\n", my_set.size()); // 4 (no duplicate 1)

    my_set.insert(2);
    my_set.insert(3); // Already exists, ignored

    // Elements are always sorted!
    for (int value : my_set) {
        printf("%d ", value); // 1 2 3 4 5
    }

    // Check if element exists
    if (my_set.find(3) != my_set.end()) {
        printf("\n3 is in the set!\n");
    }

    my_set.erase(4); // Remove element

    return 0;
}
```

#### Performances

- Access O(log n)
- Insertion O(log n)
- Deletion O(log n)
- Search O(log n)

### Unordered Set

An unordered set stores unique elements like set, but elements are NOT sorted.
Internally implemented as a hash table, which provides faster average operations than set.

```c++

#include <unordered_set>

int main() {
    std::unordered_set<int> my_uset = {3, 1, 4, 1, 5};

    printf("Size: %d\n", my_uset.size()); // 4

    my_uset.insert(2);

    // Order is NOT guaranteed!
    for (int value : my_uset) {
        printf("%d ", value); // Could be any order
    }

    // Check if element exists
    if (my_uset.count(3) > 0) {
        printf("\n3 is in the set!\n");
    }

    return 0;
}
```

#### Performances

- Access O(1) average, O(n) worst case
- Insertion O(1) average, O(n) worst case
- Deletion O(1) average, O(n) worst case
- Search O(1) average, O(n) worst case

### Map

A map is an ordered associative container that stores key-value pairs.
Keys are unique and automatically sorted.
Internally implemented as a balanced binary search tree.

```c++

#include <map>
#include <string>

int main() {
    std::map<std::string, int> ages;

    ages["Alice"] = 25;
    ages["Bob"] = 30;
    ages.insert({"Charlie", 35});

    printf("Bob's age: %d\n", ages["Bob"]); // 30

    // Iterate over key-value pairs
    for (const auto& pair : ages) {
        printf("%s is %d years old\n", pair.first.c_str(), pair.second);
    }
    // Output is sorted by key: Alice, Bob, Charlie

    // Check if key exists
    if (ages.find("Alice") != ages.end()) {
        printf("Alice is in the map!\n");
    }

    ages.erase("Bob"); // Remove by key

    return 0;
}
```

#### Performances

- Access by key O(log n)
- Insertion O(log n)
- Deletion O(log n)
- Search O(log n)

### Unordered Map

An unordered map stores key-value pairs like map, but keys are NOT sorted.
Internally implemented as a hash table, which provides faster average operations than map.

```c++

#include <unordered_map>
#include <string>

int main() {
    std::unordered_map<std::string, int> ages;

    ages["Alice"] = 25;
    ages["Bob"] = 30;
    ages["Charlie"] = 35;

    printf("Bob's age: %d\n", ages["Bob"]); // 30

    // Order is NOT guaranteed!
    for (const auto& pair : ages) {
        printf("%s is %d years old\n", pair.first.c_str(), pair.second);
    }

    // Check if key exists (alternative to find)
    if (ages.count("Alice") > 0) {
        printf("Alice is in the map!\n");
    }

    return 0;
}
```

#### Performances

- Access by key O(1) average, O(n) worst case
- Insertion O(1) average, O(n) worst case
- Deletion O(1) average, O(n) worst case
- Search O(1) average, O(n) worst case

### Stack

A stack is a container adapter that provides LIFO (Last In, First Out) operations.

```c++

#include <stack>

int main() {
    std::stack<int> my_stack;

    my_stack.push(1);
    my_stack.push(2);
    my_stack.push(3);

    printf("Top: %d\n", my_stack.top()); // 3

    my_stack.pop(); // Remove top element

    printf("Top after pop: %d\n", my_stack.top()); // 2
    printf("Size: %d\n", my_stack.size()); // 2

    return 0;
}
```

#### Performances

- Push O(1)
- Pop O(1)
- Top O(1)
- No random access or iteration!

### Queue

A queue is a container adapter that provides FIFO (First In, First Out) operations.

```c++

#include <queue>

int main() {
    std::queue<int> my_queue;

    my_queue.push(1);
    my_queue.push(2);
    my_queue.push(3);

    printf("Front: %d\n", my_queue.front()); // 1
    printf("Back: %d\n", my_queue.back());   // 3

    my_queue.pop(); // Remove front element

    printf("Front after pop: %d\n", my_queue.front()); // 2

    return 0;
}
```

#### Performances

- Push O(1)
- Pop O(1)
- Front/Back O(1)
- No random access or iteration!

## Exercises

### Exercice 1:

>For each scenario, choose the most appropriate container and justify:
>
>a) You need to store 1000 sensor readings and frequently access them by index
>
>b) You need to check if a username already exists in a system with millions of users
>
>c) You need to process tasks in the order they arrive
>
>d) You need to maintain a sorted list of high scores with frequent insertions
>
>e) You need to frequently insert/remove elements in the middle of a collection
>
>f) You need to associate employee IDs with their names, with fast lookups

### Exercice 2:

> Write a program that:
> 1. Inserts 100,000 integers into both a vector and a list at the front. (use insert() function for vector)
> 2. Measures and compares the time taken
> 3. Explains why one is faster
