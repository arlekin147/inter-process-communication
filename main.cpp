#include "shmem/SharedMemory.cpp"
#include <iostream>
#include "util/Menu.cpp"
#include "util/VoidRunnable.cpp"
#include "util/ProxyRunnable.cpp"
#include "util/MenuEntry.cpp"
#include "util/AutoCloseable.cpp"
#include <vector>
#include <exception>


std::vector<SharedMemory> shmems;
bool exitFlag;

void allocShmem();
void openShmem();
void readFromShmem();
void writeIntoShmem();
void freeShmem();
void Exit();
SharedMemory* chooseShm();

int main(){
    shmems = std::vector<SharedMemory>();

    Menu menu(L"Choose your action:");    
    menu.addEntry(
        L"Allocate shared memory area", 
        new VoidRunnable(allocShmem)
    );    
    menu.addEntry(
        L"Open shared memory area", 
        new VoidRunnable(openShmem)
    );    
    menu.addEntry(
        L"Write into shared memory",
        new VoidRunnable(writeIntoShmem)
    );
    menu.addEntry(
        L"Read from shared memory", 
        new VoidRunnable(readFromShmem)
    );    
    menu.addEntry(
        L"Free shared memory area", 
        new VoidRunnable(freeShmem)
    );
    menu.addEntry(
        L"Exit",
        new VoidRunnable(Exit)
    );

    exitFlag = 0;
    while(!exitFlag){
        system("cls");
        std::wcout << menu;
        try{
            menu.handleInput();
        }catch(std::exception& err){
            std::wcout << L"Error while choosing:" << err.what() << std::endl;
        }
        system("pause");
    }

    return 0;
}

void allocShmem(){
    std::wstring name;
    std::wcout << "Enter a name of mapping: ";
    std::wcin >> std::ws;
    std::getline(std::wcin, name);
    
    size_t size;
    std::wcout << "Enter a size of mapping u want to use: ";
    std::wcin >> size;

    try{
        shmems.push_back(SharedMemory(name, size+sizeof(size_t)));
    }catch(std::bad_alloc e){
        std::wcout << L"Failed to open shared memory area. Errcode: ";
        std::wcout << e.what() << std::endl;
        return;
    }
}

void openShmem(){
    std::wstring name;
    std::wcout << "Enter a name of mapping: ";
    std::wcin >> std::ws;
    std::getline(std::wcin, name);

    try{
        shmems.push_back(SharedMemory(name));
    }catch(std::bad_alloc e){
        std::wcout << L"Failed to open shared memory area. Errcode: ";
        std::wcout << e.what() << std::endl;
        return;
    }
}

void writeIntoShmem(){
    const SharedMemory* shmem = nullptr;
    shmem = chooseShm();
    
    if(shmem){
        std::wstring str;
        std::wcout << L"Input a string: ";
        std::wcin >> std::ws;
        std::getline(std::wcin, str);

        size_t size = (str.size()+1)*sizeof(wchar_t);
        *((size_t*) shmem->getPtr()) = size;
        
        shmem->write((BYTE*)str.c_str(), size, sizeof(size_t));

        std::wcout << L"Successufly writen!" << std::endl;
    }
}

void readFromShmem(){
    const SharedMemory* shmem = nullptr;
    shmem =  chooseShm();  
    if(shmem){
        size_t size = *((size_t*)shmem->getPtr());

        BYTE buffer[size];
        shmem->read((BYTE*)buffer, size, sizeof(size_t));
        std::wcout << L"Your data is:" << std::endl;
        std::wcout << std::wstring((wchar_t*) buffer) << std::endl;
    }
}


void freeShmem(){
    const SharedMemory* shmem = chooseShm();
    
    if(shmem){
        for(int i = 0; i < shmems.size(); ++i){
            if (&shmems[i] == shmem){
                shmems.erase(shmems.begin()+i);
                break;
            }
        }
    }
}

SharedMemory* chooseShm(){
    if(shmems.size() <= 0){
        std::wcout << L"There are no allocated/opened shared memory areas yet." << std::endl;
        return nullptr;
    }

    SharedMemory* shmem = nullptr;
    try{
        shmem = Menu::chooseOneFromVector<SharedMemory>(
            shmems, L"Please, choose shared memory area: ", 
            [](const SharedMemory* shmem){
                return shmem->getName();
            }
        );
    }catch(std::exception& err){
        std::wcout << L"Error while choosing:" << err.what() << std::endl;
    }

    return shmem;
}

void Exit(){
    exitFlag = true;
}