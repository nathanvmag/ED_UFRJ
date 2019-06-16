#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

     struct no
{
    int chave,altura,balanceamento;
    no* direita;
    no* esquerda;
    no* parent;
    char color;
};
int getAltura(no* pai);
no* adiciona (no* &pai,int chave);
void printarvore(no* pai);
int max(int i1,int i2);
int getBalancemento(no* pai);
no* rotsimplesesq(no* pai);
void rotduplaesq(no* &pai);
void rotdupladir(no* &pai);
void balanceia(no* &pai);
void updatePais(no* &raiz);
void updatepais2(no* &raiz,no* pai);
void colore(no* &raiz);
no *getavo(no *n);
no *gettio(no *n);
no* encontra(no* raiz,int chave);
void manageRot(no* &pai);

no* rotsimpledir(no* &pai)
{
    no* temp;

    temp = pai->esquerda;
    pai->esquerda = temp->direita != NULL ? temp->direita : NULL;
    temp->direita = pai;
    balanceia(pai);
    return temp;
 
}
void updatePais(no* &raiz)
{
    raiz->parent=NULL;
    updatepais2(raiz->esquerda,raiz);
    updatepais2(raiz->direita,raiz);
}
void updatepais2(no* &raiz,no* pai)
{
    if(raiz!=NULL)
    {
        raiz->parent=pai; 
        raiz->color=raiz->parent->color=='R'?'N':raiz->color;       
        updatepais2(raiz->esquerda,raiz);
        updatepais2(raiz->direita,raiz);
    }
}
void colore(no* &raiz)
{
    if(raiz!=NULL)
    {
        if(raiz->parent==NULL){
           // printf("cheguei caso 1 \n");
            raiz->color='N';
            }
        else if(raiz->parent->color=='N')
        {            
            //printf("cheguei caso 2 \n");
            return;
        }
        else {
            //printf("cheguei caso 3 \n");
            no* tio = gettio(raiz);
            no* avo;
            if(tio!=NULL &&tio->color=='R')
            {
              //  printf("cheguei caso 4 \n");
                raiz->parent->color='N';
                tio->color='P';
                avo=getavo(raiz);
                avo->color='R';                
                colore(avo);
            }
            else {
                
                //printf("cheguei caso 5 \n");
                avo= getavo(raiz); 
                if((raiz==raiz->parent->direita &&raiz->parent==avo->esquerda))
                {
                    //printf("tentei rot 1");
                    manageRot(raiz->parent);
                }
                else if((raiz==raiz->parent->esquerda &&raiz->parent==avo->direita))
                {
                    
                  //  printf("tentei rot 2");                  
                    manageRot(raiz->parent);
                }
                avo= getavo(raiz);                
                //printf("cheguei caso 6\n");
                if(avo!=NULL){
                raiz->parent->color='N';
                avo->color='R';
                if(raiz==raiz->parent->esquerda&& raiz->parent==avo->esquerda)
                {
                    avo=rotsimpledir(avo);
                }else if(raiz==raiz->parent->direita&& raiz->parent==avo->direita)
                {
                    avo= rotsimplesesq(avo);
                }}
                }
            
        }



    }
}

no* adiciona (no* &pai,int chave)
{
    no* adicionado;
    if(pai==NULL)
    {
        pai= (no*) malloc(sizeof(struct no));
        pai->chave=chave;
        pai->esquerda=NULL;
        pai->direita=NULL;
        pai->color='R';
    }
    else if(pai->chave>=chave)
    {
        adiciona(pai->esquerda,chave);

    }else adiciona(pai->direita,chave);
    manageRot(pai);       

   
        
}
void manageRot(no* &pai)
{
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
no* encontra(no* raiz,int chave)
{
    if(raiz!=NULL)
    {
        if(raiz->chave==chave)
        return raiz;
        else{
            no* encontrado = encontra(raiz->esquerda,chave);
            if(encontrado==NULL)encontrado= encontra(raiz->direita,chave);
            return encontrado;
                    }
    }else 
    return NULL;
}
void encontraPai(no* &filho,no* rz)
{
   
}
void rotduplaesq(no* &pai)
{
   //pai->direita=rotsimpledir(pai->direita);
   pai= rotsimplesesq(pai);
}
void rotdupladir(no* &pai)
{
   //pai->esquerda= rotsimplesesq(pai->esquerda);
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
        pai->parent=NULL;

    }
}
no *getavo(no *n)
{
	if ((n != NULL) && (n->parent != NULL))
		return n->parent->parent;
	else
		return NULL;
}

no *gettio(no *n)
{
	no *g = getavo(n);
	if (g == NULL)
		return NULL; 
	if (n->parent == g->esquerda)
		return g->direita;
	else
		return g->esquerda;
}
void printarvore(no* pai)
{
    if(pai!=NULL)
    {
        printf("%d%c\n",pai->chave,pai->color);

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
            no* adicionado= encontra(raiz,leitura);  
            updatePais(raiz);  
            //printf("Adicionado %d\n",adicionado->chave);
            colore(raiz);  

        }        
    }
    printarvore(raiz);


  

    return 0;
}
