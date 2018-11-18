#ifndef RUNNABLE_HPP
#define RUNNABLE_HPP

typedef void (*fptr)();

class Runnable{
public:
    virtual void operator()() = 0;
    virtual Runnable* cloneOnHeap() = 0;
};

#endif