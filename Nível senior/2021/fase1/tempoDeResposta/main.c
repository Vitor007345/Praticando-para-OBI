#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAXA_CRESCIMENTO 2
typedef struct{
    char metodo;
    int amigo;
}Registro;

typedef struct{
    int size;
    int length;
    Registro* v;
}vectorR;

typedef struct{
    int amigo;
    int tempo;
    char lastMetodo;
    bool somarTempo;
}TempoResposta;

typedef struct{
    int size;
    int length;
    TempoResposta* v;
}vectorT;

vectorR createVectorR(int size){
    vectorR v;
    v.size = size;
    v.length = 0;
    v.v = NULL;
    if(size > 0){
        v.v = (Registro*)malloc(size * sizeof(Registro));
        if(!v.v){
            v.size = 0;
            printf("Falha na criacao do vetor");
        }
    }
    return v;
}

vectorT createVectorT(int size){
    vectorT v;
    v.size = size;
    v.length = 0;
    v.v = NULL;
    if(size > 0){
        v.v = (TempoResposta*)malloc(size * sizeof(TempoResposta));
        if(!v.v){
            v.size = 0;
            printf("Falha na criacao do vetor");
        }
    }
    return v;
}

void pushInVectorR(vectorR* v, Registro r){
    if(v->length >= v->size){
        int newSize = v->size == 0 ? 1: v->size * TAXA_CRESCIMENTO;
        Registro* temp = (Registro*)realloc(v->v, newSize * sizeof(Registro));
        if(temp){
            v->v = temp;
            v->size = newSize;
            v->v[v->length] = r;
            v->length++;
        }else{
            printf("Erro na realocação do push");
        }
    }else{
        v->v[v->length] = r;
        v->length++;
    }
}

void pushInVectorT(vectorT* v, TempoResposta t){
    if(v->length >= v->size){
        int newSize = v->size == 0 ? 1: v->size * TAXA_CRESCIMENTO;
        TempoResposta* temp = (TempoResposta*)realloc(v->v, newSize * sizeof(TempoResposta));
        if(temp){
            v->v = temp;
            v->size = newSize;
            v->v[v->length] = t;
            v->length++;
        }else{
            printf("Erro na realocação do push");
        }
    }else{
        v->v[v->length] = t;
        v->length++;
    }


}

Registro lerRegistro(){
    Registro registro;
    scanf(" %c", &registro.metodo);
    scanf("%d", &registro.amigo);
    return registro;
}
void printRegistro(Registro r){
    printf("%c %d\n", r.metodo, r.amigo);
}

void lerRegistros(vectorR* registros, int qnt){
    for(int i = 0; i< qnt; i++){
        pushInVectorR(registros, lerRegistro());
    }
}

TempoResposta* findPorAmigo(vectorT* temposDeResposta, int amigo){
    int i = 0;
    while(i < temposDeResposta->length && temposDeResposta->v[i].amigo != amigo){
        i++;
    }
    return (i<temposDeResposta->length)? &temposDeResposta->v[i]: NULL;
}

vectorT temposDeResposta(vectorR registros){
    vectorT temposResposta = createVectorT(registros.size);
    for(int i = 0; i < registros.length; i++){
        if(i > 0){
            for(int j = 0; j < temposResposta.length; j++){
                if(temposResposta.v[j].somarTempo && temposResposta.v[j].tempo != -1){
                    temposResposta.v[j].tempo++;
                }
            }
        }
        switch(registros.v[i].metodo){
            case 'R':{
                TempoResposta* T = findPorAmigo(&temposResposta, registros.v[i].amigo);
                if(T){
                    if(T->lastMetodo == 'E'){
                        T->somarTempo = true;
                        T->lastMetodo = 'R';

                    }else{
                        T->tempo = -1;
                        T->somarTempo = false;
                    }
                }else{
                    TempoResposta newT;
                    newT.amigo = registros.v[i].amigo;
                    newT.tempo = 0;
                    newT.lastMetodo = 'R';
                    newT.somarTempo = true;
                    pushInVectorT(&temposResposta, newT);
                }

                break;
            }
            case 'E':{
                TempoResposta* T = findPorAmigo(&temposResposta, registros.v[i].amigo);
                if(T){
                    T->somarTempo = false;
                    if(T->lastMetodo == 'R'){
                        T->lastMetodo = 'E';
                    }else{
                        T->tempo = -1;
                    }
                }else{
                    TempoResposta newT;
                    newT.amigo = registros.v[i].amigo;
                    newT.tempo = -1;
                    newT.lastMetodo = 'E';
                    newT.somarTempo = false;
                    pushInVectorT(&temposResposta, newT);
                }
                break;
            }
            case 'T':{
                for(int j = 0; j < temposResposta.length; j++){
                    if(temposResposta.v[j].somarTempo && temposResposta.v[j].tempo != -1){
                        temposResposta.v[j].tempo += registros.v[i].amigo - 2;
                    }
                }
                break;
            }

        }
    }
    for(int i = 0; i< temposResposta.length; i++){
        if(temposResposta.v[i].lastMetodo == 'R'){
            temposResposta.v[i].tempo = -1;
        }
    }
    return temposResposta;
}
void printTempoResposta(TempoResposta t){
    printf("%d %d\n", t.amigo, t.tempo);
}

void escreveTemposDeResposta(vectorT temposResposta){
    for(int i = 0; i < temposResposta.length; i++){
        printTempoResposta(temposResposta.v[i]);
    }
}
void swap(TempoResposta* a, TempoResposta* b){
    TempoResposta temp = *a;
    *a = *b;
    *b = temp;
}
sortVectorT(vectorT v){
    bool ordenou = false;
    while(!ordenou){
        int c = 0;
        for(int i = 0; i < v.length - 1; i++){
            if(v.v[i].amigo > v.v[i + 1].amigo){
                swap(&v.v[i], &v.v[i + 1]);
            }else{
                c++;
            }
        }
        if(c == (v.length - 1))ordenou = true;
    }


}
int main()
{
    int qntRegistro;
    scanf("%d", &qntRegistro);
    vectorR registros = createVectorR(qntRegistro);
    lerRegistros(&registros, qntRegistro);

    vectorT temposResposta = temposDeResposta(registros);
    sortVectorT(temposResposta);
    escreveTemposDeResposta(temposResposta);


    return 0;
}
