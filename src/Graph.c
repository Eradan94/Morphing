#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "../include/Graph.h"

void init_images(char * nom_image1, char * nom_image2, MLV_Image ** image1, MLV_Image ** image2) {
	*image1 = MLV_load_image(nom_image1);
	if(*image1 == NULL){
		fprintf(stderr, "Impossible de charger l'image %s\n", nom_image1);
		exit(EXIT_FAILURE);
	}
	
	*image2 = MLV_load_image(nom_image2);
	if(*image2 == NULL){
		fprintf(stderr, "Impossible de charger l'image %s\n", nom_image2);
		exit(EXIT_FAILURE);
	}
	MLV_resize_image_with_proportions(*image1, T_IMAGE, T_IMAGE);
	MLV_resize_image_with_proportions(*image2, T_IMAGE, T_IMAGE);
}

Bouton * bouton(char * texte, int x, int y, int larg, int haut) {
	Bouton * tmp;
	if (NULL == (tmp = (Bouton *)malloc(sizeof(Bouton)))) {
		fprintf(stderr, "Erreur d'allocation\n");
		exit(EXIT_FAILURE);
	}
	strcpy(tmp -> texte, texte);
	tmp -> x = x;
	tmp -> y = y;
	tmp -> larg = larg;
	tmp -> haut = haut;
	return tmp;
}

void init_interface(Interface * itf, char * img1, char * img2) {
	MLV_create_window("Morph", "Morph", X_FENETRE, Y_FENETRE);
	int t_image, y, haut;
	if (itf == NULL) {
		fprintf(stderr, "ITF NULL\n");
		exit(EXIT_FAILURE);
	}
	init_images(img1, img2, &(itf -> img1), &(itf -> img2));
	itf -> x1_img1 = 10;
	itf -> y1_img1 = 10;
	itf -> x2_img1 = itf -> x1_img1 + MLV_get_image_width(itf -> img1);
	itf -> y2_img1 = itf -> y1_img1 + MLV_get_image_height(itf -> img1);
	itf -> x1_img2 = 10 + itf -> x1_img1 + MLV_get_image_width(itf -> img1);
	itf -> y1_img2 = 10;
	itf -> x2_img2 = itf -> x1_img2 + MLV_get_image_width(itf -> img2);
	itf -> y2_img2 = itf -> y1_img2 + MLV_get_image_height(itf -> img2);
	
	t_image = MLV_get_image_height(itf -> img1);
	/* Les boutons ont tous la même position sur l'axe Y */
	y = t_image + 20;
	haut = 60;

	itf -> ajout = bouton("Ajouter point", 
		10,	y, 200,	haut);
	itf -> affichage = bouton("Cacher points",
		220, y,	200, haut);
	itf -> rendu = bouton("Rendu",
		430, y,	180, haut);
	itf -> moins = bouton("<<<",
		620, y,	80,	haut);
	itf -> frames = bouton("** Frames",
		710, y,	120, haut);
	itf -> plus = bouton(">>>",
		840, y,	80,	haut);
	itf -> quitter = bouton("Quitter",
		930, y, 110, haut);
}

void affiche_interface(Interface * itf) {
	int t_image;
	if (itf == NULL) {
		fprintf(stderr, "ITF NULL\n");
		exit(EXIT_FAILURE);
	}
	t_image = itf -> x2_img1 - itf -> x1_img1;

	MLV_clear_window(MLV_COLOR_BLACK);
	MLV_draw_image(itf -> img1, itf -> x1_img1, itf -> y1_img1);
	MLV_draw_image(itf -> img2, itf -> x1_img2, itf -> y1_img2);

	MLV_draw_rectangle(itf -> x1_img1, itf -> y1_img1, t_image, t_image, MLV_COLOR_WHITE);
	MLV_draw_rectangle(itf -> x1_img2, itf -> y1_img2, t_image, t_image, MLV_COLOR_WHITE);

	MLV_draw_text_box(itf -> ajout -> x, itf -> ajout -> y,
		itf -> ajout -> larg, itf -> ajout -> haut,
		itf -> ajout -> texte,
		1,
		MLV_COLOR_WHITE,
		MLV_COLOR_WHITE,
		MLV_COLOR_BLACK,
		MLV_TEXT_CENTER,
		MLV_HORIZONTAL_CENTER,
		MLV_VERTICAL_CENTER
	);
	
	MLV_draw_text_box(itf -> affichage -> x, itf -> affichage -> y,
		itf -> affichage -> larg, itf -> affichage -> haut,
		itf -> affichage -> texte,
		1,
		MLV_COLOR_WHITE,
		MLV_COLOR_WHITE,
		MLV_COLOR_BLACK,
		MLV_TEXT_CENTER,
		MLV_HORIZONTAL_CENTER,
		MLV_VERTICAL_CENTER
	);
	
	MLV_draw_text_box(itf -> rendu -> x, itf -> rendu -> y,
		itf -> rendu -> larg, itf -> rendu -> haut,
		itf -> rendu -> texte,
		1,
		MLV_COLOR_WHITE,
		MLV_COLOR_WHITE,
		MLV_COLOR_BLACK,
		MLV_TEXT_CENTER,
		MLV_HORIZONTAL_CENTER,
		MLV_VERTICAL_CENTER
	);
	
	MLV_draw_text_box(itf -> moins -> x, itf -> moins -> y,
		itf -> moins -> larg, itf -> moins -> haut,
		itf -> moins -> texte,
		1,
		MLV_COLOR_WHITE,
		MLV_COLOR_WHITE,
		MLV_COLOR_BLACK,
		MLV_TEXT_CENTER,
		MLV_HORIZONTAL_CENTER,
		MLV_VERTICAL_CENTER
	);
	
	MLV_draw_text_box(itf -> frames -> x, itf -> frames -> y,
		itf -> frames -> larg, itf -> frames -> haut,
		itf -> frames -> texte,
		1,
		MLV_COLOR_WHITE,
		MLV_COLOR_WHITE,
		MLV_COLOR_BLACK,
		MLV_TEXT_CENTER,
		MLV_HORIZONTAL_CENTER,
		MLV_VERTICAL_CENTER
	);
	
	MLV_draw_text_box(itf -> plus -> x, itf -> plus -> y,
		itf -> plus -> larg, itf -> plus -> haut,
		itf -> plus -> texte,
		1,
		MLV_COLOR_WHITE,
		MLV_COLOR_WHITE,
		MLV_COLOR_BLACK,
		MLV_TEXT_CENTER,
		MLV_HORIZONTAL_CENTER,
		MLV_VERTICAL_CENTER
	);
		
	MLV_draw_text_box(itf -> quitter -> x, itf -> quitter -> y,
		itf -> quitter -> larg, itf -> quitter -> haut,
		itf -> quitter -> texte,
		1,
		MLV_COLOR_WHITE,
		MLV_COLOR_WHITE,
		MLV_COLOR_BLACK,
		MLV_TEXT_CENTER,
		MLV_HORIZONTAL_CENTER,
		MLV_VERTICAL_CENTER
	);
	
	MLV_actualise_window();
}

