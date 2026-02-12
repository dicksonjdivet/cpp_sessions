# C -> C++ Session

## Functions as variables

In this session we are going to look at the different ways to create variables that are callables as functions.

They are often useful for callbacks.

We are going to look at how it is done in C and the different ways to achieve it in C++.

### The old way, function pointers and void* context

In C the only way to create a callable variable is to create a function pointer.

``` c++
#include <stdio.h>

int add(int a, int b)
{
    return a + b;
}

int main() {
  
    // Declare a function pointer that matches
  	// the signature of add() function
    int (*fptr)(int, int);

    // Assign to add()
    fptr = &add;

    // Call the function via ptr
    printf("%d", fptr(10, 5));
    return 0;
}
```

When creating callbacks we often want to work on custom data. It is achievable thanks to `void*`. But we are dependent on the callback design (if `void*` parameter is missing we can't modify an external variable except for global variables).

``` c++
struct Player {
    int x;
    int y;
};

void update_player(void* data)
{
    Player* p = (Player*) data;
    p->x++;
    p->y++;
}

int main() {
    void (*update)(void*);

    Player p;

    p.x = 0;
    p.y = 0;

    while(true)
    {
        update(&player);
    }
}
```

The main drawback is the type safety.

Direct casts from `void*` could be problematic if we change the data structure given to `update` function here.

### C++ Functors

In C++ it is possible to create objects that can be callable, they are named functors.

``` c++
class Adder {
public:
    Adder(int initial_value) : m_initial_value(initial_value){}

    // Declare callable operator
    int operator()(int value)
    {
        return m_initial_value + value;
    }

private:
    int m_initial_value;
}

int main()
{
    // Construct Adder with initial value of 5
    Adder addFive(5);

    // Call addFive with 10, 5 + 10 = 15
    printf("%d\n", addFive(10));

    return 0;
}
```

One of the perks of using functors is that they have an internal context (here `m_initial_value`).

Another example used in LoRaConnector:

``` c++

// .h
// ...
namespace use_cases {

/// \brief Use case to add a data logger.
class AddDataLogger {
public:
	/// \brief Constructor.
	/// \param dataLoggerRepository The data logger repository to add the
	/// data logger to.
	AddDataLogger(domain::IDataLoggerRepository& dataLoggerRepository);

	/// \brief Adds the given data logger to the repository.
	void operator()(domain::DataLogger device);

private:
	domain::IDataLoggerRepository& mDataLoggerRepository;
};

}

// .cpp
// ...
namespace use_cases {

AddDataLogger::AddDataLogger(domain::IDataLoggerRepository& dataLoggerRepository)
	: mDataLoggerRepository(dataLoggerRepository)
{
}

void AddDataLogger::operator()(domain::DataLogger device)
{
	LOG_DEBUG(
		"[%s] Adding data logger to repository\r\n",
		domain::device_serial_number::toString(device.serialNumber).c_str());

	bool deviceAdded = mDataLoggerRepository.addDataLogger(device);

	if (!deviceAdded) {
		LOG_ERROR(
			"[%s] Failed to add device to repository\r\n",
			domain::device_serial_number::toString(device.serialNumber).c_str());
		return;
	}

	LOG_TRACE(
		"[%s] Added device to repository\r\n",
		domain::device_serial_number::toString(device.serialNumber).c_str());

	mDataLoggerRepository.save();
}

}

// ...
// Very limited example
int main()
{
    AddDataLogger add_data_logger(repository);

    domain::DataLogger data_logger;

    // ...
    // Calling add_data_logger as it was a regular function.
    // But we injected a repository in constructor.
    add_data_logger(data_logger);
}
```

### Lambdas (since C++11)

Since modern C++ we have the choice of creating lambdas.
In C++ they are anonymous inline functions.

``` c++
int main() {
    // variable 'add' takes lambda expression
    auto add = [](int x, int y) {
        return x + y;
    };

    printf("%d\n", add(3, 8));

    return 0;
}
```

The brackets `[]` is called lambda's closures.
It is meant to capture context variables.
We are going to see the different type of captures:

#### Capture by copy

```c++
int main()
{
    int value = 1;

    // If we give the name of the value variable directly.
    // Then value is copied into the lambda's closures
    // As it was an independent member of type int.
    auto add = [value](int x) {
        return value + x;
    };

    value++; // Here we change value

    printf("%d\n", add(3)); // return 4 (because value was copied)

    return 0;
}
```

#### Capture by reference

```c++
int main()
{
    int value = 1;

    // If we prepend `&` to the name of the variable name.
    // Then value is a reference in the lambda's closures
    auto add = [&value](int x) {
        return value + x;
    };

    value++; // Here we change value

    printf("%d\n", add(3)); // return 5 (because value was taken as a reference)

    return 0;
}
```

#### Capture all variables by copy

```c++
int main()
{
    int value = 1;
    float another_value = 2.f;
    const char* message = "Hello world !\n";
    // If we just set `=` then we will capture all context variables
    auto display_message = [=](){
        printf("%s: %d, %f\n", message, value, another_value);
    };

    display_message();

    return 0;
}
```

#### Capture all variables by reference

```c++
int main()
{
    int value;
    float another_value;
    char buffer[32];

    // If we just set `&` then we will capture all context variables
    auto init = [&](){
        value = 0;
        another_value = 0.f;
        memset(buffer, 0, sizeof(buffer));
    };

    init();

    return 0;
}

```

#### Using member variables of a class

```c++

class Engine {
public:

    void run() {
        // Lambda treating events
        // Might better do a private method instead
        // But it is to illustrate lambdas with members
        // Without this, it is not possible to use members
        auto process_events = [this](){
            while(m_events.size()){
                // Take first element of the queue
                auto& event = m_events.front();
                // If quit then set variable to true
                if(event.type() == EventQuit){
                    m_quit = true;
                }
                // Remove first element
                m_events.pop();
            }
        }
        // Event loop
        while (!m_quit)
        {
            process_events();
        }
    }

private:
    bool m_quit{false};
    std::queue<Event> m_events;
};

```
In C++, lambdas are compatible with function pointers as long as they don't capture any variables

``` c++
void display(int value, void(*)(int value) display_callback)
{
    display_callback(value);
}

int main()
{
    int dummy = 1;
    // Here the update function will call the lambda expression
    // We can directly pass the lambda without having to write a separate function
    update(dummy, [](int value){
        printf("Displaying: %d\n", value);
    });

    update(dummy, [](int value){
        printf("Another display: %d\n", value);
    })
}

```

### std::function as function pointer replacement.

With C++ when you give a function as parameter for a callback you have basically the choice between old C function pointers or `std::function`.

`std::function` has the advantage of working with lambdas, functors and any callable objects embedding internal data.

```c++

// Include functional in order to use std::function
#include <functional>
#include <stdio.h>

// std::function is a template
// inside its template parameter you should use a function signature
// Here the function is taking one argument of type int and returning a int as a result.
void use_callback(std::function<int(int)> add_callback)
{
	int value = 5;

	int result = add_callback(value);

	printf("Result is %d\n", result);
}

class Functor {
public:
	Functor(int initial_value)
		: m_initial_value(initial_value)
	{
	}

	int operator()(int other_value)
	{
		return m_initial_value + other_value;
	}

private:
	int m_initial_value;
};

int addTen(int value)
{
	return 10 + value;
}

int main()
{
	Functor addFive(5);

	// Give a functor as parameter
	use_callback(addFive);

	int my_value = 2;

	// Taking my_value by copy
	// Give a lambda as parameter
	use_callback([my_value](int other_value) { return my_value + other_value; });

	// Giving a function directly as parameter
	use_callback(addTen);

	int (*addTenPtr)(int) = addTen;

	// Giving a function pointer as parameter
	use_callback(addTenPtr);

	return 0;
}

```

You see that std::function is really powerful in C++, and why you should use it rather than C function pointers.
One of its drawback would be to be a bit heavier in term of memory footprint than C because it has to embed all variables.

You should also be careful when giving arguments by reference.
Sometimes it is possible for the given objects to be already destroyed. Their usage would lead to undefined behaviors most commonly leading to crashes.

```c++

int main()
{
    std::function<void()> update_value;
    {
        int value = 0;
        // Copy by reference
        update_value = [&value](){
            value++; 
        };
    }

    update_value(); // UB: value is not valid anymore

    return 0;
}

```

### Exercice 1:

Now that you are more familiar with the different ways to create callable variables in C++, try to implement the observer pattern:

- Create a class `Observable` that has a method `subscribe` to add observers and a method `notify` to call all observers.
Note that no parameter is given to the observers in this exercice.

- Create a class `Observer` that is a functor that will be called when the observable is notified.

- Create a function `dummy_observer` that will be called when the observable is notified.

- Create a main function where you create an observable and some observers, subscribe them to the observable and notify them.

### Exercice 2: (hard)

Now try to use variadic templates to create an observable that accept observers with different signatures. They should be notified with the same parameters as the ones they are expecting.