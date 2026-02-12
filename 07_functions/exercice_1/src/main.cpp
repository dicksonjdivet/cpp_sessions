#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <exception>

#include <vector>
#include <functional>

int main()
{
    Observer observer;

    Observable observable;

    observable.subscribe(observer);

    int value = 0;
    observable.subscribe([&value](){
        value++;
        printf("Lambda is notified as well: %d!\n", value);
    });

    observable.subscribe(dummy_observer);

    // All three observers should be notified !
    observable.notify();

    return 0;
}