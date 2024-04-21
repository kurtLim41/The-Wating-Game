#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
using namespace std;

class Window{
    private:
        bool isOpen;

    public:
        Window();
        ~Window();

        //core functions 
        bool openWindow();
        bool occupiedWindow(); 
        

        //aux functions 
        bool getIsOpen();  
};
#endif 
