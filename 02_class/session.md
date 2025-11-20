# C -> C++ Session

## Classes

### Classes in C++

How to declare a class or a struct in C++ (minimalistic example):

```c++
struct MyStruct {
    // No need for typedef in C++
};

class MyClass {

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

### Difference struct and classes in C++

All members in a C++ classes are by default private, for a struct they are by default public.

```c++
struct MyStruct {
    int member; // public
}

class MyClass {
    int member; // private
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
    MyClass() : member(0), other_member(true){}
    MyClass(int value) : member(value), other_member(false){}
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