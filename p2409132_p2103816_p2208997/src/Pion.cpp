#include "Pion.h"
#include <iostream>
using namespace std; 


Pion::Pion(int idf)
{
    i=0;    //dans la poule
    id = idf;
    est_sorti = false;
    est_arrive = false;
}

//destructeur a voir car il ne sert a rien sans sdl
Pion::~Pion()
{
    i=0;    //remet dans la poule
    est_sorti = false;
    est_arrive = false;    
}

unsigned char Pion::GetI() const
{
    return i;
}

int Pion::GetId() const
{
    return id;
}

bool Pion::GetEstSorti() const
{
    return est_sorti;
}

bool Pion::GetEstArrive() const 
{
    return est_arrive;
}

void Pion::SetI(int nb)   //verification du bon pion dans plateau
{
    i+=nb;
}

void Pion::SortirBase(){
    est_sorti=true; //Le pion est maintenant en jeu
    i=1;  //supposons que la position de depart soit 1
    cout<<"Pion "<<id <<" sorti de la base"<<endl;

}

void Pion::RetournerBase(){
    est_sorti=false;
    i=0;
}


