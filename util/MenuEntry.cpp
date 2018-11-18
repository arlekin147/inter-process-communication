#include "MenuEntry.hpp"

MenuEntry::MenuEntry(std::wstring text, Runnable* func):
text(text),
func(func)
{
}

MenuEntry::MenuEntry(const MenuEntry& other):
text(other.text),
func(other.func->cloneOnHeap())
{
}

MenuEntry::MenuEntry(MenuEntry&& other):
text(std::move(other.text)),
func(std::move(other.func))
{
}

std::wostream& operator<<(std::wostream& os, const MenuEntry& menuEntry){
    os << menuEntry.text;

    return os;
}

void MenuEntry::operator()(){
    (*func)();
}

