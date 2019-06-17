#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std; 
  
enum COLOR { R, B }; 
  
class no { 
public: 
  int chave; 
  COLOR cor; 
  no *esquerda, *direita, *pai; 
  
  no(int chave) : chave(chave) { 
    pai = esquerda = direita = NULL;       
    cor = R; 
  } 
  
  no *tio() { 
    if (pai == NULL or pai->pai == NULL) 
      return NULL; 
  
    if (pai->checkesquerda()) 
      return pai->pai->direita; 
    else
      return pai->pai->esquerda; 
  } 
  char getColor(){
      switch (cor)
      {
      case R:
        return 'R';
          break;
      case B:
        return 'N';
          break;
      
      
      default:
      return ' ';
          break;
      }
  }

  bool checkesquerda() { return this == pai->esquerda; } 
  
  no *irmao() { 
    if (pai == NULL) 
      return NULL;   
    if (checkesquerda()) 
      return pai->direita;   
    return pai->esquerda; 
  }   
  void auxRotation(no *npai) { 
    if (pai != NULL) { 
      if (checkesquerda()) { 
        pai->esquerda = npai; 
      } else { 
        pai->direita = npai; 
      } 
    } 
    npai->pai = pai; 
    pai = npai; 
  } 
  
  bool checkfilho() { 
    return (esquerda != NULL and esquerda->cor == R) or 
           (direita != NULL and direita->cor == R); 
  } 
}; 
  
class arvore { 
  no *raiz; 
  
  void rotsimplesesq(no *x) { 
    no *npai = x->direita;   
    if (x == raiz) 
      raiz = npai;   
    x->auxRotation(npai);   
    x->direita = npai->esquerda;    
    if (npai->esquerda != NULL) 
      npai->esquerda->pai = x;   
    npai->esquerda = x; 
  } 
  
  void rotsimpledir(no *x) { 
    no *npai = x->esquerda;   
    if (x == raiz) 
      raiz = npai; 
  
    x->auxRotation(npai);   
    x->esquerda = npai->direita; 
    if (npai->direita != NULL) 
      npai->direita->pai = x;   
    npai->direita = x; 
  } 
  
  void trocacor(no *x1, no *x2) { 
    COLOR temp; 
    temp = x1->cor; 
    x1->cor = x2->cor; 
    x2->cor = temp; 
  } 
  
  void trocachave(no *u, no *v) { 
    int temp; 
    temp = u->chave; 
    u->chave = v->chave; 
    v->chave = temp; 
  } 
  
  void Balanceia(no *x) { 
    if (x == raiz) { 
      x->cor = B; 
      return; 
    } 
  
    no *pai = x->pai; 
    no*avo = pai->pai;
    no*tio = x->tio(); 
  
    if (pai->cor != B) { 
      if (tio != NULL && tio->cor == R) { 
        pai->cor = B; 
        tio->cor = B; 
        avo->cor = R; 
        Balanceia(avo); 
      } else { 
        if (pai->checkesquerda()) { 
          if (x->checkesquerda()) { 
            trocacor(pai, avo); 
          } else { 
            rotsimplesesq(pai); 
            trocacor(x, avo); 
          } 
          rotsimpledir(avo); 
        } else { 
          if (x->checkesquerda()) { 
            rotsimpledir(pai); 
            trocacor(x, avo); 
          } else { 
            trocacor(pai, avo); 
          }   
          rotsimplesesq(avo); 
        } 
      } 
    } 
  }  
  
  void PretoFix(no *x) { 
    if (x == raiz) 
      return; 
  
    no *irmao = x->irmao();
    no *pai = x->pai; 
    if (irmao == NULL) { 
      PretoFix(pai); 
    } else { 
      if (irmao->cor == R) { 
        pai->cor = R; 
        irmao->cor = B; 
        if (irmao->checkesquerda()) { 
          rotsimpledir(pai); 
        } else { 
          rotsimplesesq(pai); 
        } 
        PretoFix(x); 
      } else { 
        if (irmao->checkfilho()) { 
          if (irmao->esquerda != NULL and irmao->esquerda->cor == R) { 
            if (irmao->checkesquerda()) { 
              irmao->esquerda->cor = irmao->cor; 
              irmao->cor = pai->cor; 
              rotsimpledir(pai); 
            } else { 
              irmao->esquerda->cor = pai->cor; 
              rotsimpledir(irmao); 
              rotsimplesesq(pai); 
            } 
          } else { 
            if (irmao->checkesquerda()) { 
              irmao->direita->cor = pai->cor; 
              rotsimplesesq(irmao); 
              rotsimpledir(pai); 
            } else { 
              irmao->direita->cor = irmao->cor; 
              irmao->cor = pai->cor; 
              rotsimplesesq(pai); 
            } 
          } 
          pai->cor = B; 
        } else { 
          irmao->cor = R; 
          if (pai->cor == B) 
            PretoFix(pai); 
          else
            pai->cor = B; 
        } 
      } 
    } 
  } 
  
  
public: 
  arvore() { raiz = NULL; }   
  no* getraiz(){return raiz;}
  
  no *procura(int n) { 
    // usar iteracao para nao quebrar o código
    no *temp = raiz; 
    while (temp != NULL) { 
      if (n < temp->chave) { 
        if (temp->esquerda == NULL) 
          break; 
        else
          temp = temp->esquerda; 
      } else if (n == temp->chave) { 
        break; 
      } else { 
        if (temp->direita == NULL) 
          break; 
        else
          temp = temp->direita; 
      } 
    } 
  
    return temp; 
  } 
  // adiciona 
  void adiciona(int n) { 
    no *novoNo = new no(n); 
    if (raiz == NULL) { 
     
      novoNo->cor = B; 
      raiz = novoNo; 
    } else { 
      no *temp = procura(n);
      if (temp->chave == n) { 
        return; 
      }       
      novoNo->pai = temp;   
      if (n < temp->chave) 
        temp->esquerda = novoNo; 
      else
        temp->direita = novoNo; 
  
      Balanceia(novoNo); 
    } 
  }  
  
}; 
void printarvore(no* pai)
{
    if(pai!=NULL)
    {
        printf("%d%c\n",pai->chave,pai->getColor());
        printarvore(pai->esquerda);
        printarvore(pai->direita);
        
    }
}
  
int main() { 
  
  arvore arv ;
    while (!feof(stdin) ) {
	int leitura;
    if ( scanf("%d", &leitura) == 1) {
            arv.adiciona(leitura);          		
        }        
    }
    printarvore(arv.getraiz());

  
  return 0; 
} 