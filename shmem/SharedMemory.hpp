#pragma once

#include <string>
#include <memory>

class SharedMemory{
private:
	struct Impl; // defined in SharedMemory.cpp platform specific
	std::unique_ptr<Impl> impl;
    SharedMemory(SharedMemory&)  = delete;
    SharedMemory& operator=(SharedMemory&) = delete;
    std::wstring name;
    size_t size;
public:

    typedef unsigned char BYTE;
    SharedMemory(std::wstring name, size_t size=0);
    SharedMemory(SharedMemory&&);
    SharedMemory& operator=(SharedMemory&&);
    virtual ~SharedMemory() {};

    size_t getSize() const;
    void write(BYTE* data, const size_t len, size_t offset = 0) const;
    void read(BYTE* const storage, const size_t len, size_t offset = 0) const;
    std::wstring getName() const;
    BYTE* getPtr() const; //Unsafe!!
};