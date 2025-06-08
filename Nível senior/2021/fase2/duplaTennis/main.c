#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define _TAM 4


void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sortArr(int arr[], int length){
    bool ordenou = false;
    while(!ordenou){
        int c = 0;
        for(int i = 0; i < length - 1; i++){
            if(arr[i] > arr[i + 1]){
                swap(&arr[i], &arr[i + 1]);
            }else{
                c++;
            }
        }
        if(c == (length - 1)){
            ordenou = true;
        }
    }
}

int menorDiferenca(int niveis[]){
    sortArr(niveis, _TAM);
    int diferenca = niveis[0] + niveis[3] - niveis[1] - niveis[2];
    if(diferenca < 0)diferenca *= -1;
    return diferenca;
}

void lerArr(int arr[], int qnt){
    for(int i = 0; i < qnt; i++){
        scanf("%d", &arr[i]);
    }
}

int main()
{
    int niveis[_TAM];
    lerArr(niveis, _TAM);
    printf("%d", menorDiferenca(niveis));
    return 0;
}
