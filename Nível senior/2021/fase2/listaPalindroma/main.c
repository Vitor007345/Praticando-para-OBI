#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define _TAXAVECTOR_CRESCIMENTO 2
#define _TAXEVECTOR_DECRESCIMENTO 4

typedef struct{
    int capacity;
    int length;
    int* v;
}vectorInt;

vectorInt createVectorInt(int capacity);
void destroyVectorInt(vectorInt* v);
void pushInVectorInt(vectorInt* v, int newValue);
int popInVectorInt(vectorInt* v);
int resizeVector(vectorInt* v);
void swap(int* a, int*b);
void shiftMenosX(vectorInt* v, int index, int X);
int somaArrDeIndexAoutro(vectorInt v, int index1, int index2);
int contracao(vectorInt* v, int index1, int index2, int* valorSoma);
void printVectorInt(vectorInt v);
int numContracoesAtePalindromo(vectorInt* v);
void lerVectorInt(vectorInt* v, int qnt);



int main()
{
    int qnt;
    scanf("%d", &qnt);
    vectorInt v = createVectorInt(qnt);
    lerVectorInt(&v, qnt);
    printf("%d\n", numContracoesAtePalindromo(&v));
    printVectorInt(v);



    return 0;
}

void swap(int* a, int*b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

vectorInt createVectorInt(int capacity){
    vectorInt v;
    v.capacity = 0;
    v.length = 0;
    v.v = NULL;
    if(capacity > 0){
        v.v = (int*)malloc(capacity * sizeof(int));
        if(v.v != NULL){
            v.capacity = capacity;
        }else{
            printf("Erro na alocação");
        }
    }
    return v;
}

void destroyVectorInt(vectorInt* v){
    free(v->v);
    v->v = NULL;
    v->capacity = 0;
    v->length = 0;
}

void pushInVectorInt(vectorInt* v, int newValue){
    int status = 0;
    if(v->length >= v->capacity){
        status = resizeVector(v);
    }
    if(status == 0 || status == 1){
        v->v[v->length] = newValue;
        v->length++;
    }else{
        printf("Erro na realocação");
    }
}

int popInVectorInt(vectorInt* v){
    int lastValue = -1;
    if(v->length != 0){
        v->length--;
        lastValue = v->v[v->length];
        if((v->length * _TAXEVECTOR_DECRESCIMENTO < v->capacity)){
            resizeVector(v);
        }
    }
    return lastValue;
}

int resizeVector(vectorInt* v){
    int status = 0; //não foi necessraio

    int newCapacity = v->capacity;

    if(v->length >= v->capacity){
        newCapacity = v->capacity? (v->capacity * _TAXAVECTOR_CRESCIMENTO) : 1;
    }else if(v->length * _TAXEVECTOR_DECRESCIMENTO < v->capacity){
        newCapacity = v->length? v->length : 1;
    }

    if(newCapacity != v->capacity){
        int* temp = realloc(v->v, newCapacity * sizeof(int));
        if(temp){
            v->v = temp;
            v->capacity = newCapacity;
            status = 1; //sucesso
        }else{
            status = -1; //erro
        }
    }

    return status;
}

void printVectorInt(vectorInt v){
    for(int i = 0; i < v.length; i++){
        printf("-%d-", v.v[i]);
    }
    printf("\n");
}

void lerVectorInt(vectorInt* v, int qnt){
    for(int i = 0; i < qnt; i++){
        int valor;
        scanf("%d", &valor);
        pushInVectorInt(v, valor);
    }
}

void shiftMenosX(vectorInt* v, int index, int X){
    if(v->length != 0 && index >= 0 && X > 0 && index + X <= v->length){
        for(int i = index; i < v->length - X; i++){
            v->v[i] = v->v[i + X];
        }
        v->length -= X;
        resizeVector(v);
    }

}

int somaArrDeIndexAoutro(vectorInt v, int index1, int index2){
    int soma = 0;
    if(v.length != 0){
        if(index1 > index2)swap(&index1, &index2);
        if(index1 < 0)index1 = 0;
        if(index2 >= v.length) index2 = v.length - 1;
        for(int i = index1; i <= index2; i++){
            soma += v.v[i];
        }
    }
    return soma;
}

int contracao(vectorInt* v, int index1, int index2, int* valorSoma){
    int numContracoes = 0;
    if(v->length != 0 && index1 < index2){
        int soma;
        if(valorSoma == NULL){
            soma = somaArrDeIndexAoutro(*v, index1, index2);
        }else{
            soma = *valorSoma;
        }
        numContracoes = index2 - index1;
        v->v[index1] = soma;
        shiftMenosX(v, index1 + 1, numContracoes);
    }
    return numContracoes;
}



void corrigirValores(vectorInt* v, int i, int j, int backupI, int backupJ, int first, int last, char letraAtestar, int* numContracoes){
    printf("i:%d -- j:%d -- backupI:%d -- backupJ:%d -- first:%d -- last:%d -- letra:%c\n", i, j, backupI, backupJ, first, last, letraAtestar);
    int soma1 = somaArrDeIndexAoutro(*v, first, i);
    int soma2 = somaArrDeIndexAoutro(*v, j, last);
    printf("soma1:%d -- soma2:%d\n", soma1, soma2);
    //printf("soma1: %d   ----  soma2: %d\n", soma1, soma2);
    if(soma1 != soma2){
        if(letraAtestar == 'i'){
            if(soma1 < soma2 && ((i + 1) < j)){
                corrigirValores(v, i + 1, j, backupI, backupJ, first, last, 'i', numContracoes);
            }else{
                corrigirValores(v, backupI, j - 1, backupI, backupJ, first, last, 'j', numContracoes);
            }
        }else if(letraAtestar == 'j'){
            if(soma1 > soma2 && ((j - 1) > i)){
                corrigirValores(v, i, j - 1, backupI, backupJ, first, last, 'j', numContracoes);
            }else{
                if(i + 1 < backupJ - 1){
                    corrigirValores(v, i + 1, backupJ - 1, (backupI + 1), (backupJ - 1), first, last, 'i', numContracoes);
                }else{
                    *numContracoes += contracao(v, first, last, NULL);
                    printf("numContracoesAqui: %d\n", *numContracoes);
                }

            }
        }

    }else{
        int contracao1 = contracao(v, first, i, &soma1);
        int contracao2 = contracao(v, j - contracao1, last - contracao1, &soma2);
        *numContracoes += contracao1 + contracao2;
        printf("numContracoes: %d\n", *numContracoes);
    }


}



int numContracoesAtePalindromo(vectorInt* v){
    int numContracoes = 0;

    for(int i = 0, j = v->length - 1; i < j; i++, j--){
        if(v->v[i] != v->v[j]){
            corrigirValores(v, i, j, i, j, i, j, 'i', &numContracoes);
            j -= numContracoes;
        }

    }

    return numContracoes;

}




