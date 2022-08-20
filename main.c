#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nome[50];
    int idade;
    float altura;
}PESSOA;

void leNomeArquivoEntrada(char S1[50]){
    printf("Digite o nome do arquivo: ");
    fscanf(stdin, "%s", S1);
}

int abreArquivoAEntrada(FILE **Arq, char S1[50]){
    char filename[50];

    sprintf(filename, "%s.txt", S1);

    *Arq = fopen(filename, "r");

    if(*Arq != NULL){
        return 1;
    }else{
        return 0;
    }
}

int leDadosUmaPessoa(PESSOA *P, FILE *Arq){
    char nome[10];
    int idade;
    float altura;

    if(feof(Arq)){
        return 0; 
    }

    fscanf(Arq, "%s", nome);
    strcpy(P->nome, nome);

    fscanf(Arq, "%d", &idade);
    P->idade = idade;

    fscanf(Arq, "%f", &altura);
    P->altura = altura;

    return 1;
}

void fechaArquivo(FILE **Arq){
    fclose(*Arq);
}

void imprimeVetor(PESSOA *Povo, int i){
    for(i = 0; i < 4; i++){
        printf("\nNome: %s\nIdade: %d\nAltura: %.1f\n", Povo[i].nome, Povo[i].idade, Povo[i].altura);
    }
}

int cmp(const void *a, const void *b){
    const PESSOA *left  = ( const PESSOA *)a;
    const PESSOA *right = ( const PESSOA *)b;

    return (right->altura < left->altura ) - ( left->altura < right->altura);
}

void ordenaVetor(PESSOA *Povo, int i){
    qsort(Povo, 4, sizeof(PESSOA), cmp);
}

int main(){
    char S1[50];
    PESSOA Povo[3], P;
    FILE *Arq;
    int i = 0;

    leNomeArquivoEntrada(S1);

    if(abreArquivoAEntrada(&Arq, S1) == 1){
        do{
            if (leDadosUmaPessoa(&P, Arq) == 1){
                Povo[i] = P;
                i++;
            }
            else {
                break;
            };
        } while(1);
        fechaArquivo(&Arq);
        ordenaVetor(Povo, i);
        imprimeVetor(Povo, i);
    }
    else{
        printf("Erro na abertura do arquivo");    
    }
    
    return 0;
}