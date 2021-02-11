#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<math.h>
#define N 7

int adyacencia[N][N];
float visibilidad[N][N],feromonas[N][N],p;
int alfa,beta,Q;
int camino[N];
int camino_aux[N];
int contador_camino=0;


void camino_inicial(int init){
	camino[contador_camino]=init;
	int temp,siguiente,fin=1,ab=0,i;
	
	do{
		temp=1;
		siguiente=rand()%(N);
		if(adyacencia[camino[contador_camino]][siguiente]!=0){
			for(i=0;i<contador_camino+1;i++){
				if(camino[i]==siguiente){
					temp=0;
				}
			}
		}else{
			temp=0;
		}
		if(temp==1){
			contador_camino++;
			camino[contador_camino]=siguiente;
			if(siguiente==3){
				fin=0;
			}
			
		}
		ab++;
		if(ab>100){
			contador_camino=0;
			ab=0;
		}
		
	}while(fin!=0);
	contador_camino=0;	
}//fin camino_inicial

void actualizar_feromonas(){
	float tau;
	int i,j,k;
	for(i=0;i<N;i++){
		for(j=i+1;j<N;j++){
			if(adyacencia[i][j]!=0){
				tau=(1.0-p)*feromonas[i][j];
				for(k=0;k<6;k++){
					if( camino[k]==i && camino[k+1]==j){
						tau=(1.0-p)+(Q/recorrido());
					}else if(camino[k]==j&&camino[k+1]==i){
						tau=(1.0-p)+(Q/recorrido());
					}
					
				}
				feromonas[i][j]=tau;
				feromonas[j][i]=tau;
			}
		}
	}
}//fin actualizar_feromonas

int recorrido(){
	int t=0,i,j;
	for(i=1;i<N;i++){
		if(camino[i]!=-1){
			t=t+adyacencia[camino[i-1]][camino[i]];	
		}
	}
	return t;
}//fin recorrido

void nuevo_camino(){
	float posibles_c[N];
	int posibles[N];
	int a,contador;
	float total,total_c;
	float selector;
	long int temp;
	int siguiente=0;
	int bandera;
	int fin=1;
	int ab=0;
	int i,j,w,s,r;
	do{
		a=camino[contador_camino];
		contador=0;
		ab=0;
		total=0.0;
		total_c=0.0;
		for(i=0;i<N;i++){
			if(adyacencia[a][i]!=0){
				posibles[contador]=i;
				posibles_c[contador]=pow(feromonas[a][i],alfa) * pow(visibilidad[a][i],beta);
				total=total+posibles_c[contador];
				contador++;
			}
		}
		for(i=0;i<contador;i++){
			posibles_c[i]=posibles_c[i]/total;
		}
		for(i=1;i<contador;i++){
			posibles_c[i]=posibles_c[i-1]+posibles_c[i];
		}
		do{
			bandera=0;
			temp=1+rand()%(10001-1);
			selector=temp/10000.0;
			for(i=0;i<contador;i++){
				if(selector<=posibles_c[i]){
					siguiente=posibles[i];
					i=100;	
				}	
			}
			ab++;
			if(ab>100){
				contador_camino=0;
				ab=0;//reinciiar camino de hro,iga
				a=camino[contador_camino];
				contador=0;
				total=0.0;
				total_c=0.0;
				for(i=0;i<N;i++){
					if(adyacencia[a][i]!=0){
						posibles[contador]=i;
						posibles_c[contador]=pow(feromonas[a][i],alfa) * pow(visibilidad[a][i],beta);
						total=total+posibles_c[contador];
						contador++;
					}
				}
				for(i=0;i<contador;i++){
					posibles_c[i]=posibles_c[i]/total;
				}
				for(i=1;i<contador;i++){
					posibles_c[i]=posibles_c[i-1]+posibles_c[i];
				}
				
			}
			for(w=0;w<contador_camino;w++){
				if(siguiente==camino[w]){
					bandera=1;
				}
			}
			
		}while(bandera!=0);
		contador_camino++;
		camino[contador_camino]=siguiente;
		if(siguiente==3){
			fin=0;
		}
	}while(fin!=0);
	for(s=contador_camino+1;s<N;s++){
		camino[s]=-1;
		camino_aux[s]=0;
	}
	for(r=0;r<contador_camino+1;r++){
		camino_aux[r]=camino[r];
	}
	contador_camino=0;
	
}

int main(){
	srand(time(NULL));
	int i,j,hormigas,g;
	float feromona;
	printf("Digite el valor de alfa: ");
	scanf("%d",&alfa);
	printf("Digite el valor de beta: ");
	scanf("%d",&beta);
	printf("Digite el valor de Q: ");
	scanf("%d",&Q);
	printf("Digite el valor de evaporacion: ");
	scanf("%f",&p);
	
	//--------------------------------------------llenado de mayrices-------------------------------------
	
	printf("digite la matriz con adyacencia y peso\n");
	for(i=0;i<N;i++){
		adyacencia[i][i]=0;
		for(j=i+1;j<N;j++){
			printf("%d a %d: ",i+1,j+1);
			scanf("%d",&adyacencia[i][j]);
			adyacencia[j][i]=adyacencia[i][j];
			if(adyacencia[i][j]!=0){
				visibilidad[i][j]=1.0/adyacencia[i][j];
				visibilidad[j][i]=1.0/adyacencia[j][i];
			}
		}
	}
	//matriz de feromonas------------------------------------------------------------------------------
	printf("ingrese la feromona(tau): ");
	scanf("%f",&feromona);
	for(i=0;i<N;i++){
		feromonas[i][i]=0;
		for(j=i+1;j<N;j++){
			if(adyacencia[i][j]!=0){
				feromonas[i][j]=feromona;
				feromonas[j][i]=feromona;
			}else{
				feromonas[i][j]=0;
			}
		}
	}
	//---------------------------------------------------------------------------------------
	printf("digite la cantidad de hormigas requeridas para el algoritmo: ");
	scanf("%d",&hormigas);
	
	system("cls");
	
	printf("\nDatos ingresados de la hormiga\n");
	//--------------------------datos iniciales de la hormiga--------------------------------------------------------------------
	printf("Matrices de adyacencia y de costos\n");
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("%d",adyacencia[i][j]);
		}
		printf("\n");
	}
	printf("Matriz de feromonas\n");
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("%f",feromonas[i][j]);
		}
		printf("\n");
	}
	printf("Matriz de visibilidad\n");
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("%f",visibilidad[i][j]);
		}
		printf("\n");
	}
	
	//---------------------------------datos iniciales de la hormiga------------------------------------------------------------
	
	printf("\n\n");
	
	camino_inicial(0);
	printf("\nDatos actualizados de la hormiga\n");
	for(g=0;g<hormigas;g++){
		actualizar_feromonas();
		nuevo_camino();	
	}
	//------------------------------------datos actualizados de la hormiga----------------------------------------------------------------------
	//int i,j;
	printf("Matrices de adyacencia y de costos\n");
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("%d",adyacencia[i][j]);
		}
		printf("\n");
	}
	printf("Matriz de feromonas\n");
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("%f",feromonas[i][j]);
		}
		printf("\n");
	}
	printf("Matriz de visibilidad\n");
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("%f",visibilidad[i][j]);
		}
		printf("\n");
	}
	//------------------------------------datos actualizados de la hormiga---------------------------------------------------------------------
	printf("\n El Costo del recorrido de la hormiga es %d: \n",recorrido());
	for(i=0;i<N;i++){
		if(camino[i]!=-1){
			printf("[%d]",camino[i]+1);
		}
	}
	getch();
	return 0;
		
}

