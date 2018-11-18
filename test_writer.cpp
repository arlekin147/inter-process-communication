#define DEBUG

#include <iostream>
#include "util/AutoCloseable.cpp"
#include "shmem/SharedMemory.cpp"

int main(){

    std::wstring str = L"My test string :)";
    SharedMemory shm(L"myshm", 500);
    shm.write((BYTE*)str.c_str(), str.size()*sizeof(wchar_t));

    system("pause");

    return 0;
}