# C -> C++ Session

## General introduction

### Language evolution

- First released in 1985 Bjarne Stroustrup -> C with classes
- Language is tandardized by ISO C++98,03
- Modern C++: 11, 14, 17, 20, 23
- Upcoming C++26

### C comparison

C -> Procedural language

C++ -> Multi paradigms

Adds abstraction without sacrificing (too much) performance.

Core ideas:
- Encapsulation (classes)
- Resource management (RAII)
- Generic Programming (templates)
- Modern expressiveness (lambda, auto, etc...)

## First session function overloading, namespaces, references, constexpr


### Function overloading

In C++ you can have the same function names as long as the signature change (except for its return type)

```c++
int sum(
	int a,
	int b)
{
	return a + b;
}

double sum(
	double a,
	double b)
{
	return a + b;
}
```

#### exercice_1

### Namespace

In C++ you can use namespace to avoid naming collisions between different compilation unit, libraries, etc...
No need to prefix your functions

```c++
namespace my_lib {
    int sum(int a, int b);
}

int main()
{
    return my_lib::sum(1, 2);
}
```

You can nest namespaces into namespaces

```c++
namespace my_lib {
    namespace model
    {

    }
}

namespace my_lib::controllers {
    // C++17 compact style
}
```

#### exercice_2

### References

In C++ you can use reference to access/modify an upper variable inside a function as you would to with a pointer in C.
But it guarantees that the variable is valid.

```c++
void modify_variable(int& my_var)
{
    // No need to check for null pointer here
    my_var = 0;
}

int main()
{
    int var = 1;
    return modify_variable(var);
}
```

When you want to give a read only variable you can use const&

```c++
void print_variable(const int& my_var)
{
    printf("%d\r\n", my_var);
}

int main()
{
    int var = 1;
    return print_variable(var);
}
```

#### exercice_3

### Constexpr

In C++ you can have type safety and compile time evaluated variables with `constexpr` (c++11)

They replace C macros and bring type safety with.

```c++

// This will be evaluated during compilation and should not produce any symbole in the final application
constexpr int MY_VARIABLE = 5;

int main()
{
    printf("%d\r\n", MY_VARIABLE);
}

```

`constexpr` can also be used to create functions evaluated at compile time !

```c++

constexpr int sum(int a, int b)
{
    return a + b;
}

constexpr int MY_SUM_RESULT = sum(2, 3);

```

#### exercice_4