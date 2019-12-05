#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct aresta{
	struct vertice* v1;
	struct vertice* v2;
	int peso;
}aresta;

typedef struct vertice{
	struct vertice* predecessor;
	int estimativa;
}vertice;


void inicializa(vertice* sistemas, int n){
	int i;
	for (i = 0; i < n; i++){
		sistemas[i].predecessor = NULL;
		sistemas[i].estimativa = INT_MAX;
	}
	sistemas[0].estimativa = 0;
}

int overflow(int a, int b){
	if (a>0 && b>0 && (a+b<0))
		return 1;
	return 0;
}

void relaxar(aresta* buraco){
	int a, b;
	a = buraco->v1->estimativa;
	b = buraco->peso;
	if ((buraco->v2->estimativa > a+b) && !overflow(a, b)){
		buraco->v2->estimativa = buraco->v1->estimativa + buraco->peso;
		buraco->v2->predecessor = buraco->v1;
	}
}



int main (){

	int n_sistemas, n_buracos;
	vertice *sistemas;
	aresta *buracos;
	int i, j, m, n, p;

	scanf("%d %d", &n_sistemas, &n_buracos);
	sistemas = malloc(n_sistemas * sizeof(vertice));
	buracos = malloc(n_buracos * sizeof(aresta));

	inicializa(sistemas, n_sistemas);

	for (i = 0; i < n_buracos; i++){
		scanf("%d %d %d", &m, &n, &p);
		buracos[i].peso = p;
		buracos[i].v1 = &(sistemas[m]);
		buracos[i].v2 = &(sistemas[n]);
	}

	for (i = 0; i < n_sistemas-1; i++){
		for (j = 0; j < n_buracos; j++){
			/*for (p = 0; p < n_sistemas; p++){
				printf(" %d ", sistemas[p].estimativa);
			}
			printf("\n");*/
			relaxar(&(buracos[j]));
		}
	}
	/*for (p = 0; p < n_sistemas; p++){
		printf(" %d ", sistemas[p].estimativa);
	}
	printf("\n");*/
	for (j = 0; j < n_buracos; j++){
		if (buracos[j].v2->estimativa > buracos[j].v1->estimativa + buracos[j].peso){
			printf("Possivel\n");
			free(sistemas);
			free(buracos);
			return 0;
		}
	}
	free(sistemas);
	free(buracos);
	printf("Impossivel\n");

	return 0;
}
