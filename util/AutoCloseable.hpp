#pragma once

template<typename T>
class AutoCloseable
{
private:
    typedef void (*dtor)(T);
	T resource;
	dtor reset;
public:
	AutoCloseable(T={}, dtor d=nullptr);
    AutoCloseable& operator=(T);

	virtual ~AutoCloseable();

	AutoCloseable(AutoCloseable const&) = delete;
    AutoCloseable& operator=(AutoCloseable const&) = delete;

	AutoCloseable(AutoCloseable &&);
    AutoCloseable& operator=(AutoCloseable &&);

	// implict cast to mimics T
	operator T() const;
};