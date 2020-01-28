#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <MLV/MLV_all.h>
#include <time.h>
#include "../include/Point.h"
#include "../include/Triangle.h"
#include "../include/Graph.h"
#include "../include/Frame.h"
#include "../include/Triangulation.h"

#define T_IMAGE 512

int main(int argc, char* argv[]) {
	Image img_gauche;	
	ListePoint l_p = NULL;
	ListePoint tmp = NULL;
	ListeTriangle l_t = NULL;
	CelTriangle * c_tg;
	int x1, y1, x2, y2, opt, test;
	int affichage = 1, frames = 16;
	Interface itf;

	if (argc < 2){
		printf("Usage : ./Morphing img_1 img_2 [-h]\n"); 
		return 1;
	}
	/* Options :
	 * h : help
	 */
	while ((opt = getopt(argc, argv, "h")) != -1) {
		switch (opt) {
			case 'h': printf("Usage : ./Morphing img_1 img_2 [-h]\n"); return 0;
		}
	}
	
	img_gauche = alloue_tab_image();
	init_interface(&itf, argv[1], argv[2]);
	init_triangle(&l_t);
	while(1) {
		sprintf(itf.frames -> texte, "%d frames", frames);
		affiche_interface(&itf);
		if (affichage) {
			affiche_liste_triangle(&l_t);
		}
		switch(test = selectionne(&itf)) {
			case 0 : continue;
			case 1 : if(clic (&itf, &x1, &x2, &y1, &y2)) break; fprintf(stderr, "TEST\n"); continue;
			case 2 : affichage = !affichage; continue;
			case 3 : capture_image(&img_gauche); genere_frame(l_t, img_gauche, frames); continue;
			case 4 : if (frames > 2) {frames /= 2;} continue;
			case 5 : if (frames < 64) {frames *= 2;} continue;
			case 6 : libere_liste_point(&l_p); libere_liste_triangle(&l_t); exit(EXIT_SUCCESS);
			default: break;
		}
		construit_liste_point(&tmp, point(x1, y1), point(x2, y2));
		if (l_p == NULL)
			l_p = tmp;	
		
		c_tg = cherche_triangle(tmp -> p_gauche, &l_t);
		
		triangule(&l_t, c_tg, tmp);
		MLV_clear_window(MLV_COLOR_BLACK);
	}
	MLV_wait_mouse(NULL, NULL);
	MLV_free_window();
	return 0;
}
