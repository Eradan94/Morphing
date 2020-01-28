/*!
 * \file Graph.h
 * \brief Gère l'affichage du projet.
 * 
 * -# Structure Bouton : permet de représenter un bouton.
 * \n Contient son texte et ses coordonées.
 * 
 * -# Structure Interface : permet de gerer l'interface.
 * \n Contient les 2 images, leurs coordonées et les boutons.
 */

#ifndef __GRAPH__
#define __GRAPH__

#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "Triangle.h"

#define X_FENETRE 1054
#define Y_FENETRE 600

typedef struct {
	int x, y, haut, larg;
	char texte[128];
} Bouton;

typedef struct {
	Bouton * ajout, * affichage, * rendu, * moins, * frames, * plus, * quitter;
	MLV_Image * img1, * img2;
	int x1_img1, y1_img1, x2_img1, y2_img1;
	int x1_img2, y1_img2, x2_img2, y2_img2;
} Interface;

/*!
 * \brief Initialise les images en les plaçant dans des images MLV.
 * 
 * \param nom_image1 : le nom de la première image
 * \param nom_image2 : le nom de la deuxième image
 * \param image1 : un pointeur vers une image MLV, permet le passage par adresse de la première image
 * \param image2 : un pointeur vers une image MLV, permet le passage par adresse de la deuxième image
 * 
 * Charge les images et les place dans les pointeurs d'images MLV. 
 * Les redimensionne egalement pour qu'elles aient une taille de 512.
 */
void init_images(char * nom_image1, char * nom_image2, MLV_Image ** image1, MLV_Image ** image2);

/*!
 * \brief Alloue un nouveau bouton et initialise ses champs.
 *
 * \param texte : le texte du bouton.
 * \param x : l'abscisse du coin en haut à gauche du bouton.
 * \param y : l'ordonnée du coin en haut à gauche du bouton.
 * \param larg : la largeur du bouton.
 * \param haut : la hauteur du bouton.
 * 
 * Alloue un nouveau bouton et initialise ses champs à l'aide des parametres. 
 * Si l'llocation echoue, le programme est quitté.
 * 
 * \return Renvoie le bouton alloué.
 */
Bouton * bouton(char * texte, int x, int y, int larg, int haut);

/*!
 * \brief Initialise l'interface en chargeant les boutons et les images.
 * 
 * \param itf : l'interface à initialiser.
 * \param img1 : le nom de la première image
 * \param img2 : le nom de la deuxième image
 * 
 * Charge les images dans l'interface (déjà allouée) et alloue les boutons.
 */
void init_interface(Interface * itf, char * img1, char * img_2);

/*!
 * \brief Affiche l'interface.
 *
 * \param itf : l'interface à afficher.
 * 
 * Affiche l'interface, ses boutons, ainsi que ses deux images.
 * 
 * \return Renvoie le bouton alloué.
 */
void affiche_interface(Interface * itf);	

/*!
 * \brief Affiche un triangle sur l'interface graphique.
 *
 * \param itf : le triangle à afficher.
 * 
 * Affiche le triangle avec des arretes et cotés rouges.
 */
void affiche_triangle(Triangle * t);

/*!
 * \brief Affiche les triangle de la liste sur l'interface graphique.
 *
 * \param l : la liste de triangles à afficher.
 * 
 * Affiche les triangles de la liste avec des arretes et cotés rouges.
 */
void affiche_liste_triangle(ListeTriangle* l);

/*!
 * \brief  Récupère un clic sur la fenetre, 
 * et verifie qu'il est bien positionné sur l'un des boutons de l'interface.
 * 
 * \param itf : l'interface qui contient les boutons sur lesquels l'utilisateur est censé cliquer.
 * 
 * Recupère un clic, et cherche dans quel bouton il se trouve. Renvoie une valeur spécifique en fonction du bouton.
 * 
 * \return Renvoie une valeur en fonction de la position du clic :
 * 0 : clic en dehors des boutons
 * 1 : ajout
 * 2 : cacher les points de contrainte
 * 3 : rendu
 * 4 : reduire les frames
 * 5 : augmenter les frames
 * 6 : quitter
 */
int selectionne(Interface * itf);

/*!
 * \brief  Récupère un clic sur la première image, puis sur la deuxième.
 * 
 * \param itf : l'interface qui contient les images sur lesquels l'utilisateur est censé cliquer.
 * \param x1 : l'adresse à laquelle stocker l'abscisse du premier clic.
 * \param x2 : l'adresse à laquelle stocker l'abscisse du deuxième clic.
 * \param y1 : l'adresse à laquelle stocker l'ordonnée du premier clic.
 * \param y2 : l'adresse à laquelle stocker l'ordonnée du deuxième clic.
 * 
 * Recupère un clic, et cherche dans quel bouton il se trouve. Renvoie une valeur spécifique en fonction du bouton.
 * 
 * \return Renvoie une valeur en fonction de la position du clic :
 * 0 : clic en dehors des images.
 * 1 : clic dans des images.
 */
int clic(Interface * itf, int * x1, int * x2, int * y1, int * y2);

#endif
