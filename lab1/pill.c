#include <stdio.h>
#include <stdlib.h>

int main(){
	int n_moleculas, n_ligacoes;
	int *adjacencias;
	int *vertices;
	int *fila;
	int i, j, k;
	int posicao;
	int inicio_fila, fim_fila = 0;
	int pai;

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

	fila = (int *)malloc(sizeof(int) * n_moleculas + 1);

	for (i = 0; i < n_moleculas; i++){
		if (vertices[i] == -1){
			inicio_fila = fim_fila = 0;
			fila[fim_fila++] = i;
			vertices[i] = 1;

			while (inicio_fila < fim_fila){
				pai = fila[inicio_fila];
				for (k = 0; k < n_moleculas; k++){
					if (adjacencias[pai * n_moleculas + k] == 1){
						if (vertices[k] == vertices[pai]){
							printf ("dotutama\n");
							return 0;
						}
						if (vertices[k] == -1){
							vertices[k] = (vertices[pai] + 1) % 2;
							fila[fim_fila++] = k;					
						}
					}
				}
				inicio_fila++;
			}
			
			
		}
	}

	printf ("doturacu ou dotutama\n");

	return 0;
}

