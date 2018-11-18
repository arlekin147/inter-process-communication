#ifndef PROXY_RUNNABLE_HPP
#define PROXY_RUNNABLE_HPP

#include "Runnable.hpp"

template <class Arg>
using func_target = void (*)(Arg); 

template <class Arg>
class ProxyRunnable: public Runnable{
private:
    func_target<Arg> func;
    Arg arg;

    ProxyRunnable(const ProxyRunnable<Arg>&);
public:

    ProxyRunnable(func_target<Arg>, Arg);

    virtual void operator()();

    virtual Runnable* cloneOnHeap();
};

#endif