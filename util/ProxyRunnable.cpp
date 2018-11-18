#include "ProxyRunnable.hpp"

template <class Arg>
ProxyRunnable<Arg>::ProxyRunnable(const ProxyRunnable<Arg>& other):
func(other.func),
arg(other.arg)
{
}

template <class Arg>
ProxyRunnable<Arg>::ProxyRunnable(func_target<Arg> func, Arg arg):
func(func),
arg(arg)
{

}

template <class Arg>
void ProxyRunnable<Arg>::operator()(){
    func(arg);
}

template <class Arg>
Runnable* ProxyRunnable<Arg>::cloneOnHeap(){
    return new ProxyRunnable(func, arg);
}