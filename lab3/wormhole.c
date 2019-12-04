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
		sistemas[i].estimativa = 9999999;
	}
	sistemas[0].estimativa = 0;
}

int overflow(int a, int b){
	if (a>0 && b>0 && (a+b<0))
		return 1;
	return 0;
}

void relaxar(aresta* buraco){
	int a = buraco->v1->estimativa;
	int b = buraco->v2->estimativa;
	if ((a > b + buraco->peso) && !overflow(a, b)){
		buraco->v1->estimativa = buraco->v2->estimativa + buraco->peso;
		buraco->v1->predecessor = buraco->v2;
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

	for (i = 0; i < n_sistemas; i++){
		for (j = 0; j < n_buracos; j++){
			relaxar(&(buracos[j]));
		}
	}
	for (j = 0; j < n_buracos; j++){
		if (buracos[j].v1->estimativa > buracos[j].v2->estimativa + buracos[j].peso){
			printf("Possivel\n");
			return 0;
		}
	}
	printf("Impossivel\n");

	return 0;
}
