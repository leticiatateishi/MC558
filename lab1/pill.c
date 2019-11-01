/*	Letícia Mayumi Araújo Tateishi - RA 201454 */
/*	MC558 - Projeto e Análise de Algoritmos II */
/*	Laboratório 1 - A pílula fantástica */

#include <stdio.h>
#include <stdlib.h>

int main(){
	int n_moleculas, n_ligacoes;
	int *adjacencias, *vertices, *fila;
	int i, j, k;
	int posicao;
	int inicio_fila, fim_fila;
	int pai;

	scanf("%d %d", &n_moleculas, &n_ligacoes);

	/*	Inicializamos a matriz de adjacências */
	adjacencias = (int *)calloc(sizeof(int), n_moleculas * n_moleculas);

	/*	Preenchemos a matriz de adjacências conforme entrada */
	for (k = 0; k < n_ligacoes; k++){
		scanf("%d %d", &i, &j);
		posicao = (i-1) * n_moleculas + j-1;
		adjacencias[posicao] = 1;
		posicao = (j-1) * n_moleculas + i-1;
		adjacencias[posicao] = 1;
	}

	/*	Inicializamos o vetor que armazena a cor dos vértices (0 ou 1).
	 *	Utilizamos a cor -1 para identificar que o vértice ainda não foi descoberto */
	vertices = (int *)malloc(sizeof(int) * n_moleculas);
	for (k = 0; k < n_moleculas; k++)
		vertices[k] = -1;

	/*	Inicializamos a fila */
	fila = (int *)malloc(sizeof(int) * n_moleculas + 1);

	/*	Percorremos todos os vertices e visitamos os que ainda não foram descobertos,
	 *	para que todas as componentes conexas sejam encontradas */
	for (i = 0; i < n_moleculas; i++){
		if (vertices[i] == -1){
			inicio_fila = fim_fila = 0;
			fila[fim_fila++] = i;
			vertices[i] = 1;

			/*	Removemos um vértice da fila */
			while (inicio_fila < fim_fila){
				pai = fila[inicio_fila];
				/*	Encontramos os vértices que são adjacentes a ele */
				for (k = 0; k < n_moleculas; k++){
					if (adjacencias[pai * n_moleculas + k] == 1){
						/*	Se os dois possuirem a mesma cor, sabemos que o grafo não 
						 *	é bipartido e a molécula deve ser de dotutama */
						if (vertices[k] == vertices[pai]){
							printf ("dotutama\n");
							return 0;
						}
						/*	Descobrimos o vértice adjacente */
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