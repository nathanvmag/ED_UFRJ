#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;
 
 struct no {
    int chave;
    no* esquerda;
    no* direira;

};
void adicona(no* &topo,int novachave)
{
    if(topo==NULL)
    {
        printf("eai");
        topo= (no*)malloc(sizeof(no));
        topo->chave=novachave;
        printf("addes");
    }
    else {
        printf("Aq89");
        if(novachave<=topo->chave)
        {
            adicona(topo->esquerda,novachave);
        }else{
            adicona(topo->direira,novachave);

        }
    }
}
void imprime(no* meuno)
{
    if(meuno!=NULL)
    {
        imprime(meuno->esquerda);
        printf("%d",meuno->chave);
        imprime(meuno->direira);

    }

}
int main ()
{
    no* raiz = (no*)malloc(sizeof(no));
    raiz->chave=10;
    printf("ahhhh");
    adicona(raiz,20);
    adicona(raiz,14);
    adicona(raiz,40);
    printf("eai");
    imprime(raiz);


    return 0;
}
