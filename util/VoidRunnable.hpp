#ifndef VOID_RUNNABLE_HPP
#define VOID_RUNNABLE_HPP

#include "Runnable.hpp"


class VoidRunnable: public Runnable{
    private:
        fptr ptr;
    public: 
        VoidRunnable(fptr);

        virtual void operator()();

        virtual Runnable* cloneOnHeap();
};

#endif