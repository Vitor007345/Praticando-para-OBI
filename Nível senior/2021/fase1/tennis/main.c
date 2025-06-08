#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define _NUM_JOGOS 6

int qntJogosVencidos(){
    int vencidos = 0;
    for(int i = 0; i < _NUM_JOGOS; i++){
        char letra;
        bool erro;
        do{
            scanf(" %c", &letra);
            erro = false;
            if(letra == 'V'){
                vencidos++;
            }else if(letra != 'P'){
                erro = true;
            }
            if(erro){
                printf("Invalid letter, type V or P\n");
            }
        }while(erro);
    }
    return vencidos;
}
bool ehImpar(int num){
    return num & 1;
}
int dividePraCima(int num){
    if(ehImpar(num))num++;
    return num / 2;
}
int calcularGrupo(int vencidos){
    int metadePraCimaVencidos = dividePraCima(vencidos);
    int metadePraCimaNumJogos = dividePraCima(_NUM_JOGOS);
    return  metadePraCimaVencidos? ((metadePraCimaNumJogos + 1) - metadePraCimaVencidos) : -1;
}


int main(){
    printf("%d", calcularGrupo(qntJogosVencidos()));
    return 0;
}
