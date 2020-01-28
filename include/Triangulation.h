/*!
 * \file Triangulation.h
 * \brief Gère la triangulation de delaunay.
 * 
 */

#ifndef __TRIANGULATION__
#define __TRIANGULATION__

#include <stdio.h>
#include <stdlib.h>

#include "Triangle.h"

/*!
 * \brief Initialise la matrice pour la triangulation de delaunay.
 * 
 * \param m : matrice à initialiser.
 * \param t : triangle que l'on veut tester.
 * \param d : point que l'on veut tester.
 * 
 * Initialise la matrice 3x3 selon les coordonnées de t et d.
 */
void init_matrice_delaunay(Matrice * m, Triangle t, Point d);

/*!
 * \brief Teste si le triangle t est delaunay avec chacun de ses voisins.
 * 
 * \param t : cellule du triangle à tester.
 * 
 * Pour chaque voisin de t :
 * - on détermine le point qui n'est pas dans t.
 * - on vérifie si t est delaunay avec ce point
 * 
 * \return Renvoie 1 si est delaunay, une valeur négative sinon, en fonction du coté qui n'est pas delaunay :
 * -1 pour le coté AB
 * -2 pour le coté BC
 * -3 pour le coté AC
 */
int triangle_est_delaunay(CelTriangle* t);

/*!
 * \brief Teste si t est delaunay.
 * 
 * \param t : cellule du triangle à tester.
 * \param p : point à tester.
 * 
 * Initialise une matrice selon t et p et calcule le déterminant.
 * 
 * \return Renvoie 1 si le determinant est positif (triangle t n'est pas delaunay), sinon le triangle estdelaunay.
 */
int det_delaunay(Triangle t, Point p);

/*!
 * \brief Effectue la triangulation.
 * 
 * \param l : liste de triangles.
 * \param t : cellule du triangle ou l'on a cliqué.
 * \param p : point où l'on a cliqué.
 * 
 * Divise en trois triangles, le triangle t.
 * Ajoute les trois nouveaux triangles dans la liste.
 * Retire la cellule de t de la liste.
 * Mise à jour des voisins.
 * Flip les nouveaux triangles si nécessaire.
 * Suppression de l'ancien triangle.
 * 
 */
void triangule(ListeTriangle* l, CelTriangle* t, CelPoint* p);

/*!
 * \brief Flip la diagonale des deux triangles t1 et t2.
 * 
 * \param t1 : cellule du premier triangle.
 * \param t2 : cellule du deuxième triangle.
 * \param cote : quel est le coté de t1 à flipper : 1 pour AB, 2 pour BC et 3 pour AC.
 * 
 * Selon cote et determine_point on garde en mémoire 2 voisins de t1 et t2.
 * Toujours selon cote, on change les coordonnées des sommets de t1 et t2.
 * On reinitialise les voisins de t1 et t2 pour éviter des conflits puis on met à jour leurs voisins.
 * On appelle flip sur le triangle paire de t1 et de t2 pour affectuer les mêmes flip à gauche et à droite.
 * On appelle flip récursivement tant que t1 et t2 ne sont pas delaunay.
 */
void flip(CelTriangle * t1, CelTriangle * t2, int cote);

#endif
