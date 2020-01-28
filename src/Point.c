#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "../include/Point.h"

Point point(int x, int y) {
	Point p;
	p.x = x;
	p.y = y;
	return p;
}

void affiche_point_ascii(Point p) {
	printf("%d %d ", p.x, p.y);
}

void affiche_liste_point_ascii(ListePoint l) {
	ListePoint tmp = l;
	printf("Points gauches : \n");
	while(tmp != NULL) {
		affiche_point_ascii(tmp->p_gauche);
		printf("\n");
		tmp = tmp->suivant;
	}
	tmp = l;
	printf("Points droites : \n");
	while(tmp != NULL) {
		affiche_point_ascii(tmp->p_droite);
		printf("\n");
		tmp = tmp->suivant;
	}
}

CelPoint * alloue_cel_point(Point p_gauche, Point p_droite) {
	CelPoint * tmp;

	tmp = (CelPoint *)malloc(sizeof(CelPoint));
	if(tmp != NULL) {
		tmp -> p_gauche = p_gauche;
		tmp -> p_droite = p_droite;
		tmp -> suivant = NULL;
	}
	
	return tmp;
}

void construit_liste_point(ListePoint * l, Point p1, Point p2) {
	if (*l == NULL) {
		*l = alloue_cel_point(p1, p2);
	}
	else {
		(*l) -> suivant = alloue_cel_point(p1, p2);
		(*l) = (*l) -> suivant;
	}
}

void libere_liste_point(ListePoint* l) {
	ListePoint tmp = *l;
	while(*l != NULL) {
		tmp = (*l) -> suivant;
		(*l) -> suivant = NULL;
		free(*l);
		*l = tmp;
	}
	*l = NULL;
}

int compare_point(Point p1, Point p2) {
	if(p1.x == p2.x && p1.y == p2.y)
		return 1;
	return 0;
}

Vecteur vecteur(Point a, Point b) {
	Vecteur v;
	v.x = b.x - a.x;
	v.y = b.y - a.y;
	return v;
}
