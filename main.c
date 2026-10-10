//Trabalho de Grafos
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define Tam 150

typedef struct planta{
    int numVert;
    char especie[15];
    double splen;
    double spwid;
    double ptlen;
    double ptwid;
} Planta;

void zera(int mat[Tam][Tam]);
double distancia_euclidiana(Planta flor1, Planta flor2);
double distancia_euclidiana_norm(Planta flor1, Planta flor2, double menor_DE, double maior_DE);
void distEucIt( Planta flor[],double* menor_DE, double* maior_DE, int vertsMenor[2], int vertsMaior[2]);
void distEucItNorm( Planta flor[], double menor_DE, double maior_DE, int mat_adja[][Tam], double* menor_DENorm, double* maior_DENorm, int vertsMenorNorm[2], int vertsMaiorNorm[2]);

int main(){
    Planta flor[Tam];
    double maior_DE = 0.0, menor_DE = 2132103215464, maior_DENorm = 0.0, menor_DENorm = 2132103215464;
    int vertMaiorDist[2], vertMenorDist[2], vertMaiorDistNorm[2], vertMenorDistNorm[2];
    int mat_adja[Tam][Tam], numVerticies = 0;
    
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
        numVerticies++;
        flor[i].numVert = i + 1;
        fgets(linha,250, f);
        bloco = strtok(linha, ",");
        //printf("%s\n", bloco);
        //sscanf(bloco,"%c", &flor[i].especie);
        bloco = strtok(NULL, ",");
        sscanf(bloco,"%lf", &flor[i].splen);
        bloco = strtok(NULL, ",");
        sscanf(bloco,"%lf", &flor[i].spwid);
        bloco = strtok(NULL, ",");
        sscanf(bloco,"%lf", &flor[i].ptlen);
        bloco = strtok(NULL, ",");
        sscanf(bloco,"%lf", &flor[i].ptwid);

        /*
        printf("%lf\n", flor[i].splen);
        printf("%lf\n", flor[i].spwid);
        printf("%lf\n", flor[i].ptlen);
        printf("%lf\n\n", flor[i].ptwid);
        */
        
    }

    distEucIt(flor,&menor_DE, &maior_DE, vertMenorDist, vertMaiorDist);
    printf("Maior Dist: %f e Menor Dist: %f\n", maior_DE, menor_DE);
    distEucItNorm(flor,menor_DE, maior_DE, mat_adja, &menor_DENorm, &maior_DENorm, vertMenorDistNorm, vertMaiorDistNorm);

    

    //------------ vai ser a função para colocar o grafo no csv -------------
    /*
    f = fopen("grafo.csv", "w");
    char linha[250];
    char *bloco;

    if(f == NULL){
        printf("Arquivo Iris não encontrado");
        return 1;
    }
    */

    //fprintf(f, );

    for(int i=0;i<Tam;i++){
        
        //printf("%s\n", bloco);
        //sscanf(bloco,"%c", &flor[i].especie);
        

        /*
        printf("%lf\n", flor[i].splen);
        printf("%lf\n", flor[i].spwid);
        printf("%lf\n", flor[i].ptlen);
        printf("%lf\n\n", flor[i].ptwid);
        */
        
    }

    

    fclose(f);

    

}
void distEucIt(Planta flor[], double* menor_DE, double* maior_DE, int vertsMenor[2], int vertsMaior[2]){
    for(int i=0; i<Tam ; i++){
        for(int j=i + 1; j<Tam ; j++){
            //calculo da distancia lá
            
            double din = distancia_euclidiana(flor[i],flor[j]);
            //agora precisamos descobrir como normalizar isso...
            
            if(din> *maior_DE){
                *maior_DE = din;
                vertsMaior[0] = flor[i].numVert;
                vertsMaior[1] = flor[j].numVert;
            }
            if(din< *menor_DE){
                *menor_DE = din;
                vertsMenor[0] = flor[i].numVert;
                vertsMaior[1] = flor[j].numVert;
            }
            
            
        }
    }

}

void distEucItNorm(Planta flor[], double menor_DE, double maior_DE, int mat_adja[][Tam], double* menor_DENorm, double* maior_DENorm, int vertsMenorNorm[2], int vertsMaiorNorm[2]){
    for(int i=0; i<Tam ; i++){
        for(int j= i; j<Tam ; j++){
            //calculo da distancia lá
            

            if( i != j){
                double din = distancia_euclidiana_norm(flor[i],flor[j], menor_DE, maior_DE);
                if(din <= 0.3){
                    mat_adja[i][j] = 1;
                    mat_adja[j][i] = 1;
                }else{
                    mat_adja[i][j] = 0;
                    mat_adja[j][i] = 0;
                }

                if(din> *maior_DENorm){
                    *maior_DENorm = din;
                    vertsMaiorNorm[0] = flor[i].numVert;
                    vertsMaiorNorm[1] = flor[j].numVert;
                }
                if(din< *menor_DENorm){
                    *menor_DENorm = din;
                    vertsMenorNorm[0] = flor[i].numVert;
                    vertsMaiorNorm[1] = flor[j].numVert;
                }

            }else{
                mat_adja[i][j] = 0;
            }
            
            //agora precisamos descobrir como normalizar isso...
            
            
            
            
        }
    }

}

void zera(int mat[Tam][Tam]){
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

double distancia_euclidiana_norm(Planta flor1, Planta flor2, double menor_DE, double maior_DE){
    double disAux = sqrt(pow((flor1.splen - flor2.splen),2) + pow((flor1.spwid - flor2.spwid),2) 
    + pow((flor1.ptlen - flor2.ptlen),2) + pow((flor1.ptwid - flor2.ptwid),2));

    double dis = (disAux - menor_DE)/(maior_DE - menor_DE);

    return dis;
}