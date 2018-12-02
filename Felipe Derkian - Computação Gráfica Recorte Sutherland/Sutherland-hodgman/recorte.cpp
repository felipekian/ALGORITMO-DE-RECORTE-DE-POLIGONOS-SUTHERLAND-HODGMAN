/**
 * Autor: Felipe Derkian de Sousa Freitas
 * Algoritmo: Recorte de Poligonos Sutherland
 * Data: 15/10/2018
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

#define TAM_POINTs 100
#define TAM_MATRIX 102
#define BORDA 1
#define JANELA 4

//LIMITES DA JANELA
int a, b, c, d;

struct Point{
	int a,b,c,d;
};

//cria a struct de pontos
int TOT_POINTs;
Point p[TAM_POINTs];
int TOT_POINTs_AUX;
Point p_aux[TAM_POINTs];

void pause(){
	getchar();
	getchar();
}

void finalinaPrograma(){
	exit(0);
}

void limparTela () {
	system("clear");
}

int continuar () {

	pause();
	cout << "Deseja continuar S/N. \n>>> ";
	char op;
	cin >> op;

	if (op=='S' || op=='s') {
		return 1;
	} else {
		return 0;
	}
}

bool limitesJanela (int x1, int y1) {
	return ((x1 >= a && x1 <= c ) && (y1 >= b && y1 <= d));
}

void sutherland (int matrix[TAM_MATRIX][TAM_MATRIX], int x1, int y1, int x2, int y2, int caso){
	/*
		//caso 1
		a, b, a, d
		//caso 2
		c, b, c, d
		//caso 3
		a, b, c, b
		//caso 4
		a, d, c, d
	*/
	if (!limitesJanela(x1, y1) && !limitesJanela(x2,y2) && caso == 3){
		return;
	}

	if (limitesJanela(x1, y1) && limitesJanela(x2,y2)) {
			p_aux[TOT_POINTs_AUX].a = x1;
			p_aux[TOT_POINTs_AUX].b = y1;
			p_aux[TOT_POINTs_AUX].c = x2;
			p_aux[TOT_POINTs_AUX].d = y2;
			TOT_POINTs_AUX++;
			return;
	}


	//calcula as interseções da janela
	
	if (x1 == x2) {

		/**
		 * Para fazer retas na horizontal
		*/
		if (y1 > y2) {

			/**
			 * inverte caso esteja da direita para esquerda
			*/

			int aux = y1;
			y1 = y2;
			y2 = y1;
		}

		/**
		 *  Faz a inclusão dos pontos que tiverem interceção com a borda da janela
		*/
		
		if (limitesJanela(x1,y1)) {
			
						
			p_aux[TOT_POINTs_AUX].a = x1;
			p_aux[TOT_POINTs_AUX].b = y1;

				while  (1) {
				y1++;
				if (matrix[x1][y1] == JANELA || y1 == y2){
					
					p_aux[TOT_POINTs_AUX].c = x1;
					p_aux[TOT_POINTs_AUX].d = y1;

					TOT_POINTs_AUX++;
					return;
				}			
			}

		return;
		
		}		
		
	//- --------------------------------
		if ( !limitesJanela(x1,y1)) {

			while(matrix[x1][y1] != JANELA){
				y1++;
			}
			
			p_aux[TOT_POINTs_AUX].a = x1;
			p_aux[TOT_POINTs_AUX].b = y1;
		
		
		} else {

			p_aux[TOT_POINTs_AUX].a = x1;
			p_aux[TOT_POINTs_AUX].b = y1;

		}

		

		while  (1) {
			y1++;
			if (matrix[x1][y1] == JANELA || y1 == y2){
				
				p_aux[TOT_POINTs_AUX].c = x1;
				p_aux[TOT_POINTs_AUX].d = y1;

				TOT_POINTs_AUX++;
				return;
			}

			
		}

		return;

	} else if (y1 == y2) {

		/**
		 * para fazer retas na vertical
		*/

		if ( x1 > x2 ) {

			/**
			 * caso estaja de baixo para cima inverte
			*/

			int aux = x1;
			x1 = x2;
			x2 = x1;
		}

		/**
		 *  Faz a inclusão dos pontos que tiverem interceção com a borda da janela
		*/

		if( limitesJanela(x1, y1)){

			p_aux[TOT_POINTs_AUX].a = x1;
			p_aux[TOT_POINTs_AUX].b = y1;

			while (1) {
				x1++;
				if (matrix[x1][y1] == JANELA || x1 == x2) {
					
					p_aux[TOT_POINTs_AUX].c = x1;
					p_aux[TOT_POINTs_AUX].d = y1;
					TOT_POINTs_AUX++;
					return;
				}			
			}

		return;

		}		

		



		//Teste de lime ta janela
		if( !limitesJanela(x1, y1)){

			while(matrix[x1][y1] != JANELA){
				x1++;
			}

			p_aux[TOT_POINTs_AUX].a = x1;
			p_aux[TOT_POINTs_AUX].b = y1;

		} else {

			p_aux[TOT_POINTs_AUX].a = x1;
			p_aux[TOT_POINTs_AUX].b = y1;

		}		

		while (1) {
			x1++;
			if (matrix[x1][y1] == JANELA || x1 == x2) {
				
				p_aux[TOT_POINTs_AUX].c = x1;
				p_aux[TOT_POINTs_AUX].d = y1;
				TOT_POINTs_AUX++;
				return;
			}

			
		}

		return;

	} else {	

		/**
		 * Para fazer retas na diagonal --- DDA para baixo
		*/

		if (limitesJanela(x1, y1) && limitesJanela(x2,y2)) {
			p_aux[TOT_POINTs_AUX].a = x1;
			p_aux[TOT_POINTs_AUX].b = y1;
			p_aux[TOT_POINTs_AUX].c = x2;
			p_aux[TOT_POINTs_AUX].d = y2;
			TOT_POINTs_AUX++;
			return;
		}

			
		int abs_x = x2-x1;
		abs_x = abs(abs_x); //pega o valor abs do delta x

		int abs_y = y2-y1;
		abs_y = abs(abs_y); //pega o valor abs do delta y

		double incremento=0, totalIncrementos=0;

		int x , y, cont = 0;

		if(abs_x > abs_y){			

			incremento = (double) (y2-y1) / (x2-x1);
			y = y1;

			//printf("INCREMETO = %f\n", incremento);
			cont = 0;
			for(x=x1 ; x<=x2 ; x++){
				
				totalIncrementos = totalIncrementos + incremento;
				y =  round(totalIncrementos);

				if (matrix[x][y+y1] == JANELA || x==x2 ) {
					/*
					int t = x-p_aux[TOT_POINTs_AUX].a;
					int l = y+y1 - p_aux[TOT_POINTs_AUX].b;

					if (l == 0 || t == 0) {
						continue;
					}
					*/
					cont++;

					if (cont == 1) {
						p_aux[TOT_POINTs_AUX].a = x;
						p_aux[TOT_POINTs_AUX].b = y+y1;
					} else if (cont == 2) {
						p_aux[TOT_POINTs_AUX].c = x;
						p_aux[TOT_POINTs_AUX].d = y+y1;
						printf("1 - %d %d %d %d\n", p_aux[TOT_POINTs_AUX].a, p_aux[TOT_POINTs_AUX].b, p_aux[TOT_POINTs_AUX].c, p_aux[TOT_POINTs_AUX].d);

						TOT_POINTs_AUX++;
						break;
					} else {
						return;
					}
				}
				//matrix[x][y+y1] = marcar;	//adicionei o +y1
			}


		}else{			

			incremento = (double) (x2-x1) / (y2-y1);
			x = x1;
			
			//printf("INCREMETO = %f\n", incremento);

			cont = 0;
			for(y=y1 ; y<=y2 ; y++){				
				totalIncrementos = totalIncrementos + incremento ;
				x =  round(totalIncrementos);

				if (matrix[x+x1][y] == JANELA || y==y2 ) {
					
					int t = (x+x1)-p_aux[TOT_POINTs_AUX].a;
					int l = y - p_aux[TOT_POINTs_AUX].b;

					if (l == 0 || t == 0) {
						continue;
					}
					
					cont++;

					if (cont == 1) {
						p_aux[TOT_POINTs_AUX].a = x+x1;
						p_aux[TOT_POINTs_AUX].b = y;
						x += (int) round(totalIncrementos) + 3;
					} else if (cont == 2) {
						p_aux[TOT_POINTs_AUX].c = x+x1;
						p_aux[TOT_POINTs_AUX].d = y;
						//printf("2 - %d %d %d %d\n", p_aux[TOT_POINTs_AUX].a, p_aux[TOT_POINTs_AUX].b, p_aux[TOT_POINTs_AUX].c, p_aux[TOT_POINTs_AUX].d);
						TOT_POINTs_AUX++;


						break;
					}
				}
				//matrix[x+x1][y] = marcar; 	//adicionei o +x1
			}
		}
	}
}

