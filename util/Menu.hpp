#ifndef MENU_HPP
#define MENU_HPP

#include <iostream> 
#include <string>
#include <vector>
#include "MenuEntry.hpp"

class Menu{
public:
    Menu(std::wstring);
    Menu(const Menu&);
    Menu(Menu&&);

    void addEntry(std::wstring, Runnable*);
    void executeEntry(size_t);
    void handleInput(std::wstring);
    friend std::wostream& operator<<(std::wostream&, const Menu&);

    template<class T>
    static T* chooseOneFromVector(std::vector<T>&, std::wstring, std::wstring (*toString)(const T*));
 
private:   
    std::wstring name;
    std::vector<MenuEntry> entries;
};

#endif