#include "Color.h"
#include <isotream>
using namespace std;
    
    Color::Color(): r(0), v(0), b(0){};

    Color::~Color(){}

    void Color::setColor(unsigned char nr, unsigned char nv, unsigned char nb):r(nr), v(nv), b(nb) {}

    const Color& Color::getColor(){
        return *this; //Renvoie une reference sur l'objet courant
        
    }