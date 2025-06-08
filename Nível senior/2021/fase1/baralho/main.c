#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define _MAX 157 //52 * 3 + 1

int strToInt(char str[]){
    int num = 0;
    int i = 0;
    while(str[i] != '\0'){
        num *= 10;
        num+= (int)(str[i] - '0');
        i++;
    }
    return num;
}
void fill(bool vetor[], int lenght, bool value){
    for(int i = 0; i < lenght; i++){
        vetor[i] = value;
    }
}

void checarBaralho(char baralho[]){
    bool copas[13]; fill(copas, 13, false);
    bool espadas[13]; fill(espadas, 13, false);
    bool ouros[13]; fill(ouros, 13, false);
    bool paus[13]; fill(paus, 13, false);

    int qntCopasFaltante = 13;
    int qntEspadasFaltante = 13;
    int qntOurosFaltante = 13;
    int qntPausFaltante = 13;

    int lenBaralho = strlen(baralho);
    if(lenBaralho % 3 == 0){
        for(int i = 0; i < lenBaralho; i += 3){
            char strNum[3];
            sprintf(strNum, "%c%c", baralho[i], baralho[i+1]);
            int num = strToInt(strNum);
            switch(baralho[i+2]){
                case 'C':
                    if(qntCopasFaltante != -1){
                        if(!copas[num - 1]){
                            copas[num - 1] = true;
                            qntCopasFaltante--;
                        }else{
                            qntCopasFaltante = -1;
                        }
                    }
                    break;
                case 'E':
                    if(qntEspadasFaltante != -1){
                        if(!espadas[num - 1]){
                            espadas[num - 1] = true;
                            qntEspadasFaltante--;
                        }else{
                            qntEspadasFaltante = -1;
                        }
                    }
                    break;
                case 'U':
                    if(qntOurosFaltante != -1){
                        if(!ouros[num - 1]){
                            ouros[num - 1] = true;
                            qntOurosFaltante--;
                        }else{
                            qntOurosFaltante = -1;
                        }
                    }
                    break;
                case 'P':
                    if(qntPausFaltante != -1){
                        if(!paus[num - 1]){
                            paus[num - 1] = true;
                            qntPausFaltante--;
                        }else{
                            qntPausFaltante = -1;
                        }
                    }
                    break;
            }

        }


        if(qntCopasFaltante == -1)printf("erro\n");
        else                      printf("%d\n", qntCopasFaltante);

        if(qntEspadasFaltante == -1)printf("erro\n");
        else                        printf("%d\n", qntEspadasFaltante);

        if(qntOurosFaltante == -1)printf("erro\n");
        else                      printf("%d\n", qntOurosFaltante);

        if(qntPausFaltante == -1)printf("erro\n");
        else                     printf("%d\n", qntPausFaltante);


    }else{
        printf("Baralho invalido");
    }
}




int main()
{
    char baralho[_MAX];
    scanf("%s", baralho);
    checarBaralho(baralho);
    return 0;
}
