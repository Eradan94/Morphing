/*!
 * \file Point.h
 * \brief Gère la construction et l'utilisation de la structure Point.
 * 
 * -# Structure Vecteur/Point : permet de représenter un point ou un vecteur.
 * \n Contient une abscisse et une ordonnée.
 * 
 * -# Structure CelPoint/ListePoint : permet de représenter une liste de point ou une cellule.
 * \n Contient une paire une point et un pointeur vers le point suivant.
 * 
 * -# T_IMAGE : correspond à la taille de l'image (512 pixels).
 */

#ifndef __POINT__
#define __POINT__

#include <stdio.h>
#include <stdlib.h>
#define T_IMAGE 512

typedef struct {
	int x;
	int y;
} Vecteur, Point;

typedef struct lpoint{
	Point p_gauche;
	Point p_droite;
	struct lpoint * suivant;
} CelPoint, * ListePoint;

/*!
 * \brief Initialise un point à partir de l'abscisse et de l'ordonnée données en arguments.
 * 
 * \param x : abscisse du point.
 * \param y : ordonnée du point.
 * 
 * Définit un point et affecte les coordonnées dans x et y.
 * 
 * \return Renvoie un point initialisé.
 */
Point point(int x, int y);

/*!
 * \brief Affiche un point dans la console.
 * 
 * \param p : point à afficher.
*/
void affiche_point_ascii(Point p);

/*!
 * \brief Affiche une liste de points dans la console.
 * 
 * \param l : liste de points à afficher.
*/
void affiche_liste_point_ascii(ListePoint l);

/*!
 * \brief Alloue une cellule pour une paire de points.
 * 
 * \param p_gauche : point dans l'image de gauche.
 * \param p_droite : point dans l'image de droite.
 * 
 * Alloue la mémoire nécessaire pour une cellule de liste de points.
 * 
 * \return Renvoie une cellule de liste de points.
 */
CelPoint * alloue_cel_point(Point p_gauche, Point p_droite);

/*!
 * \brief Permet d'ajouter une paire de points dans la liste de points.
 * 
 * \param p1 : point dans l'image de gauche.
 * \param p2 : point dans l'image de droite.
 * 
 * Alloue une cellule et l'ajoute à la fin de la liste
 * 
 */
void construit_liste_point(ListePoint *l, Point p1, Point p2);

/*!
 * \brief Compare deux points.
 * 
 * \param p1 : premier point.
 * \param p2 : deuxième point.
 * 
 * Compare les coordonnées de deux points.
 * 
 * \return Renvoie 1 si les deux points sont les mêmes et 0 sinon.
 */
int compare_point(Point p1, Point p2);

/*!
 * \brief Libère la mémoire allouée à la liste de points.
 * \param l : liste de points à libérer.
 */
void libere_liste_point(ListePoint* l);

/*!
 * \brief Crée un vecteur à partir de deux points.
 * 
 * \param a : premier point.
 * \param b : deuxième point.
 * 
 * Initialise un vecteur à partir des coordonnées des deux points.
 * 
 * \return Renvoie un vecteur.
 */
Vecteur vecteur(Point a, Point b);

#endif
