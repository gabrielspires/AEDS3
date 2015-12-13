#include "funcoes.h"

int cmpInt(const void* a, const void* b){
  return *(int*)a - *(int*)b;
}

void bar(int* cal, int* subGrp, int calIndx, int subIndx, int calTam, int subTam, int soma){
	if(somaAchada) return;
	
	int i, somaSubGrupo = 0;
	
	if(subIndx==subTam){
		for(i=0; i<subTam; i++){
			somaSubGrupo += subGrp[i];
			// printf("%d ", subGrp[i]);
		}
		if(somaSubGrupo == soma){
			printf("sim\n");
			somaAchada = 1;
			return;
		}
		// printf("\n");
	}
	else{
		for(i=calIndx; i<calTam; i++){
			subGrp[subIndx] = cal[i];
			bar(cal, subGrp, i+1, subIndx+1, calTam, subTam, soma);
		}
	}
}

void foo(int* cal, int size, int tamSubGrp, int soma){
	int *subGrp;
	subGrp = (int*)calloc(tamSubGrp, sizeof(int));
	bar(cal, subGrp, 0, 0, size, tamSubGrp, soma);
}

int achaSomaPD(int valores[], int qtdV, int soma){
	int **subConjunto;
	int i, j;

	subConjunto = (int**)malloc((qtdV+1) * sizeof(int*));
	for(i=0; i<=qtdV; i++) subConjunto[i] = (int*)calloc((soma+1), sizeof(int));

	// Se a soma não for zero e o conjunto for vazio o resultado é 0
	for(i=1; i<=soma; i++){
		subConjunto[0][i] = 0;
	}

	/*Se a soma for 0, então o resultado é 1 uma vez que
	em sub-conjuntos vazios a soma é zero*/
	for(i=0; i<=qtdV; i++){
		subConjunto[i][0] = 1;
	}
 
	// Preenche a matriz de subConjuntos
	for(i=1; i<=qtdV; i++){
		for(j=1; j<=soma; j++){
			subConjunto[i][j] = subConjunto[i-1][j];

			if(j >= valores[i-1]){
				subConjunto[i][j] = subConjunto[i][j] || subConjunto[i-1][j- valores[i-1]];
			}
		}
	}

	// Joga o resultado em uma variável e da free na matriz
	int resultado = subConjunto[qtdV-1][soma];

	for(i=0; i<qtdV; i++) free(subConjunto[i]);
	free(subConjunto);

	return resultado;
}