void algoritmo_dda(int matrix[TAM_MATRIX][TAM_MATRIX], int marcar, int x1, int y1, int x2, int y2){
	/*
		//caso 1
		a, b, a, d
		//caso 2
		c, b, c, d
		//caso 3
		a, b, c, b
		//caso 4
		a, d, c, d
	*/
	
	if (x1 == x2) {

		/**
		 * Para fazer retas na horizontal
		*/
		if (y1 > y2) {

			/**
			 * inverte caso esteja da direita para esquerda
			*/

			int aux = y1;
			y1 = y2;
			y2 = y1;
		}

		while  (y1 != y2) {
			matrix[x1][y1] = marcar;
			y1++;
		}

		return;

	} else if (y1 == y2) {

		/**
		 * para fazer retas na vertical
		*/

		if ( x1 > x2 ) {

			/**
			 * caso estaja de baixo para cima inverte
			*/

			int aux = x1;
			x1 = x2;
			x2 = x1;
		}

		while (x1 != x2+1) {
			matrix[x1][y1] = marcar;
			x1++;
		}

		return;

	} else {	

		/**
		 * Para fazer retas na diagonal --- DDA para baixo
		*/
	
		int abs_x = x2-x1;
		abs_x = abs(abs_x); //pega o valor abs do delta x

		int abs_y = y2-y1;
		abs_y = abs(abs_y); //pega o valor abs do delta y

		double incremento=0, totalIncrementos=0;

		int x , y;

		if(abs_x > abs_y){

			

			incremento = (double) (y2-y1) / (x2-x1);
			y = y1;

			//printf("INCREMETO = %f\n", incremento);

			for(x=x1 ; x<=x2 ; x++){
				
				totalIncrementos = totalIncrementos + incremento;
				y =  round(totalIncrementos);
				matrix[x][y+y1] = marcar;	//adicionei o +y1
			}


		}else{

			

			incremento = (double) (x2-x1) / (y2-y1);
			x = x1;
			//printf("INCREMETO = %f\n", incremento);

			for(y=y1 ; y<=y2 ; y++){				
				totalIncrementos = totalIncrementos + incremento ;
				x =  round(totalIncrementos);
				matrix[x+x1][y] = marcar; 	//adicionei o +x1
			}
		}
	}
}

