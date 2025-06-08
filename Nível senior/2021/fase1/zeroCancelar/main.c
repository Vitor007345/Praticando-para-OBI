#include <stdio.h>
#include <stdlib.h>

#define _TAXAVECTOR 2

typedef struct{
    int capacity;
    int length;
    int* v;
}vectorInt;

vectorInt createVectorInt(int capacity);
void destroyVectorInt(vectorInt* v);
void pushInVectorInt(vectorInt* v, int newValue);
int popInVectorInt(vectorInt* v);
void lerNumerosDoChefe(vectorInt* v, int qnt);
int somaVectorInt(vectorInt v);

int main(){
    int qntDeNum;
    scanf("%d", &qntDeNum);
    vectorInt numerosDoChefe = createVectorInt(qntDeNum);
    lerNumerosDoChefe(&numerosDoChefe, qntDeNum);
    printf("%d", somaVectorInt(numerosDoChefe));
    destroyVectorInt(&numerosDoChefe);
    return 0;
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
    if(v->length >= v->capacity){
        int newCapacity = v->capacity == 0? 1 : (v->capacity * _TAXAVECTOR);
        int* temp = realloc(v->v, newCapacity * sizeof(int));
        if(temp){
            v->v = temp;
            v->capacity = newCapacity;
            v->v[v->length] = newValue;
            v->length++;
        }else{
            printf("Erro na realocação");
        }

    }else{
        v->v[v->length] = newValue;
        v->length++;
    }
}

int popInVectorInt(vectorInt* v){
    int lastValue = -1;
    if(v->length != 0){
        v->length--;
        lastValue = v->v[v->length];
        if(v->length * _TAXAVECTOR < v->capacity){
            int newCapacity = v->length == 0? 1 : v->length;
            int* temp = realloc(v->v, newCapacity * sizeof(int));
            if(temp){
                v->v = temp;
                v->capacity = newCapacity;
            }else{
                printf("Erro na realocação");
            }
        }
    }
    return lastValue;
}

void lerNumerosDoChefe(vectorInt* v, int qnt){
    for(int i = 0; i < qnt; i++){
        int valor;
        scanf("%d", &valor);
        if(valor == 0){
            popInVectorInt(v);
        }else{
            pushInVectorInt(v, valor);
        }
    }
}

int somaVectorInt(vectorInt v){
    int soma = 0;
    for(int i = 0; i < v.length; i++){
        soma += v.v[i];
    }
    return soma;
}
