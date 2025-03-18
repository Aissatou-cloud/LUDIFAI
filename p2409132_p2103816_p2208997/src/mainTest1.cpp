#include <iostream>
#include "Joueur.h"
#include "Pion.h"
#include "De.h"
#include "Color.h"

using namespace std;

int main() {
    //  Test de la classe Color
    cout << "==== TEST COLOR ====" << endl;
    Color c;
    c.setColor(255, 0, 0); // Rouge
    cout << "Couleur définie : R=" << (int)c.getColor().r 
         << ", V=" << (int)c.getColor().v 
         << ", B=" << (int)c.getColor().b << endl;

    // Test de la classe De (lancer de dé)
    cout << "\n==== TEST DE ====" << endl;
    De de;
    for (int i = 0; i < 5; i++) {
        cout << "Lancer " << i+1 << " : " << de.GetVal() << endl;
    }

    //  Test de la classe Pion
    cout << "\n==== TEST PION ====" << endl;
    Pion pion1(1);
    cout << "Pion créé avec ID " << pion1.GetId() 
         << ", Position : " << (int)pion1.GetI() << endl;

    pion1.SeDeplace(6); // Déplacement de 6 cases
    cout << "Après déplacement : Position = " << (int)pion1.GetI() << endl;

    // Test de la classe Joueur
    cout << "\n==== TEST JOUEUR ====" << endl;
    Joueur joueur1(1, 0, 255, 0); // Joueur vert
    cout << "Joueur " << joueur1.getId() 
         << " a la couleur R=" << (int)joueur1.getCouleur().r 
         << ", V=" << (int)joueur1.getCouleur().v 
         << ", B=" << (int)joueur1.getCouleur().b << endl;

    return 0;
}
