/*!
 * \file Frame.h
 * \brief Gère le rendu.
 * 
 * -# Structure Pixel : permet de représenter un pixel par ses coordonnées et sa couleur (rgba).
 * 
 * -# Structure Image : Tableau à deux dimensions de pixels.
 */

#ifndef __FRAME__
#define __FRAME__

#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "Triangle.h"
#include "Point.h"

typedef struct {
	Point p;
	int r;
	int g;
	int b;
	int a;	
} Pixel;

typedef struct {
	Pixel** tab;
} Image;

/*!
 * \brief  Dessine une image à partir d'un tableau de pixel.
 * 
 * \param tab_pix : le tableau de pixels contenant les images.
 * 
 * Affiche l'image à partir du tableau de pixel obtenu après le rendu de la triangulation.
 */
void dessine_image(Image img);

/*!
 * \brief  Alloue un tableau de 512x512 pour stocker l'image de gauche.
 */
Image alloue_tab_image();

/*!
 * \brief  enregistre l'image prise en argument dans un tableau de pixels.
 * 
 * \param img_gauche : le tableau de pixels qui va contenir l'image.
 * 
 */
void capture_image(Image* img_gauche);

/*!
 * \brief  Retrouve le pixel du triangle déformé pris en argument dans les triangles à gauche ou à droite..
 * 
 * \param t : triangle sur la fenêtre qui correspond au triangle déformé ou l'on a trouvé le pixel.
 * \param img_gauche : tableau de pixels qui stocke l'image.
 * \param pixel : pixel ou l'on va stocker les coordonnées et la couleur correspondante.
 * \param a : alpha
 * \param b : beta
 * \param c : gamma
 * 
 * Selon si t est sur l'image de gauche ou l'image de droite, on récupère à tel endroit sur la fenêtre les coordonnées et la couleur du pixel équivalent.
 * On utilise a, b et c pour trouver la position du pixel équivalent.
 */
void retrouve_pixel(CelTriangle* t, Image img_gauche, Pixel* pixel, int a, int b, int c);

/*!
 * \brief  Gen.
 * 
 * \param lt : liste des triangles générer avec les clics.
 * \param img_gauche : tableau de pixels qui stocke l'image de gauche.
 * \param nb_frame : nombre de frame à générer.
 * 
 * Affiche l'image à partir du tableau de pixel obtenu après le rendu de la triangulation.
 */
void genere_frame(ListeTriangle lt, Image img_gauche, int nb_frame);

#endif

