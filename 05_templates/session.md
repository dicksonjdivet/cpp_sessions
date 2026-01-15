# C -> C++ Session

## Templates

### Introduction

Templates are one of the most powerful features of C++, enabling generic programming.
They allow you to write code that works with any data type, avoiding code duplication while maintaining type safety.

Templates are resolved at compile time, meaning there is no runtime overhead for using them.

### Function templates

A function template allows you to write a single function that can work with different types.

```c++
// Template function declaration
template <typename T>
T sum(T a, T b)
{
    return a + b;
}

int main()
{
    int result1 = sum(1, 2);           // T is deduced as int
    double result2 = sum(1.5, 2.5);    // T is deduced as double
    
    // Explicit type specification
    int result3 = sum<int>(1, 2);
    
    return 0;
}
```

The `typename` keyword can be replaced by `class` (they are equivalent in this context):

```c++
template <class T>
T max(T a, T b)
{
    return (a > b) ? a : b;
}
```

### Multiple template parameters

You can have multiple template parameters:

```c++
template <typename ReturnType, typename ArgType>
ReturnType convert(ArgType value)
{
    return static_cast<ReturnType>(value);
}

int main()
{
    int intValue = convert<int, double>(3.14);
    float floatValue = convert<float, int>(42);
    
    return 0;
}
```

### Class templates

Templates can also be applied to classes, allowing you to create generic data structures.

```c++
template <typename T>
class Container {
public:
    Container(T value) : m_value(value) {}
    
    T getValue() const { return m_value; }
    void setValue(T value) { m_value = value; }

private:
    T m_value;
};

int main()
{
    Container<int> intContainer(42);
    Container<std::string> stringContainer("Hello");
    
    printf("%d\n", intContainer.getValue());
    
    return 0;
}
```

### Method definition outside class template

When defining methods outside a class template, you need to repeat the template declaration:

```c++
template <typename T>
class Container {
public:
    Container(T value);
    T getValue() const;
    void setValue(T value);

private:
    T m_value;
};

// Method definitions outside the class
template <typename T>
Container<T>::Container(T value) : m_value(value) {}

template <typename T>
T Container<T>::getValue() const
{
    return m_value;
}

template <typename T>
void Container<T>::setValue(T value)
{
    m_value = value;
}
```

### Non-type template parameters

Templates can also have non-type parameters like integers:

```c++
template <typename T, int Size>
class FixedArray {
public:
    T& operator[](int index) { return m_data[index]; }
    const T& operator[](int index) const { return m_data[index]; }
    
    constexpr int size() const { return Size; }

private:
    T m_data[Size];
};

int main()
{
    FixedArray<int, 10> array;
    
    for (int i = 0; i < array.size(); ++i) {
        array[i] = i * 2;
    }
    
    return 0;
}
```

### Template specialization

Sometimes you need a specific implementation for a particular type. This is called template specialization.

#### Full specialization

```c++
// Primary template
template <typename T>
class Printer {
public:
    void print(T value) {
        printf("Value: %s\n", std::to_string(value).c_str());
    }
};

// Full specialization for const char*
template <>
class Printer<const char*> {
public:
    void print(const char* value) {
        printf("String: %s\n", value);
    }
};

int main()
{
    Printer<int> intPrinter;
    intPrinter.print(42);           // Output: Value: 42
    
    Printer<const char*> stringPrinter;
    stringPrinter.print("Hello");   // Output: String: Hello
    
    return 0;
}
```

### Default template arguments

Template parameters can have default values:

```c++
template <typename T = int, int Size = 10>
class Buffer {
public:
    T& operator[](int index) { return m_data[index]; }
    constexpr int size() const { return Size; }

private:
    T m_data[Size];
};

int main()
{
    Buffer<> defaultBuffer;           // T = int, Size = 10
    Buffer<double> doubleBuffer;      // T = double, Size = 10
    Buffer<float, 20> customBuffer;   // T = float, Size = 20
    
    return 0;
}
```

### Variadic templates (C++11)

Variadic templates allow you to create templates that accept any number of arguments.

```c++
#include <cstdio>

// Base case: no arguments
void print()
{
    printf("\n");
}

// Recursive case: at least one argument
template <typename T, typename... Args>
void print(T first, Args... rest)
{
    printf("%s ", std::to_string(first).c_str());
    print(rest...);  // Recursive call with remaining arguments
}

int main()
{
    print(1, 2.5, 3, 4.0f);  // Output: 1 2.5 3 4.0
    
    return 0;
}
```

### Fold expressions (C++17)

C++17 introduced fold expressions to simplify variadic template operations:

```c++
// Sum all arguments using fold expression
template <typename... Args>
auto sum(Args... args)
{
    return (args + ...);  // Unary right fold
}

// Print all arguments
template <typename... Args>
void printAll(Args... args)
{
    ((printf("%d ", args)), ...);  // Unary right fold with comma operator
    printf("\n");
}

int main()
{
    int result = sum(1, 2, 3, 4, 5);  // result = 15
    
    printAll(1, 2, 3, 4, 5);  // Output: 1 2 3 4 5
    
    return 0;
}
```

### Template compilation model

Templates are typically defined in header files because the compiler needs to see the full definition to instantiate them.

```c++
// Container.hpp
#pragma once

template <typename T>
class Container {
public:
    Container(T value) : m_value(value) {}
    T getValue() const { return m_value; }
    void setValue(T value) { m_value = value; }

private:
    T m_value;
};

// main.cpp
#include "Container.hpp"

int main()
{
    Container<int> c(42);
    return 0;
}
```

If you want to separate declaration and definition, you can use explicit instantiation:

```c++
// Container.hpp
#pragma once

template <typename T>
class Container {
public:
    Container(T value);
    T getValue() const;
private:
    T m_value;
};

// Container.cpp
#include "Container.hpp"

template <typename T>
Container<T>::Container(T value) : m_value(value) {}

template <typename T>
T Container<T>::getValue() const { return m_value; }

// Explicit instantiation for supported types
template class Container<int>;
template class Container<double>;
template class Container<std::string>;
```

### Exercice 1: Generic Stack

Implement a class template `Stack<...>` that:
- Uses a fixed-size array (template parameter for size)
- Has methods: `push(T)`, `pop()`, `top()`, `isEmpty()`, `isFull()`
- Properly handles stack overflow and underflow

### Exercice 2: unique_ptr with Templates

Implement a simplified version of `std::unique_ptr` as a class template `UniquePtr<T>`. (See cppreference for reference: https://en.cppreference.com/w/cpp/memory/unique_ptr, do not focus on custom deleters for this exercise.)

The class should:
- Manage a dynamically allocated object of type T
- Implement constructor, destructor, copy constructor (deleted), move constructor, copy assignment (deleted), and move assignment
- Overload the dereference (`*`) and member access (`->`) operators
- Provide a method `get()` to access the raw pointer
- Provide a method `release()` to release ownership of the managed object
- Provide a method `reset(T* ptr = nullptr)` to replace the managed object

You can inspire yourself from your implementation of `UniqueGPIO` from the previous session and convert it to use templates.

### Exercice 3: Variadic Function Template

Implement a std::make_unique-like function template `make_unique<T>(Args&&... args)` that:
- Accepts any number of arguments
- Constructs an object of type T with the provided arguments
- Returns a `UniquePtr<T>` managing the created object
