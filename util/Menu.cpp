#include "Menu.hpp"
#include "ProxyRunnable.hpp"
#include <exception>

Menu::Menu(std::wstring name):
name(name),
entries()
{
}

Menu::Menu(const Menu& other):
name(other.name),
entries(other.entries)
{
}

Menu::Menu(Menu&& other):
name(std::move(other.name)),
entries(std::move(other.entries))
{
}

void Menu::addEntry(std::wstring text, Runnable* func){
    this->entries.push_back(MenuEntry(text, func));
}

void Menu::executeEntry(size_t index){
    (entries.at(index)) ();
}

std::wostream& operator<<(std::wostream& os, const Menu& menu){
    os << menu.name << std::endl;
    for(size_t i = 0; i < menu.entries.size(); ++i){
        os << (i+1) << L". " << menu.entries.at(i) << std::endl;
    }

    return os;
}


void Menu::handleInput(std::wstring prompt = L"Please, input ur choise: "){
    std::wcout << prompt;

    std::wstring inputBuffer;
    std::wcin >> inputBuffer;

    size_t chosenIndex = std::stoi(inputBuffer);

    if(chosenIndex == 0){
        throw std::runtime_error("Wrong input: number can't be zero");
    }
    --chosenIndex; // We count from zero

    this->executeEntry(chosenIndex);
}

template<class T>
T* Menu::chooseOneFromVector(std::vector<T>& vec, std::wstring prompt, std::wstring (*toString)(const T*)){
    if(vec.size() == 0){
        throw std::runtime_error("Can't choose from empty vector.");
    }

    T* choosen;

    Menu menu(prompt);

    auto placer = [](std::pair<T** , T*> pp){
        (*pp.first) = pp.second;
    };
    
    for(T& elem: vec){
        menu.addEntry(
            toString(&elem),
            new ProxyRunnable<std::pair<T**, T*>>(placer, std::pair(&choosen, &elem)));
    }

    std::wcout << menu;
    menu.handleInput();

    return choosen;
}