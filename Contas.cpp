#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

char** alocar(char** array,int newsize)
{
    char** temparray= array;
    array= (char**) malloc (newsize*sizeof(char*));
    for(int i=0;i<newsize;i++)array[i]= (char*)malloc (25*sizeof(char));
    if(newsize!=8)
    for(int i=0;i<newsize/2;i++)
    {
        strcpy(array[i],temparray[i]);
    }
    //free(temparray);
    return array;
}
int main ()
{
    char ** palavras;
    int qntpalavras=0;
    int arraysize=8;
    palavras= alocar(palavras,arraysize);


    while (!feof(stdin) ) {
    char palavra[25];
    if ( scanf("%s", palavra) == 1 ) {
        if(qntpalavras==arraysize)
        {
            arraysize*=2;
            palavras= alocar(palavras,arraysize);
        }
        //printf("Li uma palavra: %s\n", palavra); // trate aqui as palavras.
        strcpy(palavras[qntpalavras],palavra);
        qntpalavras++;

    } 
}


 //   printf("%d\n",qntpalavras);


    for(int i=0;i<qntpalavras;i++){
        for(int j=i+1;j<qntpalavras;j++){
            int lpala1= (int) palavras[i][0];
            int lpala2= (int) palavras[j][0];
            int cont=0;
            while(lpala1==lpala2)
            {
                cont++;
                lpala1= (int) palavras[i][cont];
                lpala2= (int) palavras[j][cont];
            }
            if(lpala1>lpala2)
            {
                char temp[50];
                strcpy(temp,palavras[i]);
                strcpy(palavras[i],palavras[j]);
                strcpy(palavras[j],temp);
            }
        }
    }

    char ultima[25]="";
      for(int i=0;i<qntpalavras;i++)
    {
        int count=0;
        int nexti=0;
        if(strcmp(ultima,palavras[i])==0)continue;

        for(int j=i;j<qntpalavras;j++){
            if(strcmp(palavras[i],palavras[j])==0)
                count++;   
            else {
                    break;
                }             
            // printf("palabra %d %s terminou\n",i,palavras[i]);
        }
        printf("%s - %d\n",palavras[i],count);
        strcpy(ultima,palavras[i]);

    }
    free(palavras);
    return 0;
}
