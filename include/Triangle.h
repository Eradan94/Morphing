/*!
 * \file Triangle.h
 * \brief Gère la construction et l'utilisation de la structure Triangle.
 * 
 * -# Structure Triangle : permet de représenter un triangle avec ses trois sommets.
 * \n Contient 3 strcutures de type point.
 * 
 * -# Structure CelTriangle/ListeTriangle : permet de représenter une liste de triangle ou une cellule.
 * \n Contient un triangle, 3 pointeurs vers les 3 possibles voisins de ce triangle,
 * contient aussi un pointeur vers la paire du triangle dans l'image de droite.
 * le pointeur suivant correspond au triangle suivant dans la liste.
 */

#ifndef __TRIANGLE__
#define __TRIANGLE__

#include <stdio.h>
#include <stdlib.h>
#include "Point.h"

#include "Matrice.h"

typedef struct {
	Point a;
	Point b;
	Point c;
} Triangle;

typedef struct ltriangle{
	Triangle t;
	struct ltriangle *voisin_AB;
	struct ltriangle *voisin_BC;
	struct ltriangle *voisin_AC;
	struct ltriangle *paire;
	struct ltriangle *suivant;
} CelTriangle, *ListeTriangle;

/*!
 * \brief Initialise un triangle à partir de 3 points donnés en arguments.
 * 
 * \param a : sommet A
 * \param b : sommet B
 * \param c : sommet C
 * 
 * Définit un triangle et affecte les 3 points dans ses champs a, b, et c.
 * 
 * \return Renvoie un triangle initialisé.
 */
Triangle triangle(Point a, Point b, Point c);


/*!
 * \brief Affiche le triangle t dans le terminal.
 * 
 * \param t : triangle à afficher.
 */
void affiche_triangle_ascii(Triangle* t);

/*!
 * \brief Affiche la liste de triangles l dans le terminal.
 * 
 * \param l : liste de triangle à afficher.
 */
void affiche_liste_triangle_ascii(ListeTriangle* l);

/*!
 * \brief Alloue une cellule pour un triangle.
 * 
 * \param t : triangle qui sera ajouté dans la cellule allouée.
 * 
 * Alloue la mémoire nécessaire pour une cellule de liste de triangles.
 * 
 * \return Renvoie une cellule de liste de triangles.
 */
CelTriangle* alloue_cel_triangle(Triangle t);


/*!
 * \brief Libère la mémoire allouée à la liste de triangles.
 * \param l : liste de triangles à libérer.
 */
void libere_liste_triangle(ListeTriangle * l);

/*!
 * \brief Détermine quel point de t2 n'est pas dans t1.
 * 
 * \param t : triangle que l'on veut tester s'il est delaunya ou non.
 * \param t2 : un des voisins de t.
 * 
 * Determine quel est le voisin de t2 qui permet de revenir sur t.
 * Le point de t2 qui n'est dans t est celui qui n'est pas dans la diagonale en commun des 2 triangles.
 * Quitte le programme si l'un des deux triangles est NULL.
 * 
 * \return Renvoie le point de t2 qui n'est pas dans t, si les deux triangles ne sont pas voisins, le programme quitte car ils doivent être obligatoirement voisins.
 */
Point determine_point(CelTriangle* t, CelTriangle* t2);

/*!
 * \brief Initialise la liste de triangle selon la situation de départ.
 * 
 * \param l : liste de triangle à initialiser.
 * 
 * Ajoute 2 cellules à la liste de triangles (les deux triangles de départ), 
 * ainsi que 2 cellules pour les triangles de droites.
 */
void init_triangle(ListeTriangle * l);

/*!
 * \brief Initialise la liste de triangle selon la situation de départ.
 * 
 * \param t : triangle de référence.
 * \param p : point dont on veut déterminer les coordonnées barycentriques dans t.
 * \param a : alpha.
 * \param b : beta.
 * \param c : gamma.
 * 
 * Calcule les coordonnées barycentriques du point p dans t, les coordonnées sont passées par adresse dans a, b et c.
 */
void calcule_barycentre(Triangle t, Point p, int* a, int* b, int* c);

/*!
 * \brief Détermine si le point p est dans t.
 * 
 * \param t : triangle de référence.
 * \param p : point testé.
 * 
 * Calcule les coordonnées barycentriques de p dans t.
 * p est dans t si a b et c sont tous >= 0 ou <= 0.
 * 
 * \return Renvoie 1 si p est dans t. Renvoie 0 sinon.
 */
int est_dans_triangle(Triangle t, Point p);

/*!
 * \brief Cherche dans quel triangle est le point p.
 * 
 * \param l : liste de triangles.
 * \param p : point testé.
 * 
 * Parcourt la liste des triangles, si p n'est pas dans le triangle de la cellules courante, 
 * alors on regarde s'il est dans le triangle paire de cette cellule. Sinon on passe au suivant.
 * 
 * \return Renvoie la cellule du triangle où le point est situé.
 */
CelTriangle * cherche_triangle(Point p, ListeTriangle * l);

/*!
 * \brief Remet à NULL tous les voisins de la cellule prise en argument.
 * 
 * \param t : cellule dont l'on veut réinitialiser les voisins.
 *
 * Tous les voisins de t sont remis à NULL.
 */
void reinitialise_voisins(CelTriangle* t);

/*!
 * \brief Crée les liens de voisinage entre deux triangles dans la mesure du possible.
 * 
 * \param t1 : première cellule.
 * \param t2 : deuxième cellule.
 * 
 * Teste les coordonnées des sommets de t1 et t2 et affecte les champs de voisinages dans le cas ou les deux triangles sont voisins.
 * 
 * \return Renvoie 1 si les deux triangles sont voisins et 0 sinon.
 */
int voisinage(CelTriangle* t1, CelTriangle* t2);

/*!
 * \brief Détermine quel sommet correspond au point pris en argument.
 * 
 * \param t : cellule du triangle à tester.
 * \param p : point à tester.
 * 
 * Teste les coordonnées de p avec les sommets de t.
 * 
 * \return  a b ou c selon à quel sommet correspond p, renvoie le caractère 0 sinon..
 */
char position_point(Triangle t, Point p);


#endif
