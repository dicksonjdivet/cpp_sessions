# C -> C++ Session

## Classes

### Classes in C++

How to declare a class or a struct in C++ (minimalistic example):

```c++
class MyClass {

};

struct MyStruct {
    // No need for typedef in C++
};
```

How to instanciate objects:

```c++
int main()
{
    MyClass object;
    MyStruct data;
    return 0;
}
```

### Difference between structs and classes in C++

All members in a C++ classes are by default private.

For a struct they are by default public.

```c++
class MyClass {
    int member; // private
}

struct MyStruct {
    int member; // public
}

int main()
{
    MyStruct data;
    data.member = 4; // OK

    MyClass object;
    object.member = 4; // Compilation error !
    return 0;
}
```

A struct in C++ can also have methods (function member), but semantically it is best to use them as data structure (no logic).

### Default constructor

In the previous examples the constructor was implicit (the compiler generates it automatically).

It is equivalent to the following declaration:

```c++
class MyClass {
    int member; // private
public: // public keyword so the following is considered available to the class consumer

    MyClass(){ // Default constructor doing nothing
        // member is not initialized here
    }
};

// Or

class MyClass {
    int member; // private
public:
    MyClass() = default; // C++ 11 same as MyClass(){}
};
```

How to instanciate members in the constructor ?

```c++
class MyClass {
    int member; // private
public: // public keyword so the following is considered available to the class consumer
    MyClass()
        : member(0){
        // Member will have value 0
    }
};

// It is also possible to initialize members like so:
class MyClass {
    int member{0};
    int member_2 = 0;
};

```

### Multiple constructors

In C++ you can have multiple constructors:

```c++
class MyClass {
    int member;
    bool other_member;
public:
    // Default constructor
    MyClass()
        : member(0), other_member(true){}

    // Second
    MyClass(int value)
        : member(value), other_member(false){}

    // Third
    MyClass(int value, bool second_value)
        : member(value), other_member(second_value){}
};

int main()
{
    MyClass object_1 {}; // First constructor
    MyClass object_2 {3}; // Second ...
    MyClass object_3 {6, false};
}
```

### Destructor

If you want special operations when an object is destroyed such as freeing memory, releasing resources, stopping a thread etc... You can do so in its destructor.

```c++
class MyClass {
    int* member;
public:
    MyClass(int value) : member((int*)malloc(sizeof(int)))
    {
        *member = value;
    }

    ~MyClass(){
        // releasing memory
        free(member);
    }
};

int main()
{
    int dummy;
    dummy = 5;
    {
        MyClass obj{dummy}; // Here we are calling malloc
    } // Reaching out of scope for obj, destructor is called
    
    return 0;
}
```

### RAII (Resource Acquisition Is Initialization)

With the concept of constructor being called at object creation and
destructor being called when object is being destroyed we just saw 
one of the most powerful C++ feature.
From it an important idiom of C++ is called RAII and allow programmers to take a resource in a scoped way, being sure that this resource will be given back when an object goes out of scope.

#### Exercice 1

Code the class `LockGuard` that will take a `std::mutex&` as constructor parameter, lock it in the constructor, unlock it in the destructor.

C++ mutex reference (https://en.cppreference.com/w/cpp/thread/mutex.html)

Exercice link: https://godbolt.org/z/vvv1ozd79

### Copy constructor/operator

By default C++ will generate both copy constructor and copy operator.
Unless one of the member is not copyable (we will see that later).

```c++
#include <cstdio>

class MyClass {
public:
    int member{3};
};

int main()
{
    MyClass obj1;

    obj1.member = 6;

    MyClass obj2{obj1}; // Copy constructor called here

    printf("%d\r\n", obj2.member); // Printing 6
    
    obj1.member = 9;

    obj2 = obj1; // Copy operator called here

    printf("%d\r\n", obj2.member); // Printing 9

    return 0;
}
```

This is okay when no pointers or so are used.
If we take back one of our example what could happen if we copy
an object of this class:

```c++
class MyClass {
    int* member;
public:
    MyClass(int value) : member((int*)malloc(sizeof(int)))
    {
        member = value;
    }

    ~MyClass(){
        // releasing memory
        free(member);
    }

    // Warning copy constructor and operator are available by default
};

int main()
{
	int dummy;
	dummy = 5;

	MyClass obj{dummy}; // Here we are calling malloc
	MyClass obj2{obj}; // Compile :')

	return 0;
}
```

Sometimes you will need to override copy constructor and operator.
You can do so with the following syntax:

```c++
class MyClass{
    int member;
public:
    // Copy constructor
    MyClass(const MyClass& other)
    {
        member = other.member;
    }

    // Copy operator
    MyClass& operator=(const MyClass& other)
    {
        if (this != &other){ // If we are not copying the same object
            member = other.member;
        }
        return *this; // Returning the reference on itself
    }
};
```

#### Exercice 2

In order to familiarize ourselves with the concept, code the following class which:

- In its default constructor, allocate on the heap (with a malloc) a counter and set it to `1`.
- It its destructor, decrement the counter, if equal to 0 free the counter.
- In its copy constructor, copy and increment the counter owned by the other object.
- In its copy operator, decrement its current counter and free the memory if equal to 0. Copy the other counter and increment it.
- Add printf on counter creation, destruction and increments to observe what's going on.

Link: https://godbolt.org/z/47Wdza6jr