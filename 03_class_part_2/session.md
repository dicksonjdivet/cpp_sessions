# C -> C++ Session

## Class 2nd part

### Methods

A function in a class is called a method.
A method is generally declared so we can interact with the object.
For example, moving an instance of a `Player` class with a method `move(int x, int y)`.

A method is declared inside the class scope:

```c++
class Position2D {
public:
    // This is the translate method of class Position2D
    // Executing a geometric translation
    void translate(int x, int y){
        m_x += x;
        m_y += y;
    }

private:
    // x and y position
    int m_x {0};
    int m_y {0};
};

int main()
{
    Position2D pos;

    // Method call
    pos.translate(3, 5);

    return 0;
}
```

Methods are always declared in the class scope but can be defined elsewhere like so:

```c++
class Position2D {
public:
    // Method declaration
    void translate(int x, int y);

private:
    int m_x {0};
    int m_y {0};
};

// Method definition (most of the time in cpp file)
void Position2D::translate(int x, int y)
{
    m_x += x;
    m_y += y;
}
```

### Private methods
Sometimes you want to hide some methods to the class user.
This is part of encapsulation, meaning what you want to expose to the user vs what you want to hide.
Those methods are called private methods.
Private methods are only callable from the class itself.

```c++
class Position2D {
public:
    Position2D(int x, int y)
    : m_x(x), m_y(y) {
        clampCoordinates();
    }
    // This is the translate method of class Position2D
    // Executing a geometric translation
    void translate(int x, int y){
        m_x += x;
        m_y += y;
        clampCoordinates();
    }

private:
    // Private method restraining the x and y parameters to go out of bound
    void clampCoordinates()
    {
        const int MIN = -100.0;
        const int MAX =  100.0;
        if(m_x > MAX) m_x = MAX;
        if(m_x < MIN) m_x = MIN;
        if(m_y > MAX) m_y = MAX;
        if(m_y < MIN) m_y = MIN;
    }
    // x and y position
    int m_x {0};
    int m_y {0};
};

int main()
{
    Position2D pos;

    // Method call
    pos.clampCoordinates(); // Compilation failure !

    return 0;
}
```

### Static methods
Sometimes you will need to call methods on a class directly and not on an object.
These methods are called static methods.
Maybe one of the most encountered example of static method is the singleton implementation:

```c++
class Singleton {
public:
    // If you add static before a method it signals that the method
    // does not need an object to be called.
    static Singleton& getInstance() {
        // Our static method can call the private method below because we are the designers
        // of Singleton class

        // Beware static below has the same meaning than in C.
        // We are declaring a global variable below.
        static Singleton instance;
        return instance;
    }

private:
    // Here we prevent an external consumer to use the default constructor
    Singleton() = default;
};

int main()
{
    // Here we call our static method with the class name followed by "::"
    Singleton& instance = Singleton::getInstance();

    Singleton myInstance; // Compilation failure (because of private constructor)!
}
```

### Const qualifier

It is possible to set a method as "read-only" when adding the `const` qualifier.

```c++
class Position2D
{
public:
    // Here we are just accessing m_x member and not modifying it.
    // Thus we can mark the method const.
    int getX() const {
        return m_x;
    }

    // This kind of method member is called "getter" method.
    // It is used to access a class member
    int getY() const {
        return m_y;
    }

private:
    int m_x{0};
    int m_y{0};
}

// Here we pass "position" as a const object so we can only
// access its const methods
void print(const Position2D& position)
{
    printf("Position2D{ x: \"%d\", y: \"%d\"})\n",
        position.getX(),
        position.getY());
}
```

The const qualifier has two main purposes.
- The first one is to inform the class user that this method does not modify any of the class member (i.e. the method is "read-only").
- The second is to be able to use those methods when the object is given as const.

## Inheritance

One of the main concept introduced in C++ regarding C is the possibility for a class to inherit from another.
It means that we can reuse some of the functionalities of the overridden  class. With inheritance it is possible to share members, overwrite some already existing methods, avoid code repetition, etc...
Inheritance brings genericity.

### How to inherit from another class

```c++
class Parent {
public:
    Parent(int value) : m_value(value) {}
    
    void parentMethod()
    {
        printf("This is the parent method !\n");
    }

private:
    int m_value;
};

// To inherit we declare our class Child and use ":" followed by the access specifier "public/protected/private"
class Child : public Parent {
public:
    // Child constructor using Parent constructor and injecting its own parameter
    Child() : Parent(10){}

    void childMethod() {
        printf("This is the child method !\n");
    }
};

int main()
{
    Child child;

    child.parentMethod();
    child.childMethod(); // Both methods are allowed because Child class inherits from Parent class with public access
}
```

Here is the table for access specifier permissions:

| Access Specifier | Parent Class Members | Child Class Members | User access |
|-------------------|----------------------|---------------------|-------------|
| public            | Accessible           | Accessible          | Accessible  |
| protected         | Accessible           | Accessible          | Not Accessible |
| private           | Accessible           | Not Accessible      | Not Accessible |

### Protected methods

A protected method is a method that is solely accessible from inheriting classes

```c++
class Vehicle {
protected:
    void log(const char* message) {
        printf("[Vehicle]: %s\n", message);
    }
}

class Car : public Vehicle {
public:
    void start(){
        log("vroum!");
    }
};

class Bus : public Vehicle {
public:
    void start(){
        log("VROUM!");
    }
};
```

### Virtual methods

A virtual method is a method that can be overridden by inheriting classes.

```c++
class Animal
{
public:
    virtual void doSound() const{
        printf("?\n");
    }
};

class Dog : public Animal {
public:
    // override was added in c++11
    // highlighting the class designer to override a given method
    void doSound() const override {
        printf("WOAF!\n");
    }
};

class Cat : public Animal {
public:
    void doSound() const override {
        printf("MEOW!\n");
    }
};

int main() {
    Animal animal;
    Dog dog;
    Cat cat;

    animal.doSound();
    dog.doSound();
    cat.doSound();
}
```

### Pure virtual methods

A pure virtual method is a method that has no definition.
Meaning that inheriting classes are forced to implement them otherwise they cannot be instanciated.

```c++
class Animal
{
public:
    // We declare a pure virtual method with "= 0"
    virtual void doSound() const = 0;
};

class Dog : public Animal {
public:
    // override was added in c++11
    // highlighting the class designer to override a given method
    void doSound() const override {
        printf("WOAF!\n");
    }
};

class Cat : public Animal {
public:
    void doSound() const override {
        printf("MEOW!\n");
    }
};

int main() {
    // Animal animal; Compilation error if uncommented (animal has doSound() not implemented)
    Dog dog;
    Cat cat;

    dog.doSound();
    cat.doSound();
}
```

Classes containing pure virtual methods are called abstract classes.

#### Exercice

- Create 5 classes `Size2D`, `Position2D`, `Entity`, `Player`, `Enemy`.

- `Size2D` and `Position2D` should have their members private.
- An entity should have a size, a position and a life.
- Both `Player` and `Enemy` should inherit from `Entity`
- An entity has a way to reset its life.
- A player has an initial life of `3`, and an enemy has `10`
- Both classes are able to move its position by a (x, y) translation
- A player has an hitbox being 2 times smaller than its size.
- An enemy has an hitbox being identical to its size.
- Add a `isHit` method that should tell whether an entity was hit or not
