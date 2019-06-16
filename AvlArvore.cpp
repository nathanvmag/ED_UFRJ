#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

     struct no
{
    int chave,altura,balanceamento;
    no* direita;
    no* esquerda;
};
int getAltura(no* pai);
void adiciona (no* &pai,int chave);
void printarvore(no* pai);
int max(int i1,int i2);
int getBalancemento(no* pai);
no* rotsimplesesq(no* pai);
void rotduplaesq(no* &pai);
void rotdupladir(no* &pai);
void balanceia(no* &pai);

no* rotsimpledir(no* &pai)
{
    no* temp;

    temp = pai->esquerda;
    pai->esquerda = temp->direita != NULL ? temp->direita : NULL;
    temp->direita = pai;
    balanceia(pai);
    return temp;
 
}
void adiciona (no* &pai,int chave)
{
    if(pai==NULL)
    {
        pai= (no*) malloc(sizeof(struct no));
        pai->chave=chave;
        pai->esquerda=NULL;
        pai->direita=NULL;
    }
    else if(pai->chave>=chave)
    {
        adiciona(pai->esquerda,chave);

    }else adiciona(pai->direita,chave);
    pai->altura= getAltura(pai);
    pai->balanceamento= getBalancemento(pai);
    if(pai->balanceamento<-1||pai->balanceamento>1)
    {
        //printf("ta desbalanceado %d \n",pai->chave);
        if(pai->balanceamento<0)
        {
            //rot esq
            if(pai->direita->balanceamento<0)
            {
                pai=  rotsimplesesq(pai);
            }
            else 
            { 
                rotduplaesq(pai);
               // printf("Precisa de uma rotacao dupla esq\n");

            }
        }else{
            // rot dir
            if(pai->esquerda->balanceamento>0)
            {
                // 
                pai=rotsimpledir(pai);
               // printf("precisa de uma rot dir\n");
            }
            else //{
                //rot dupla dir
                rotdupladir(pai);
            }
        }
        pai->balanceamento=getBalancemento(pai);
    
}
no* rotsimplesesq(no* pai)
{
 
      no* temp;

      temp = pai->direita;
      pai->direita = temp->esquerda != NULL ? temp->esquerda : NULL;
      temp->esquerda = pai;
      balanceia(pai);
    return temp;

  

}
void rotduplaesq(no* &pai)
{
   pai->direita=rotsimpledir(pai->direita);
   pai= rotsimplesesq(pai);
}
void rotdupladir(no* &pai)
{
   pai->esquerda= rotsimplesesq(pai->esquerda);
   pai= rotsimpledir(pai);
   
   
}
void balanceia(no* &pai)
{
    if (pai!=NULL)
    {
        balanceia(pai->esquerda);
        pai->altura= getAltura(pai);
        pai->balanceamento= getBalancemento(pai);
        balanceia(pai->direita);

    }
}

void printarvore(no* pai)
{
    if(pai!=NULL)
    {
        printf("%d\n",pai->chave);

        printarvore(pai->esquerda);

        printarvore(pai->direita);
        
    }
}
int max(int i1,int i2)
{
    return i1>i2?i1:i2;
}
int getAltura(no* pai)
{
    int h1,h2;
    if(pai->direita!=NULL)h1=getAltura(pai->direita);
    else h1=0;
    if(pai->esquerda!=NULL)h2=getAltura(pai->esquerda);
    else h2=0;
    return 1+ max(h1,h2);
}
int getBalancemento(no* pai)
{
    return (pai->esquerda!=NULL?pai->esquerda->altura:0)-(pai->direita!=NULL?pai->direita->altura:0);
}


int main ()
{
    no* raiz =NULL;
    while (!feof(stdin) ) {
	int leitura;
    if ( scanf("%d", &leitura) == 1) {
            adiciona(raiz,leitura);            		
        }        
    }
    printarvore(raiz);


  

    return 0;
}
