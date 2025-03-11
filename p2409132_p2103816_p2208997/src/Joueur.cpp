#include <iostream>
#include "Joueur.h"
using namespace std;

class Joueur
{
	public:
		//Color color;
		int id;
		int nbpionarrives;
		
		Joueur::Joueur();
		Joueur()
		{
			id=0;
			nbpionarrives=0;
		}
		Joueur::Joueur(int ident)
		{
			id=ident;
			nbpionarrives=0;
		}
		
		
		
		void getnbpionarrive()
		{
			return nbpionarrives;
		}
		~Joueur::Joueur();
};	
