#include "SharedMemory.hpp"
#include "../util/AutoCloseable.hpp"
#include <string>

#ifdef DEBUG
    #include <iostream>
#endif

#ifdef _WIN32
#define UNICODE
#include <windows.h>

struct SharedMemory::Impl {
    Impl(){}
    AutoCloseable<HANDLE> mapping;
    AutoCloseable<BYTE*> data;
};

SharedMemory::SharedMemory(std::wstring name, size_t size){
    this->name = name;
    this->size = size;
        
    impl = std::unique_ptr<Impl>(new Impl());

    LARGE_INTEGER li_size;
    li_size.QuadPart = size;
    impl->mapping = AutoCloseable<HANDLE>(
        size?(
            CreateFileMapping(
                INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE,
                li_size.HighPart, li_size.LowPart, name.c_str()
            )
        ):(
            OpenFileMapping(
                FILE_MAP_ALL_ACCESS, false, name.c_str()
            )
        ),
        [](HANDLE h){
            #ifdef DEBUG
                std::wcout << L"We'r closing mapping" << std::endl;
            #endif
            if(h){
                CloseHandle(h);
            }
        }
    );
    if(!impl->mapping){
        #ifdef DEBUG
           std::wcout << L"Failed to create mapping" << std::endl;
            std::wcout << L"Errcode:" << GetLastError() << std::endl;
        #endif
        throw std::bad_alloc();
    };

    impl->data = AutoCloseable<SharedMemory::BYTE*>(
        (BYTE*)MapViewOfFile(impl->mapping, FILE_MAP_ALL_ACCESS, 0, 0, size),
        [](BYTE* ptr){
            #ifdef DEBUG
                std::wcout << L"We'r closing data (view of file)" << std::endl;
            #endif
            if(ptr){
                UnmapViewOfFile(ptr);
            }
        }
    );
    if(!impl->data){
        #ifdef DEBUG
           std::wcout << L"Failed to create data (view of file)" << std::endl;
            std::wcout  << L"Errcode:" << GetLastError() << std::endl;
        #endif
        throw std::bad_alloc();
    }
}



void SharedMemory::read(SharedMemory::BYTE* storage, const size_t len, size_t offset) const{
    CopyMemory(storage, impl->data+offset, len);
}

void SharedMemory::write(SharedMemory::BYTE* storage, const size_t len, size_t offset) const{
    CopyMemory(impl->data+offset, storage, len);
}

BYTE* SharedMemory::getPtr() const{
    return impl->data;
}

#else //UNIX


#endif

size_t SharedMemory::getSize() const{
    return this->size;
}

std::wstring SharedMemory::getName() const{
    return this->name;
}


SharedMemory::SharedMemory(SharedMemory&& other):
{
    *this = other;
}

SharedMemory& SharedMemory::operator=(SharedMemory&& other){
    this->name = std::move(other.name);
    this->size = std::move(other.size);
    this->impl = std::move(other.impl);
    return *this;
}