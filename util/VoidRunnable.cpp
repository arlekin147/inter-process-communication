#include "VoidRunnable.hpp"

VoidRunnable::VoidRunnable(fptr ptr):
ptr(ptr)
{

}

void VoidRunnable::operator()(){
    ptr();
}

Runnable* VoidRunnable::cloneOnHeap(){
    return new VoidRunnable(ptr);
}