void affiche_triangle(Triangle * t) {
	if(t == NULL) {
		printf("Cellule NULL dans affiche_triangle \n");
		exit(EXIT_FAILURE);
	}
	
	MLV_draw_filled_circle(t -> a.x, t -> a.y, 5, MLV_COLOR_RED);	
	MLV_draw_filled_circle(t -> b.x, t -> b.y, 5, MLV_COLOR_RED);	
	MLV_draw_filled_circle(t -> c.x, t -> c.y, 5, MLV_COLOR_RED);
	MLV_draw_line(t -> a.x, t -> a.y, t -> b.x, t -> b.y, MLV_COLOR_RED);
	MLV_draw_line(t -> b.x, t -> b.y, t -> c.x, t -> c.y, MLV_COLOR_RED);
	MLV_draw_line(t -> c.x, t -> c.y, t -> a.x, t -> a.y, MLV_COLOR_RED);
}

void affiche_liste_triangle(ListeTriangle* l) {
	ListeTriangle tmp = *l;
	
	if(l == NULL) {
		printf("Liste NULL dasn affiche_liste_triangle  \n");
		exit(EXIT_FAILURE);
	}
	
	while(tmp != NULL) {
		affiche_triangle(&(tmp -> t));
		affiche_triangle(&(tmp -> paire -> t));
		tmp = tmp -> suivant;
	}
	MLV_actualise_window();
}

int selectionne(Interface * itf) {
	int x, y;
	MLV_wait_mouse(&x, &y);
	if (y < itf -> ajout -> y || y > itf -> ajout -> y + itf -> ajout -> haut)
		return 0;
	/* On verifie une seule fois les y car ils sont tous egaux */
	
	if (x > itf -> ajout -> x && x < itf -> ajout -> x + itf -> ajout -> larg)
		return 1;
	if (x > itf -> affichage -> x && x < itf -> affichage -> x + itf -> affichage -> larg)
		return 2;
	if (x > itf -> rendu -> x && x < itf -> rendu -> x + itf -> rendu -> larg)
		return 3;
	if (x > itf -> moins -> x && x < itf -> moins -> x + itf -> moins -> larg)
		return 4;
	if (x > itf -> plus -> x && x < itf -> plus -> x + itf -> plus -> larg)
		return 5;
	if (x > itf -> quitter -> x && x < itf -> quitter -> x + itf -> quitter -> larg)
		return 6;
	return 0;
}

int clic(Interface * itf, int * x1, int * x2, int * y1, int * y2) {
	MLV_draw_text_box(itf -> ajout -> x, itf -> ajout -> y,
		itf -> ajout -> larg, itf -> ajout -> haut,
		"Annuler",
		1,
		MLV_COLOR_BLUE,
		MLV_COLOR_WHITE,
		MLV_COLOR_BLACK,
		MLV_TEXT_CENTER,
		MLV_HORIZONTAL_CENTER,
		MLV_VERTICAL_CENTER
	);
	MLV_actualise_window();
	do {
		MLV_wait_mouse(x1, y1);
		if (*x1 >= itf -> ajout -> x && *x1 <= itf -> ajout -> x + itf -> ajout -> larg 
		 && *y1 >= itf -> ajout -> y && *y1 <= itf -> ajout -> y + itf -> ajout -> haut)
			return 0;
	}while (*x1 < itf -> x1_img1 || *x1 > itf -> x2_img1 || *y1 < itf -> y1_img1 || *y1 > itf -> y2_img1);
	
	do {
		MLV_wait_mouse(x2, y2);
		if (*x2 >= itf -> ajout -> x && *x2 <= itf -> ajout -> x + itf -> ajout -> larg 
		 && *y2 >= itf -> ajout -> y && *y2 <= itf -> ajout -> y + itf -> ajout -> haut)
			return 0;
	}while (*x2 < itf -> x1_img2 || *x2 > itf -> x2_img2 || *y2 < itf -> y1_img2 || *y2 > itf -> y2_img2);
	
	return 1;	
}

