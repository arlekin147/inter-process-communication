#include "AutoCloseable.hpp"

template<typename T>
AutoCloseable<T>::AutoCloseable(T resource_, dtor reset_):
resource(resource_),
reset(reset_)
{}


template<typename T>
AutoCloseable<T>::~AutoCloseable(){
    reset(resource);
}

template<typename T>
AutoCloseable<T>::operator T() const {
    return resource;
}

template<typename T>
AutoCloseable<T>::AutoCloseable(AutoCloseable && other){
    this->resource = std::move(other.resource);
    this->reset = std::move(other.reset);
    other.reset = [](T t){}; //other object will be destructed, but must do nothing with the resource
}

template<typename T>
AutoCloseable<T>& AutoCloseable<T>::operator=(AutoCloseable && other){
    if(this != &other){ 
        //fix faults of default constructor
        if(reset != nullptr){ 
            reset(this->resource);
        }
        this->resource = std::move(other.resource);
        this->reset = std::move(other.reset);
        other.reset = [](T t){}; //other object will be destructed, but must do nothing with the resource
    }
    return *this;
}