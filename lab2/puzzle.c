/*	Letícia Mayumi Araújo Tateishi - RA 201454 */
/*	MC558 - Projeto e Análise de Algoritmos II - 2s2019 */
/*	Laboratório 2 - Puzzle */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct elemento{
	int rotulo;
	struct elemento* representante;
	struct elemento* proximo;
} elemento;

typedef struct aresta{
	elemento* v1;
	elemento* v2;
	int peso;
} aresta;


elemento* make_set(int rotulo){
	elemento* set = malloc(sizeof(elemento));
	(*set).rotulo = rotulo;
	(*set).representante = set;
	(*set).proximo = NULL;
	return set;
}

elemento* find_set(elemento* e){
	return (*e).representante;
}

void join(elemento* e1, elemento* e2){
	elemento* tail;
	tail = e1;
	while ((*tail).proximo != NULL){
		tail = (*tail).proximo;
	}
	(*tail).proximo = e2;
	while(e2 != NULL){
		(*e2).representante = e1;
		e2 = (*e2).proximo;
	}
}

void print_set(elemento* e){
	while (e != NULL){
		printf("%d ", (*e).rotulo);
		e = (*e).proximo;
	}
	printf("\n");
}

void reset_set(elemento** conjuntos, int n){
	int i;
	for (i = 0; i < n; i++){
		conjuntos[i]->representante = conjuntos[i];
		conjuntos[i]->proximo = NULL;
	}
}

void merge(aresta** vetor, int p, int q, int r){
	int i, j, k;
	aresta** aux;
	aux = malloc (sizeof(aresta*) * (r-p+1));
	for (i = p; i <= q; i++)
		aux[i-p] = vetor[i];
	for (j = r; j > q; j--)
		aux[q+1-p+r-j] = vetor[j];
	i = 0;
	j = r-p;
	for (k = p; k <= r; k++){
		if (aux[i]->peso <= aux[j]->peso)
			vetor[k] = aux[i++];
		else
			vetor[k] = aux[j--];
	}
	free(aux);
}

void merge_sort(aresta** vetor, int p, int r){
	int q;
	if (p < r){
		q = floor((p+r)/2);
		merge_sort(vetor, p, q);
		merge_sort(vetor, q+1, r);
		merge(vetor, p, q, r);

	}
}

int main(){
	int n_areas, n_ligacoes;
	int i, j, v1, v2, peso;
	int k, inicio, fim;
	elemento* v_inicio, *v_fim;
	elemento** conjuntos;
	aresta** arestas;
	aresta** selecionadas;
	int n_selecionadas, maior;

	scanf("%d %d", &n_areas, &n_ligacoes);

	conjuntos = malloc(sizeof(elemento*) * n_areas);
	arestas = malloc(sizeof(aresta*) * n_ligacoes);
	selecionadas = malloc(sizeof(aresta*) * (n_areas-1));

	for (i = 0; i < n_areas; i++){
		conjuntos[i] = make_set(i);
	}

	for (i = 0; i < n_ligacoes; i++){
		scanf("%d %d %d", &v1, &v2, &peso);
		arestas[i] = malloc (sizeof(aresta));
		arestas[i]->v1 = conjuntos[v1];
		arestas[i]->v2 = conjuntos[v2];
		arestas[i]->peso = peso;
	}

	merge_sort(arestas, 0, n_ligacoes-1);

	scanf("%d", &k);
	for (i = 0; i < k; i++){
		reset_set(conjuntos, n_areas);
		n_selecionadas = 0;
		scanf("%d %d", &inicio, &fim);
		v_inicio = (conjuntos[inicio]);
		v_fim =  (conjuntos[fim]);
		for (j = 0; j < n_ligacoes; j++){
			if (find_set(v_inicio) == find_set(v_fim)){
				break;
			}
			if (find_set(arestas[j]->v1) != find_set(arestas[j]->v2)){
				selecionadas[n_selecionadas++] = arestas[j];
				join(arestas[j]->v1->representante, arestas[j]->v2->representante);
			}
		}
		maior = 0;
		for (j = 0; j < n_selecionadas; j++){
			if (selecionadas[j]->peso > maior)
				maior = selecionadas[j]->peso;
		}
		printf("%d\n", maior);
	}

	for(i = 0; i < n_areas; i++){
		free(conjuntos[i]);
	}
	free(conjuntos);
	for (i = 0; i < n_ligacoes; i++){
		free(arestas[i]);
	}
	free(arestas);
	free(selecionadas);
	return 0;
}