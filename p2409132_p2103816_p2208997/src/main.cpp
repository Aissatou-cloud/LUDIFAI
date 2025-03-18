#include <iostream>
#include "Color.h"
#include "Joueur.h"

using namespace std;

int main() 
{
    int id = 42;
    Joueur j1(id);
    cout << "Joueur créé avec ID " << id << ". Nombre de pions arrivés: " << j1.getNbpionArrives() << endl;
    cout << "Le nombre de pions arrivés du joueur1 est: " << j1.getNbpionArrives() << endl;
    j1.getNbpionArrives();
    return 0;
}
