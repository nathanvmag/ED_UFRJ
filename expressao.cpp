#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

char** alocar(char** array,int newsize)
{
    char** temparray= array;
    array= (char**) malloc (newsize*sizeof(char*));
    for(int i=0;i<newsize;i++)array[i]= (char*)malloc (10*sizeof(char));
    if(newsize!=8)
    for(int i=0;i<newsize/2;i++)
    {
        strcpy(array[i],temparray[i]);
    }
    //free(temparray);
    return array;
}
void adiciona(char ** &pilha,int &ultposi,char* valor,int &arraysize)
{
    if(ultposi==-1)
    {
        pilha= alocar(pilha,arraysize);
        ultposi++;
    }
    if(ultposi==arraysize)
    {
        arraysize*=2;
        pilha= alocar(pilha,arraysize);

    }
    strcpy(pilha[ultposi],valor);
    ultposi++;
  
    
}
char* desempilha (char ** pilha, int &topo)
{
    if(topo>0)
    {
        topo--;
        return pilha[topo];
    }
    return NULL;


}
int main ()
{
    char ** operadores;
    int topo=-1;
    int arraysize=8;
    //operadores= alocar(operadores,arraysize);
    int resultado=0;
    while (!feof(stdin) ) {
    char* palavra = (char*) malloc(sizeof(char)*1);
	char leitura;
    if ( scanf("%c", &leitura) == 1 &&leitura!=' '&&leitura!='\n') {
		palavra[0]=leitura;
		palavra[1]='\0';
		//printf("leu %s\n",palavra);
        if(strcmp(palavra,")")==0)
        {
           // printf("Achou um )\n");
            char* desen;
            //while(strcmp(desen=desempilha(operadores,topo),"(")!=0){
                    desen= desempilha(operadores,topo);             
                    double operador1= atof(desen);
                    char op= desempilha(operadores,topo)[0];
                    double auxiliar= atof(desempilha(operadores,topo));
                    double resultado=0;
                    desempilha(operadores,topo);
                    //printf("Opercao %.2f %c %.2f \n", auxiliar,op,operador1);
                    switch (op)
                    {
                        case '+':
                            /* code */
                            resultado =auxiliar+ operador1;                            
                            break;
                        case '-':
                        
                            resultado = auxiliar- operador1;                            
                            /* code */
                            break;
                        case '*':                               
                            resultado = auxiliar* operador1;                            
                            /* code */
                            break;
                        case '/':                        
                            resultado =auxiliar/ operador1;                            
                            /* code */
                            break;                    
                    }
                   // printf("vai converter o resultado %f",resultado);

                    char temp [10];
                    snprintf(temp,10,"%f",resultado);
                    //printf("converteu pefeito\n");
                    adiciona(operadores,topo,temp,arraysize);
                   // printf("resultado %s\n", temp);
              
                //}
		
        }else
        adiciona(operadores,topo,palavra,arraysize);
		free(palavra);

    }
}

    printf("%.0f",atof(desempilha(operadores,topo))); 


    return 0;
}
