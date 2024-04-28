#include "Window.h"

Window::Window(){
    isOpen = true;
    int timeRemaining = 0;
    currentCustomer = NULL;
    idleTime = 0;
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

void Window::assignCustomer(Customer *customer , int serviceTime){
    currentCustomer = customer;
    timeRemaining = serviceTime;
    isOpen = false;
}

void Window::update(){
    if(!isOpen){
        timeRemaining--;
    }
    else if(timeRemaining <= 0){
        isOpen = true;
        currentCustomer = NULL;
    }

    if (!occupiedWindow()) {
        idleTime++; // Increment idle time if the window is not occupied
    }
}

Customer* Window::releaseCustomer() {
    if (isOpen) {
        return nullptr;  // Return null if no customer to release (window is not occupied)
    }

    Customer* tempCustomer = currentCustomer; // Store the reference to the customer
    currentCustomer = nullptr;  // Clear the current customer from the window
    isOpen = true;       // Set window status to not occupied
    timeRemaining = 0;          // Reset the remaining time for good measure

    return tempCustomer;  // Return the customer who was just released
}

int Window::getIdleTime() {
    return idleTime;
}

void Window::resetIdleTime() {
    idleTime = 0;
}

void Window::updateIdleTime(){
    idleTime++;
}
