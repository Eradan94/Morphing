#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "../include/Triangle.h"

/* NVL VERSION*/
Triangle triangle(Point a, Point b, Point c) {
	Triangle t;
	t.a = a;
	t.b = b;
	t.c = c;
	return t;
}

void affiche_triangle_ascii(Triangle* t) {
	if(t == NULL) {
		printf("NULL");
	}
	
	printf("Point a : ");
	affiche_point_ascii(t->a);
	printf("Point b : ");
	affiche_point_ascii(t->b);
	printf("Point c : ");
	affiche_point_ascii(t->c);
}

void affiche_liste_triangle_ascii(ListeTriangle* l) {
	ListeTriangle tmp = *l;
	int i = 0;
	
	if(l == NULL) {
		printf("Le triangle dans affiche_liste_triangle_ascii est NULL \n");
		exit(EXIT_FAILURE);
	}

	printf("Triangles :  \n");
	while(tmp != NULL) {
		printf("Triangle %d : \n", i + 1);
		affiche_triangle_ascii(&tmp->t);
		printf("\n");
		printf("Voisins : ");
		if(tmp -> voisin_AB != NULL)
			affiche_triangle_ascii(&tmp -> voisin_AB -> t);
		else
			printf("NULL ");
		if(tmp -> voisin_BC != NULL)
			affiche_triangle_ascii(&tmp -> voisin_BC -> t);
		else
			printf("NULL ");
		if(tmp -> voisin_AC != NULL)
			affiche_triangle_ascii(&tmp -> voisin_AC -> t);
		else
			printf("NULL ");
		printf("\n");
		printf("Paire : ");
		if(tmp -> paire != NULL)
			affiche_triangle_ascii(&tmp -> paire -> t);
		else
			printf("NULL ");
		tmp = tmp->suivant;
		printf("\n\n");
		i+= 1;
	}
}

void libere_liste_triangle(ListeTriangle * l) {
	ListeTriangle tmp = *l;
	while(*l != NULL) {
		tmp = (*l) -> suivant;
		(*l) -> suivant = NULL;
		(*l) -> voisin_AB = NULL;
		(*l) -> voisin_AC = NULL;
		(*l) -> voisin_BC = NULL;
		free((*l) -> paire);
		(*l) -> paire = NULL;
		free(*l);
		*l = tmp;
	}
	*l = NULL;
}

CelTriangle* alloue_cel_triangle(Triangle t) {
	CelTriangle* tmp;
	tmp = (CelTriangle*) malloc(sizeof(CelTriangle));
	if(tmp != NULL) {
		tmp -> t = t;
		tmp -> voisin_AB = NULL;
		tmp -> voisin_BC = NULL;
		tmp -> voisin_AC = NULL;
		tmp -> paire = NULL;
		tmp -> suivant = NULL;
	}
	return tmp;
}

void init_triangle(ListeTriangle* l) {
	Point p1_no = point(10, 10);
	Point p1_so = point(10, 10 + T_IMAGE);
	Point p1_se = point(10 + T_IMAGE, 10 + T_IMAGE);
	Point p1_ne = point(10 + T_IMAGE, 10);

	Point p2_no = point(20 + T_IMAGE, 10);
	Point p2_so = point(20 + T_IMAGE, 10 + T_IMAGE);
	Point p2_se = point(20 + 2 * T_IMAGE, 10 + T_IMAGE);
	Point p2_ne = point(20 + 2 * T_IMAGE, 10);

	(*l) = alloue_cel_triangle(triangle(p1_ne, p1_no, p1_se)); 
	(*l) -> paire = alloue_cel_triangle(triangle(p2_ne, p2_no, p2_se)); 
	(*l) -> suivant = alloue_cel_triangle(triangle(p1_no, p1_so, p1_se)); 
	(*l) -> suivant -> paire = alloue_cel_triangle(triangle(p2_no, p2_so, p2_se)); 
	voisinage(*l, (*l)->suivant);
	voisinage((*l)->paire, (*l)->suivant->paire);
}

void calcule_barycentre(Triangle t, Point p, int* a, int* b, int* c) {
	Vecteur pb = vecteur(p, t.b);
	Vecteur pc = vecteur(p, t.c);
	Vecteur pa = vecteur(p, t.a);
	(*a) = (pb.x * pc.y) - (pb.y * pc.x);
	(*b) = (pc.x * pa.y) - (pc.y * pa.x);
	(*c) = (pa.x * pb.y) - (pa.y * pb.x);
}

