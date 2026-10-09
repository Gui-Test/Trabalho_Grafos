//Trabalho de Grafos
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define Tam 150

typedef struct planta{
    double splen;
    double spwid;
    double ptlen;
    double ptwid;
} Planta;

int zera(int mat[Tam][Tam]);
double distancia_euclidiana(Planta flor1, Planta flor2);

int main(){
    Planta flor[Tam];
    double maior_DE = 0.0, menor_DE = 2132103215464;
    int mat_adja[Tam][Tam];
    
    zera(mat_adja);

    FILE *f;
    f = fopen("original_IrisDataset.csv", "r");
    char linha[250];
    char *bloco;
    
    if(f == NULL){
        printf("Arquivo Iris não encontrado");
    }

    fgets(linha,250, f);

    for(int i=0;i<Tam;i++){
        fgets(linha,250, f);
        bloco = strtok(linha, ",");
        //printf("%s\n", bloco);

        bloco = strtok(NULL, ",");
        sscanf(bloco,"%lf", &flor[i].splen);
        bloco = strtok(NULL, ",");
        sscanf(bloco,"%lf", &flor[i].spwid);
        bloco = strtok(NULL, ",");
        sscanf(bloco,"%lf", &flor[i].ptlen);
        bloco = strtok(NULL, ",");
        sscanf(bloco,"%lf", &flor[i].ptwid);

        printf("%lf\n", flor[i].splen);
        printf("%lf\n", flor[i].spwid);
        printf("%lf\n", flor[i].ptlen);
        printf("%lf\n\n", flor[i].ptwid);
        
    }

    fclose(f);

    for(int i=0; i<Tam ; i++){
        for(int j=0; j<Tam ; j++){
            //calculo da distancia lá
            double din = distancia_euclidiana(flor[i],flor[j]);
            //agora precisamos descobrir como normalizar isso...

            if(din>maior_DE){
                maior_DE = din;
            }
            if(din<menor_DE){
                menor_DE = din;
            }
            
            
        }
    }

}

int zera(int mat[Tam][Tam]){
    for(int i=0; i<Tam ; i++){
        for(int j=0; j<Tam ; j++){
            mat[i][j] = 0;
        }
    }
}

double distancia_euclidiana(Planta flor1, Planta flor2){
    double dis = sqrt(pow((flor1.splen - flor2.splen),2) + pow((flor1.spwid - flor2.spwid),2) 
    + pow((flor1.ptlen - flor2.ptlen),2) + pow((flor1.ptwid - flor2.ptwid),2));

    return dis;
}