#include "../include/Triangulation.h"

int det_delaunay(Triangle t, Point p) {
	Matrice m;
	long d;
	m = alloue_matrice(3);
	init_matrice_delaunay(&m, t, p);
	d = determinant(&m);
	libere_matrice(&m);
	return d > 0;
}

/* Teste si un triangle t est delaunay ou non */
int triangle_est_delaunay(CelTriangle* t) {
	Point p1;
	Point p2;
	Point p3;
	
	if(t == NULL) {
		printf("Cellule NULL dans triangle est delaunay \n");
		exit(EXIT_FAILURE);
	}
	
	if(t->voisin_AB != NULL) {
		p1 = determine_point(t, t->voisin_AB);
		if((det_delaunay(t->t, p1)))
			return -1;
	}
	if(t->voisin_BC != NULL) {
		p2 = determine_point(t, t->voisin_BC);
		if((det_delaunay(t->t, p2)))
			return -2;
	}
	if(t->voisin_AC != NULL) {
		p3 = determine_point(t, t->voisin_AC);
		if((det_delaunay(t->t, p3)))
			return -3;
	}
	return 1;
}

/* Triangule. A decouper en plusieurs fonctions */
void triangule(ListeTriangle* l, CelTriangle* cel_t, CelPoint* p) {
	ListeTriangle tmp = *l;
    ListeTriangle tmp2 = *l;
    ListeTriangle ptmp = tmp;
    int err;
   
	/* On cherche le triangle t dans la liste */
    while(tmp != NULL && cel_t != tmp) {
        ptmp = tmp;
        tmp = tmp->suivant;
    }
    
    /* Si t n'est pas trouvé alors on quitte.*/
    if(tmp == NULL) {
		printf("Le triangle à diviser n'a pas été trouvé dans la liste \n");
        exit(EXIT_FAILURE);
	}
   
    /* On crée les 3 nouveaux triangles à partir de t.*/
    CelTriangle* t1 = alloue_cel_triangle(triangle(cel_t->t.a, cel_t->t.b, p->p_gauche)); 
    t1->paire = alloue_cel_triangle(triangle(cel_t->paire->t.a, cel_t->paire->t.b, p->p_droite));
    
    CelTriangle* t2 = alloue_cel_triangle(triangle(p->p_gauche, cel_t->t.b, cel_t->t.c));
    t2->paire = alloue_cel_triangle(triangle(p->p_droite, cel_t->paire->t.b, cel_t->paire->t.c));
    
    CelTriangle* t3 = alloue_cel_triangle(triangle(cel_t->t.a, p->p_gauche, cel_t->t.c)); 
    t3->paire = alloue_cel_triangle(triangle(cel_t->paire->t.a, p->p_droite, cel_t->paire->t.c));
    
	/* On ajoute les triangles en fin de liste.*/
    while(tmp2->suivant != NULL) {
        tmp2 = tmp2->suivant;
    }
    tmp2->suivant = t1;
    tmp2->suivant->suivant = t2;
    tmp2->suivant->suivant->suivant = t3;
    
    /* On maj les voisins à gauche*/
    voisinage(t1, t2);
    voisinage(t1, t3);
    voisinage(t2, t3);
    voisinage(t1, tmp->voisin_AB);
    voisinage(t2, tmp->voisin_BC);
    voisinage(t3, tmp->voisin_AC);
    
    /* On maj les voisins à droite*/
    voisinage(t1 -> paire, t2 -> paire);
    voisinage(t1 -> paire, t3 -> paire);
    voisinage(t2 -> paire, t3 -> paire);
	voisinage(t1 -> paire, tmp -> paire -> voisin_AB);
	voisinage(t2 -> paire, tmp -> paire -> voisin_BC);
	voisinage(t3 -> paire, tmp -> paire -> voisin_AC);

    /* On retire tmp, le triangle divisé n*/
    if(tmp == *l) {
        *l = tmp->suivant;
        tmp->suivant = NULL;
    }
    else {
        ptmp->suivant = tmp->suivant;
        tmp->suivant = NULL;
    }
    
    /* On effectue les flips */
    if((err = triangle_est_delaunay(t1)) < 0) {
    	flip(t1, (tmp -> voisin_AB), -(err));  	
    }
    if((err = triangle_est_delaunay(t2)) < 0) {
    	flip(t2, (tmp -> voisin_BC), -(err));
    }
    if((err = triangle_est_delaunay(t3)) < 0) {
    	flip(t3, (tmp -> voisin_AC), -(err));
    }
	
    free(tmp);
    tmp = NULL;
}

