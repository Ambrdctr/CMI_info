//
// Created by Ambroise Decouttere on 29/04/2019.
//
#include <stdlib.h>

#ifndef INFO603_TP1_PILE_H
#define INFO603_TP1_PILE_H


class pile {

    public :
        // CONSTRUCTEURS
        pile(int tailleMax) { donnees = NULL, taille = 0; tailleLimit = tailleMax; }


        // DESTRUCTEUR
        inline ~pile()   { empty();}


        // MÉTHODES DE MODIFICATION
        int push(const int &);
        // Ajoute un élément dans la pile. Retourne 1 en cas de
        // succès, 0 sinon (manque de mémoire).

        int pop(int &);
        // Retire un élément de la pile. Retourne 1 en cas de
        // succès et la valeur en paramètre, 0 sinon (la pile
        // était vide).

        void empty();
        // Retire tous les éléments de la pile.

        void tailleMax();
        // modifie la taille max de la pile


        // MÉTHODE DE CONSULTATION
        inline int get_size() const { return taille;}
        // Retourne le nombre d’éléments de la pile.


    private :

        int * donnees;
        int taille;
        int tailleLimit;

        // On empêche de copier une pile!
        pile(const pile &);
        pile& operator = (const pile &);
};


#endif //INFO603_TP1_PILE_H
