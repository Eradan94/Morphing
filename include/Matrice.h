/*!
 * \file Matrice.h
 * \brief Gère la construction et l'utilisation de la structure Matrice.
 * 
 * -# Structure Matrice : permet de représenter une matrice.
 * \n Contient un tableau d'entiers de rang taille.
*/

#ifndef __MATRICE__
#define __MATRICE__

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int ** val;
	size_t taille;
} Matrice;

/*!
 * \brief Alloue une matrice.
 * 
 * \param size : taille de la matrice.
 * 
 * Alloue la mémoire nécessaire pour le tableau à deux dimensions de taille size.
 * 
 * \return Renvoie une matrice.
 */
Matrice alloue_matrice(int size);

/*!
 * \brief Calcule la sous matrice de m1 selon une coordonnée de la matrice.
 * 
 * \param m1 : matrice mère.
 * \param m2 : sous matrice à calculer, de taille n-1.
 * \param x : abscisse du point.
 * \param y : ordonnée du point.
 * 
 * Stocke dans m2, le contenu de m1 après avoir retiré la x-ième ligne et y-ième colonne.
 * Le contenu de m2 est écrasé.
 * m1 et m2 doivent être allouées.
 */
void sous_matrice(Matrice * m1, Matrice * m2, int x, int y);

/*!
 * \brief Calcule la sous matrice de m1 selon une coordonnée de la matrice.
 * 
 * \param m : matrice à libérer.
 * 
 * Désalloue l'espace mémoire utilisée par le tableau à deux dimensions.
 */
void libere_matrice(Matrice * m);

/*!
 * \brief Affiche la matrice dans la console.
 * 
 * \param m : matrice à afficher.
 * 
 * Désalloue l'espace mémoire utilisée par le tableau à deux dimensions.
 */
void affiche_matrice(Matrice * m);

/*!
 * \brief Calcule le déterminant de la matrice.
 * 
 * \param m : matrice à calculer.
 * 
 * Calcule les sous matrices de m selon la premiere ligne et appelle récursivement determinant sur les sous matrices.
 * Libère la matrice une fois le calcul fini
 * 
 * \return Renvoie le résultat du déterminant.
 */
long determinant(Matrice * m);

#endif