void limpaMatrix(int matrix[TAM_MATRIX][TAM_MATRIX]){
	int i, j;
	for(i=0 ; i<TAM_MATRIX; i++){
		for(j=0; j<TAM_MATRIX; j++){
			matrix[i][j] = 0;
		}
	}
}

void limpaPontosStruct (){
	
	/**
	 * 	Aproveita e ja inicializa com 0 a variável de controle do tamanho da struct
	*/

	TOT_POINTs = 0;
	TOT_POINTs_AUX = 0;

	for(int i = 0; i < TAM_POINTs; i++){
		p[i].a = 0;
		p[i].b = 0;
		p[i].c = 0;
		p[i].d = 0;

		p_aux[i].a = 0;
		p_aux[i].b = 0;
		p_aux[i].c = 0;
		p_aux[i].d = 0;
	}	
}

void imprimirMatrix(int matrix[TAM_MATRIX][TAM_MATRIX]){
	int i, j;
	for(i=0 ; i<TAM_MATRIX ; i++){
		for(j=0 ; j<TAM_MATRIX ; j++){
			if(matrix[i][j] == 0){
				printf(" ");
			}else{
				cout << matrix[i][j];
			}
		}
		cout << endl;
	}		
}

void rasterizarJanela(int matrix[TAM_MATRIX][TAM_MATRIX]){

	FILE * fp = fopen("janela/janela.txt", "r");

	if(!fp){
		cout << "Erro na abertura do arquivo da janela..." << endl;
		pause();
		finalinaPrograma();
	}

	
	fscanf(fp, "%d %d %d %d", &a, &b, &c, &d);
	fclose(fp);

	//algoritmo_dda(matrix,JANELA,x1,y1,x2,y2);
	//caso 1
	algoritmo_dda(matrix, JANELA, a, b, a, d);
	//caso 2
	algoritmo_dda(matrix, JANELA, c, b, c, d);
	//caso 3
	algoritmo_dda(matrix, JANELA, a, b, c, b);
	//caso 4
	algoritmo_dda(matrix, JANELA, a, d, c, d);

	return;
}

