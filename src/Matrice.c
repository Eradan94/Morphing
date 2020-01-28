#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../include/Matrice.h"

Matrice alloue_matrice(int taille) {
	int i;
	Matrice res;

	res.taille = taille;
	if (NULL == (res.val = (int **)malloc(taille * sizeof(int *)))) {
		fprintf(stderr, "Erreur d'allocation de la matrice\n");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < taille; i++) {
		if (NULL == (res.val[i] = (int *)malloc(taille * sizeof(int)))) {
			fprintf(stderr, "Erreur d'allocation de la matrice\n");
			exit(EXIT_FAILURE);
		}
	}

	return res;
}

void affiche_matrice(Matrice * m) {
	int i, j;
	printf("[");
	for (i = 0; i < m -> taille; i++) {
		printf("[");
		for (j = 0; j < m -> taille; j++) {
			printf(" %4d", m -> val[j][i]);
		}
		printf("]");
		if (i != (m -> taille) - 1)
			printf("\n ");
	}
	printf("]\n");
}

void sous_matrice(Matrice * m1, Matrice * m2, int x, int y) {
	int i, j;
	int i2 , j2;

	i2 = j2 = 0;
	for(i = 0; i < m1 -> taille; i++) {
		for(j = 0; j < m1 -> taille; j++) {
			if(i != x && j != y) {
				m2 -> val[i2][j2] = m1 -> val[i][j];
				if(j2 == m1 -> taille - 2) {
					j2 = 0;
					i2 += 1;
				}
				else {
					j2 += 1;
				}
			}
		}
	}
}

void libere_matrice(Matrice * m) {
	int i;

	for (i = 0; i < m -> taille; i++) {
		free(m -> val[i]);
	}
	free(m -> val);
}

long determinant(Matrice * m) {
	int i, tmp_res;
	long res = 0;
	Matrice tmp;

	if (m == NULL) {
		exit(EXIT_FAILURE);
	}

	if (m -> taille == 1) {
		return m -> val[0][0];
	}

	if (m -> taille == 2){
		return (m -> val[0][0] * m -> val[1][1]) - (m -> val[0][1] * m -> val[1][0]);
	}

	tmp = alloue_matrice(m -> taille - 1);

	for (i = 0; i < m -> taille; i++) {
		sous_matrice(m, &tmp, i, 0);
		tmp_res = determinant(&tmp);
		res += m -> val[i][0] * pow(-1, i) * tmp_res;
	}
	libere_matrice(&tmp);
	return res;
}
