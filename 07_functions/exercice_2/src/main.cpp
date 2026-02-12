#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <exception>
#include <iostream>

#include <vector>
#include <functional>

int main()
{
    Observer<int, float> observer;

    Observable<int, float> observable;

    observable.subscribe(observer);

    observable.subscribe([](int param_a, float param_b) {
        printf("Lambda is notified as well: %d, %f!\n", param_a, param_b);
    });

    observable.subscribe(dummy_observer);

    // All three observers should be notified !
    observable.notify(3, 5.f);

    return 0;
}