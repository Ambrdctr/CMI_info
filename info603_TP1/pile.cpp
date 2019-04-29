//
// Created by Ambroise Decouttere on 29/04/2019.
//
#include <stdlib.h>
#include "pile.h"


void pile::empty()
{
    if (taille > 0)
    {
        delete [] donnees;
        taille = 0;
    }
}


// On ajoute le nouvel élément a la fin du vecteur.
int pile::push(const int & element)
{
    int * temp = new int[taille + 1];

    // On vérifie si la taille max n'est pas atteinte
    if (taille < tailleLimit) {
        // On vérifie s’il manque de mémoire vive.
        if (temp == NULL)
            return 0;

        // On copie les données et on ajoute l’élément.
        for (int i = 0; i < taille; i++)
            temp[i] = donnees[i];
        temp[taille] = element;

        // On libère l’ancien tableau (s’il y en avait un).
        if (taille > 0)
            delete[] donnees;

        // On ajuste les données.
        donnees = temp;
        taille++;
        return 1;
    }
    return 0;
}


// On retire l'élément à la fin du vecteur.
int pile::pop(int & resultat)
{
    // On vérifie si la pile est vide.
    if (taille == 0)
        return 0;

    // On crée le nouveau tableau et on vérifie la mémoire.
    int * temp = new int[taille - 1];
    if (temp == NULL)
        return 0;

    // On extrait la donnée et on copie le reste.
    resultat = donnees[--taille];
    for (int i = 0; i < taille; i++)
        temp[i] = donnees[i];

    // On efface l’ancien tableau et on ajuste les données.
    delete [] donnees;
    donnees = temp;
    return 1;
}