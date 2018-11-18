#ifndef MENU_ENTRY_HPP
#define MENU_ENTRY_HPP

#include <iostream>
#include <string>
#include<memory>
#include "Runnable.hpp"

class MenuEntry{
public:
    MenuEntry(std::wstring, Runnable*);
    MenuEntry(const MenuEntry&);
    MenuEntry(MenuEntry&&);

    friend std::wostream& operator<<(std::wostream&, const MenuEntry&);
    void operator()();
private:
    std::unique_ptr<Runnable> func;
    std::wstring text;
};

#endif