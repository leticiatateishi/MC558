/*	Letícia Mayumi Araújo Tateishi - RA 201454 */
/*	MC558 - Projeto e Análise de Algoritmos II - 2s2019 */
/*	Laboratório 2 - Puzzle */

/*	PROBLEMA:
 *	Dado um grafo G, com n vértices e m arestas, com pesos inteiros nas arestas,
 *	e dois vértices s e t, queremos encontrar, entre todos os caminhos possíveis
 *	entre s e t, aquele cujo o peso máximo de uma aresta do caminha é menor. */

/*	ENTRADA:
 *	- inteiros n e m (número de vértices e de arestas, respectivamente)
 *	- m linhas seguintes com 3 inteiros: x, y, w(x,y) (arestas com extremos x e 
 *	y, com peso w(x,y)
 *	- inteiro k 
 *	- k linhas seguintes com 2 inteiros: s e t (s é o vértice inicial do caminho
 *	e t é o vértice final do caminho) */

/*	SAÍDA:
 *	- k linhas com o maior peso de um caminho de menor peso máximo */

/*	ALGORITMO:
 *	Implementei o algoritmo de árvore geradora mínima de Kruskal, pois seleciona
 *	as arestas em ordem não-decrescente de peso. Modifiquei o algoritmo inicial
 *	para parar quando encontrarmos um caminho entre s e t, mesmo que as arestas
 *	selecionadas não cubram todos os vértices. Desta maneira, geramos um caminho
 *	entre s e t com as menores arestas do grafo. Dentre as arestas selecionadas,
 *	determinamos a de maior peso, cujo rótulo é a saída do algoritmo. */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*	Um elemento de um conjunto deve possuir um rótulo, um apontador para o 
 *	representante do conjunto e um apontador para o próximo elemento do 
 *	conjunto. */
typedef struct elemento{
	int rotulo;
	struct elemento* representante;
	struct elemento* proximo;
} elemento;

/*	Uma aresta deve ter apontadores para seus extremos v1 e v2 e um peso */
typedef struct aresta{
	elemento* v1;
	elemento* v2;
	int peso;
} aresta;

/*	Cria um conjunto vazio onde o representante é ele mesmo e não existe próximo
 *	elemento. 
 *	Entrada: rótulo do único elemento do conjunto
 *	Saída: conjunto unitário com rótulo desejado */
elemento* make_set(int rotulo){
	elemento* set = malloc(sizeof(elemento));
	(*set).rotulo = rotulo;
	(*set).representante = set;
	(*set).proximo = NULL;
	return set;
}

/*	Encontra o representante do conjunto de um elemento.
 *	Entrada: um apontador para um elemento
 *	Saída: apontador para o representante do conjunto daquele elemento */
elemento* find_set(elemento* e){
	return (*e).representante;
}

/*	Recebe dois conjuntos disjuntos e faz a união deles, ou seja, muda o 
 *	representante de todos os elementos de um conjunto para o representante do
 *	outro conjunto.
 *	Entrada: apontadores para os representantes dos conjuntos */
void join(elemento* e1, elemento* e2){
	elemento* tail;
	tail = e1;
	while ((*tail).proximo != NULL)
		tail = (*tail).proximo;
	(*tail).proximo = e2;
	while(e2 != NULL){
		(*e2).representante = e1;
		e2 = (*e2).proximo;
	}
}

/*	Torna todos os conjuntos unitários 
 *	Entrada: conjunto de conjuntos e seu tamanho */
void reset_set(elemento** conjuntos, int n){
	int i;
	for (i = 0; i < n; i++){
		conjuntos[i]->representante = conjuntos[i];
		conjuntos[i]->proximo = NULL;
	}
}

/*	Divide o vetor a ser ordenado em duas metades, ordena os dois subvetores e
 *	depois intercala os dois com merge. 
 *	Entrada: vetor de apontadores, p posição de início do vetor e r posição 
 *	final do vetor */
void merge_sort(aresta** vetor, int p, int r){
	int q;
	if (p < r){
		q = floor((p+r)/2);
		merge_sort(vetor, p, q);
		merge_sort(vetor, q+1, r);
		merge(vetor, p, q, r);

	}
}

/*	Intercala dois subvetores ordenados para que o resultado seja um vetor
 *	ordenado.
 *	Entrada: vetor de apontadores, p posição de início do vetor, q posição 
 *	do meio do vetor e r posição final. */
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

	/*	Criamos um conjunto de conjuntos disjuntos, um conjunto para arestas do 
	 *	grafo e um conjunto para as arestas que serão selecionadas */
	conjuntos = malloc(sizeof(elemento*) * n_areas);
	arestas = malloc(sizeof(aresta*) * n_ligacoes);
	selecionadas = malloc(sizeof(aresta*) * (n_areas-1));

	/*	Criamos conjuntos unitários para todos os vértices */
	for (i = 0; i < n_areas; i++)
		conjuntos[i] = make_set(i);

	/*	Criamos uma struct aresta para cada aresta do grafo */
	for (i = 0; i < n_ligacoes; i++){
		scanf("%d %d %d", &v1, &v2, &peso);
		arestas[i] = malloc (sizeof(aresta));
		arestas[i]->v1 = conjuntos[v1];
		arestas[i]->v2 = conjuntos[v2];
		arestas[i]->peso = peso;
	}

	/*	Ordenamos as arestas */
	merge_sort(arestas, 0, n_ligacoes-1);

	scanf("%d", &k);
	for (i = 0; i < k; i++){
		reset_set(conjuntos, n_areas);
		n_selecionadas = 0;
		scanf("%d %d", &inicio, &fim);
		v_inicio = (conjuntos[inicio]);
		v_fim =  (conjuntos[fim]);

		for (j = 0; j < n_ligacoes; j++){
			/*	Se os vértices s e t já pertencem ao mesmo conjunto, então já 
			 *	encontramos um caminho entre eles. */
			if (find_set(v_inicio) == find_set(v_fim))
				break;
			/*	Caso contrário, verificamos se a aresta j liga dois vértices de 
			 *	conjuntos distintos e, se sim, unimos os conjuntos */
			if (find_set(arestas[j]->v1) != find_set(arestas[j]->v2)){
				selecionadas[n_selecionadas++] = arestas[j];
				join(arestas[j]->v1->representante, arestas[j]->v2->representante);
			}
		}

		/*	Encontramos a aresta de maior peso entre as selecionadas */
		maior = 0;
		for (j = 0; j < n_selecionadas; j++){
			if (selecionadas[j]->peso > maior)
				maior = selecionadas[j]->peso;
		}
		printf("%d\n", maior);
	}

	/*	Liberamos vetores alocados dinamicamente */
	for(i = 0; i < n_areas; i++)
		free(conjuntos[i]);
	free(conjuntos);
	for (i = 0; i < n_ligacoes; i++)
		free(arestas[i]);
	free(arestas);
	free(selecionadas);

	return 0;
}