int est_dans_triangle(Triangle t, Point p) {
	int a, b, c;
	
	calcule_barycentre(t, p, &a, &b, &c);
	if(a <= 0 && b <= 0 && c <= 0)
		return 1;
	else if(a >= 0 && b >= 0 && c >= 0)
		return 1;
	return 0;
}

CelTriangle* cherche_triangle(Point p, ListeTriangle * l) {
	ListeTriangle tmp;

	if (l == NULL) {
		return NULL;
	}
	tmp = *l;
	for(tmp = *l; tmp != NULL; tmp = tmp -> suivant) {
		if (est_dans_triangle(tmp -> t, p) == 1)
			return tmp;
		else if(tmp -> paire != NULL && est_dans_triangle(tmp -> paire -> t, p) == 1)
			return tmp -> paire;
	}
	return tmp;
}

Point determine_point(CelTriangle* t, CelTriangle* t2) {
	if(t == NULL || t2 == NULL) {
		printf("Triangle NULL dans determine_point \n");
		exit(EXIT_FAILURE);
	}
	
	if(t2->voisin_AB == t) 
		return t2->t.c;
	else if(t2->voisin_BC == t) 
		return t2->t.a;
	else if(t2->voisin_AC == t)
		return t2->t.b;
	printf("les triangles ne sont pas voisins \n");
	exit(EXIT_FAILURE);
}

int voisinage(CelTriangle* t1, CelTriangle* t2) {
	/* Teste et etablit les relations de voisinage entre deux triangles, renvoie 1 si les triangles sont voisins et 0 sinon.*/
	if(t1 == NULL || t2 == NULL) {
		return 0;
	}
	if(compare_point(t1->t.a, t2->t.a)) {
		if(compare_point(t1->t.b, t2->t.c)) {
			t1->voisin_AB = t2;
			t2->voisin_AC = t1;
			return 1;
		}
		else if(compare_point(t1->t.c, t2->t.b)) {
			t1->voisin_AC = t2;
			t2->voisin_AB = t1;
			return 1;
		}
	}
	else if(compare_point(t1->t.b, t2->t.b)) {
		if(compare_point(t1->t.a, t2->t.c)) {
			t1->voisin_AB = t2;
			t2->voisin_BC = t1;
			return 1;
		}
		else if(compare_point(t1->t.c, t2->t.a)) {
			t1->voisin_BC = t2;
			t2->voisin_AB = t1;
			return 1;
		}
	}
	else if(compare_point(t1->t.c, t2->t.c)) {
		if(compare_point(t1->t.a, t2->t.b)) {
			t1->voisin_AC = t2;
			t2->voisin_BC = t1;
			return 1;
		}
		else if(compare_point(t1->t.b, t2->t.a)) {
			t1->voisin_BC = t2;
			t2->voisin_AC = t1;
			return 1;
		}
	}
	
	else if(compare_point(t1->t.c, t2->t.b)) {
		if(compare_point(t1->t.b, t2->t.c)) {
			t1->voisin_BC = t2;
			t2->voisin_BC = t1;
			return 1;
		}
	}
	else if(compare_point(t1->t.b, t2->t.a)) {
		if(compare_point(t1->t.a, t2->t.b)) {
			t1->voisin_AB = t2;
			t2->voisin_AB = t1;
			return 1;
		}
	}
	else if(compare_point(t1->t.a, t2->t.c)) {
		if(compare_point(t1->t.c, t2->t.a)) {
			t1->voisin_AC = t2;
			t2->voisin_AC = t1;
			return 1;
		}
	}
	return 0;
}

void reinitialise_voisins(CelTriangle* t) {
	if(t == NULL) {
		printf("Triangle NULL dans reinitialise_voisins \n");
		exit(EXIT_FAILURE);
	}
	t->voisin_AB = NULL;
	t->voisin_BC = NULL;
	t->voisin_AC = NULL;
}

char position_point(Triangle t, Point p) {
	if(p.x == t.a.x && p.y == t.a.y)
		return 'a';
	else if(p.x == t.b.x && p.y == t.b.y)
		return 'b';
	else if(p.x == t.c.x && p.y == t.c.y)
		return 'c';
	return '0';
}



