#define DEBUG

#include <iostream>
#include "util/AutoCloseable.cpp"
#include "shmem/SharedMemory.cpp"

int main(){
    SharedMemory shm2(L"myshm");

    std::wcout << (wchar_t*) shm2.getPtr() << std::endl;

    system("pause");

    return 0;
}