void init_matrice_delaunay(Matrice * m, Triangle t, Point d) {
	if (m == NULL){
		printf("Matrice null dans init_matrice_delaunay \n");
		exit(EXIT_FAILURE);
	}
	
	int dx = d.x -10;
	int dy = 512 - d.y + 10;
	int dx_carre = dx * dx;
	int dy_carre = dy * dy;
	
	m -> val[0][0] = (t.a.x -10) - dx;
	m -> val[0][1] = (t.b.x -10) - dx;
	m -> val[0][2] = (t.c.x -10) - dx ;
	
	m -> val[1][0] = (512 - t.a.y + 10) - dy;
	m -> val[1][1] = (512 - t.b.y + 10) - dy;
	m -> val[1][2] = (512 - t.c.y + 10) - dy;

	m -> val[2][0] = (((t.a.x -10) * (t.a.x -10)) - dx_carre) + (((512 - t.a.y + 10) * (512 - t.a.y + 10)) - dy_carre);
	m -> val[2][1] = (((t.b.x -10) * (t.b.x -10)) - dx_carre) + (((512 - t.b.y + 10) * (512 - t.b.y + 10)) - dy_carre);
	m -> val[2][2] = (((t.c.x -10) * (t.c.x -10)) - dx_carre) + (((512 - t.c.y + 10) * (512 - t.c.y + 10)) - dy_carre);
}

void flip(CelTriangle * t1, CelTriangle * t2, int cote) {
	CelTriangle* t1_v1 = NULL;
	CelTriangle* t1_v2 = NULL;	
	CelTriangle* t2_v1 = NULL;
	CelTriangle* t2_v2 = NULL;
	Triangle t = t1 -> t;
	Point p;
	char c;
	
	if(t1 == NULL || t2 == NULL)
		return;
	if (cote < 1 && cote > 3)
		exit(EXIT_FAILURE);
	
	p = determine_point(t1, t2);	
	c = position_point(t2 -> t, p);

	if(cote == 1) {
		t1 -> t = triangle(p, t.b, t.c);
		t2 -> t = triangle(p, t.c, t.a);
		/* Si l'arête à flipper est AB alors on veut garder en mémoire les voisins AC et BC car AB est communs aux deux triangles t1 et 2. */
		t1_v1 = t1->voisin_BC;
		t1_v2 = t1->voisin_AC;
	}
	else if(cote == 2) {
		t1 -> t = triangle(p, t.a, t.b);
		t2 -> t = triangle(p, t.c, t.a);
		/* Si l'arête à flipper est BC alors on veut garder en mémoire les voisins AB et AC car BC est communs aux deux triangles t1 et 2. */
		t1_v1 = t1->voisin_AB;
		t1_v2 = t1->voisin_AC;
	}
	else {
		t1 -> t = triangle(p, t.a, t.b);
		t2 -> t = triangle(p, t.b, t.c);
		/* Si l'arête à flipper est AC alors on veut garder en mémoire les voisins AB et BC car AC est communs aux deux triangles t1 et 2. */
		t1_v1 = t1->voisin_AB;
		t1_v2 = t1->voisin_BC;
	}
	if(c == 'a') {
		/* Si le point de t2 qui n'est dans t1 est A alors on garde en mémoire les voisins des cotés qui possèdent ce point : le coté BC de t2 est l'arête à flipper. */
		t2_v1 = t2 -> voisin_AB;
		t2_v2 = t2 -> voisin_AC;
	}
	else if(c == 'b') {
		/* Si le point de t2 qui n'est dans t1 est B alors on garde en mémoire les voisins des cotés qui possèdent ce point : le coté AC de t2 est l'arête à flipper. */
		t2_v1 = t2 -> voisin_AB;
		t2_v2 = t2 -> voisin_BC;
	}
	else if(c == 'c') {
		/* Si le point de t2 qui n'est dans t1 est C alors on garde en mémoire les voisins des cotés qui possèdent ce point : le coté AB de t2 est l'arête à flipper. */
		t2_v1 = t2 -> voisin_BC;
		t2_v2 = t2 -> voisin_AC;
	}
	
	/* On réinitialise les voisins pour éviter des conflits.*/
	reinitialise_voisins(t1);
	reinitialise_voisins(t2);
	
	/* Maj des voisins.*/
	voisinage(t1, t1_v1);
	voisinage(t1, t1_v2);
	voisinage(t1, t2_v1);
	voisinage(t1, t2_v2);
	voisinage(t2, t1_v1);
	voisinage(t2, t1_v2);
	voisinage(t2, t2_v1);
	voisinage(t2, t2_v2);
	voisinage(t2, t1);
	
	/* On appelle flip sur la paire du triangle courant pour flip à gauche et donc effectuer le même flip.*/
	if(t1->paire != NULL && t2 -> paire != NULL)	
		flip(t1->paire, t2 -> paire, cote);
	else
		return;
			
	/* On flippe récursivement.*/	
    switch(triangle_est_delaunay(t1)) {
    	case -1: flip(t1, t1 -> voisin_AB, 1); return;
    	case -2: flip(t1, t1 -> voisin_BC, 2); return;
    	case -3: flip(t1, t1 -> voisin_AC, 3); return;
    	default: break;
    }
 
    switch(triangle_est_delaunay(t2)) {
    	case -1: flip(t2, t2 -> voisin_AB, 1); return;
    	case -2: flip(t2, t2 -> voisin_BC, 2); return;
    	case -3: flip(t2, t2 -> voisin_AC, 3); return;
    	default: break;
    }
}
