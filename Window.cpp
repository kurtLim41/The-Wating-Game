#include "Window.h"

Window::Window(){
    isOpen = true;
}

Window::~Window(){
}

bool Window::openWindow(){
    isOpen = true;
    return true;
}

bool Window::occupiedWindow(){
    isOpen = false;
    return false;
}

bool Window::getIsOpen(){
    return isOpen;
}