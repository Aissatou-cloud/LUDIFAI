#ifndef PION_H
#define PION_H

/**
* @class Pion
* @brief Un pion d'un joueur qui se deplace le long d'un chemin
*/

class Pion{
    private: 
        unsigned char i;    ///position du pion dans le chemin
        int id;             ///identifiant 
        bool est_sorti;     ///si pion est sorti de la poule
        bool est_arrive;    ///si pion est arrive a case d'arrivée
        float x;
        float y;

    public: 
        /**
        * @brief Constructeur qui initialise un pion dans la poule
        */
        Pion(int idf);

        /**
        * @brief Destructeur qui vide un pion 
        */
        ~Pion();
        
        /**
        * @brief Retourne position du pion 
        */        
        unsigned char GetI() const;

        /**
        * @brief Retourne identifiant du pion
        */
        int GetId() const;

        /**
        * @brief Retourne si le pion est sorti de sa poule ou non        
        */
        bool GetEstSorti() const;

        /**
        * @brief Retourne si le pion est arrivé a la case d'arrivée ou non        
        */
        bool GetEstArrive() const;

        /**
        * @brief Deplace le pion en fonction du nombre du dé lancé
        * @param nb nombre de place à incrémenter a la position du pion 
        */
        void SetI(int nb);
        void SortirBase(); // sortir le pion
        void RetournerBase(); // retourner à la base

        /**
		* @brief remplir coordonnée des pions dans la poule 
		* @param x coordonnée x du pion
		* @param y coordonée y du pion 
		*/
		void CoordonneesPionPoule(float x, float y);

		/**
		* @brief Retourne les coordonnées x d'un pion
		 */
		float GetCoordoneeXPoule ();	
		
		/**
		* @brief Retourne les coordonnées y d'un pion
		 */
		 float GetCoordoneeYPoule ();
};

#endif