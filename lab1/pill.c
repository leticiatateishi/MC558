#include <stdio.h>
#include <stdlib.h>

int main(){
	int n_moleculas, n_ligacoes;
	int *adjacencias;
	int i, j, k;
	int posicao;
	int *vertices;
	int *fila;
	int n_fila = 0;
		int pai, filhos;

	scanf("%d %d", &n_moleculas, &n_ligacoes);

	adjacencias = (int *)calloc(sizeof(int), n_moleculas * n_moleculas);

	for (k = 0; k < n_ligacoes; k++){
		scanf("%d %d", &i, &j);
		posicao = (i-1) * n_moleculas + j-1;
		adjacencias[posicao] = 1;
		posicao = (j-1) * n_moleculas + i-1;
		adjacencias[posicao] = 1;
	}

	vertices = (int *)malloc(sizeof(int) * n_moleculas);
	for (k = 0; k < n_moleculas; k++)
		vertices[k] = -1;

	fila = (int *)calloc(sizeof(int), n_moleculas+1);
	for (k = 0; k < n_moleculas; k++)
		fila[k] = -1;

	fila[0] = 0;
	vertices[0] = 1;

	while (fila[n_fila] != -1){
		pai = fila[n_fila];
		filhos = 0;
		for (k = 0; k < n_moleculas; k++){
			if (adjacencias[pai * n_moleculas + k] == 1){
				if (vertices[k] == vertices[pai]){
					printf ("dotutama\n");
					return 0;
				}
				vertices[k] = (vertices[pai] + 1) % 2;
				fila[filhos++] = k;
			}

		}
		n_fila++;
	}

	printf ("doturacu ou dotutama\n");

	return 0;
}