int limiteOpcao(int op){
	if (op < 0 || op > 4) return 0;
	return 1; 
}

int apresentacao () {
	limparTela();
	int opcao;
	cout << "\t\tAlgoritmo de Recorte - Sutherland.\n" << endl;

	for (int i=1 ; i<5 ; i++) {
		printf("%d - Caso de teste %d.\n", i, i);
	}

	cout << ">>> ";
	cin >> opcao;

	if (limiteOpcao(opcao)) {
		return opcao;
	}else {
		cout << "Opcao invalida.";
		pause();
		apresentacao();
	}

}

void getPoligono (int opcao) {

	/**
	 *  Nessa fase vamos rasterizar os poligonos dados pelos vertices de ligacao dos casos de teste.
	*/

	FILE * fp = NULL;

	if (opcao == 1) {
		fp = fopen("casosTeste/caso1.txt", "r");		
	} else if (opcao == 2) {
		fp = fopen("casosTeste/caso2.txt", "r");
	} else if (opcao == 3) {
		fp = fopen("casosTeste/caso3.txt", "r");
	} else if (opcao == 4) {
		fp = fopen("casosTeste/caso4.txt", "r");
	}

	if (!fp){
		cout << "Arquivo nao encontrado ou nao pode ser lido." << endl;
		pause();
		return;
	} 
	
	//fazer um array de struct

	while (!feof(fp)) {
		fscanf(fp, "%d %d %d %d", &p[TOT_POINTs].a, &p[TOT_POINTs].b, &p[TOT_POINTs].c, &p[TOT_POINTs].d);
		TOT_POINTs++;
	}

	fclose(fp);
}

void rasterizarPoligonoCompleto (int matrix[TAM_MATRIX][TAM_MATRIX], int marcar) {

	/**
	 * 	Com os pontos dados pelo arquivo de teste vamos rasterizar os pontos
	*/

	for(int i=0 ; i<TOT_POINTs ; i++){
		algoritmo_dda(matrix, marcar, p[i].a, p[i].b, p[i].c, p[i].d);		
	}
}

void rasterizarPoligonoRecortado (int matrix[TAM_MATRIX][TAM_MATRIX], int marcar) {

	/**
	 * 	Com os pontos dados pelo arquivo de teste vamos rasterizar os pontos
	*/

	for(int i=0 ; i<TOT_POINTs_AUX ; i++){
		algoritmo_dda(matrix, marcar, p_aux[i].a, p_aux[i].b, p_aux[i].c, p_aux[i].d);		
	}
}

void aplicarSutherland (int matrix[TAM_MATRIX][TAM_MATRIX], int op) {

	/**
	 * 	Com os pontos dados pelo arquivo de teste vamos rasterizar os pontos
	*/

	for(int i=0 ; i<TOT_POINTs ; i++){
		sutherland(matrix, p[i].a, p[i].b, p[i].c, p[i].d, op);
		
	}
}

int main(){
	
	do{

		int op = apresentacao();	
		int matrix[TAM_MATRIX][TAM_MATRIX];		
		limpaMatrix(matrix);
		limpaPontosStruct();		
		//faz o desenho da janela
		rasterizarJanela(matrix);		
		//pega os poligonos da janela
		getPoligono(op);		
		//rasteriza os poligonos
		rasterizarPoligonoCompleto(matrix, BORDA);
		imprimirMatrix(matrix);
		pause();	
		/**
		 * Fazer a parte do sutherland que é determinar as os vertices de recorte
		*/
		limpaMatrix(matrix);
		rasterizarJanela(matrix);
		aplicarSutherland(matrix, op);
		rasterizarPoligonoRecortado(matrix, BORDA);
		imprimirMatrix(matrix);

	} while (continuar());

	return 0;
}
