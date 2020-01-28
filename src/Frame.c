#include "../include/Frame.h"

void dessine_image(Image img) {
	int abs, ord;
	for(abs = 0; abs < 512; abs ++) {
		for(ord = 0; ord < 512; ord ++) {
			MLV_draw_pixel(img.tab[abs][ord].p.x, img.tab[abs][ord].p.y, MLV_rgba(img.tab[abs][ord].r, img.tab[abs][ord].g, img.tab[abs][ord].b, img.tab[abs][ord].a));		
		}
	}
	MLV_actualise_window();
}

Image alloue_tab_image() {
	Image img;
	int i;
	img.tab = malloc(sizeof(Pixel*) * T_IMAGE);
	if(img.tab != NULL) {
		for(i = 0; i < T_IMAGE; i++) {
			img.tab[i] = malloc(sizeof(Pixel) * T_IMAGE);
			if(img.tab[i] == NULL)
				exit(EXIT_FAILURE);
		}
	}
	else
		exit(EXIT_FAILURE);
	return img;
}

void capture_image(Image* img_gauche) {
	Pixel pixel;
	int i, j;
	for(i = 0; i < 512; i++) {
		for(j = 0; j < 512; j++) {
			MLV_get_pixel(i + 10, j + 10, &pixel.r, &pixel.g, &pixel.b, &pixel.a);
			pixel.p.x = i + 10;
			pixel.p.y = j + 10;
			pixel.a = MLV_ALPHA_OPAQUE;
			img_gauche->tab[i][j] = pixel;
		}
	}
}

void retrouve_pixel(CelTriangle* t, Image img_gauche, Pixel* pixel, int a, int b, int c) {
	Point p;
	if(t->t.a.x > 522 || t->t.b.x > 522 || t->t.c.x > 522) {
		p.x = (a * (t->t.a.x - 522) + b * (t->t.b.x -522) + c * (t->t.c.x - 522)) / (a + b + c);
		p.y = (a * t->t.a.y + b * t->t.b.y + c * t->t.c.y) / (a + b + c);
		pixel->p = p;
		MLV_get_pixel(pixel->p.x + 522, pixel->p.y, &pixel->r, &pixel->g, &pixel->b, &pixel->a);
	}
	else {
		p.x = (a * t->t.a.x + b * t->t.b.x + c * t->t.c.x) / (a + b + c);
		p.y = (a * t->t.a.y + b * t->t.b.y + c * t->t.c.y) / (a + b + c);
		pixel->p = p;
		pixel->r = img_gauche.tab[p.x -10][p.y -10].r;
		pixel->g = img_gauche.tab[p.x -10][p.y -10].g;
		pixel->b = img_gauche.tab[p.x -10][p.y -10].b;
	}
	pixel-> a = MLV_ALPHA_OPAQUE;
}

void genere_frame(ListeTriangle lt, Image img_gauche, int nb_frame) {
	ListeTriangle t_def = NULL;
	ListeTriangle tmp_lt = lt;
	ListeTriangle tmp_t_def = NULL;
	CelTriangle* cel_triangle = NULL;
	Pixel g, d, m;
	Point p, pa, pb, pc;
	int index_frame, abs, ord, a, b, c;
	Image frame;
	
	frame = alloue_tab_image();
	/* Chaque frame*/
	for(index_frame = 1; index_frame < nb_frame; index_frame ++) {
		/* On calcule t*/
		float t = ((float)index_frame / nb_frame);
		/* On génère la liste de triangles déformés*/
		while(tmp_lt != NULL) {
			pa = point(((1 - t)*tmp_lt->t.a.x + t * (tmp_lt->paire->t.a.x - 522)), ((1 - t)*tmp_lt->t.a.y + t * tmp_lt->paire->t.a.y)); 
			pb = point(((1 - t)*tmp_lt->t.b.x + t * (tmp_lt->paire->t.b.x - 522)), ((1 - t)*tmp_lt->t.b.y + t * tmp_lt->paire->t.b.y)); 
			pc = point(((1 - t)*tmp_lt->t.c.x + t * (tmp_lt->paire->t.c.x - 522)), ((1 - t)*tmp_lt->t.c.y + t * tmp_lt->paire->t.c.y));
			CelTriangle* cel = alloue_cel_triangle(triangle(pa, pb, pc));
			if(t_def == NULL) {
				t_def = cel;
				tmp_t_def = t_def;
				tmp_t_def->voisin_AB = tmp_lt;
			}
			else {
				tmp_t_def->suivant = cel;
				tmp_t_def = tmp_t_def->suivant;
				tmp_t_def->voisin_AB = tmp_lt;
				
			}
			tmp_lt = tmp_lt->suivant;
		}
		/* Chaque pixel de frame*/
		for(abs = 0; abs < 512; abs ++) {
			for(ord = 0; ord < 512; ord ++) {
				/* On crée un point à partir des coordonnées du pixel.*/
				p = point(abs + 10, ord + 10);
				/* On cherche le triangle auquel appartient le pixel*/
				cel_triangle = cherche_triangle(p, &t_def);	
				/* Calculer les coordonnées barycentriques*/
				calcule_barycentre(cel_triangle->t, p, &a, &b, &c);
				/* On calcule la position de ce pixel dans la fenêtre de gauche et de droite. */
				m.p = p;
				retrouve_pixel(cel_triangle->voisin_AB, img_gauche, &g, a, b, c);	
				retrouve_pixel(cel_triangle->voisin_AB->paire, img_gauche, &d, a, b, c);
				/* On peut donc calculer la couleur de notre pixel de la frame*/
				m.r = (1 - t) * g.r + t * d.r;
				m.g = (1 - t) * g.g + t * d.g;
				m.b = (1 - t) * g.b + t * d.b;
				m.a = (1 - t) * g.a + t * d.a;
				frame.tab[abs][ord] = m;
			}
		}
		dessine_image(frame);
		/* On libère la liste de points déformés.*/
		tmp_t_def = t_def;
		while(tmp_t_def != NULL) {
			tmp_t_def -> paire = NULL;
			tmp_t_def = tmp_t_def->suivant;
		}
		free(t_def);
		t_def = NULL;
		tmp_lt = lt;
	}
}


