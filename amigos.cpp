#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

int findpai(int index,int* grupo)
{
    if(grupo[index]==index)
    {
        return index;
    }
    return findpai(grupo[index],grupo);
  
}
void updatepais(int index,int* grupo)
{
    if(grupo[index]==index){
        return;
    }
    updatepais(grupo[index],grupo);
    grupo[index]=findpai(grupo[index],grupo);
}
int getsize(int index, int* tamanhos){
    return tamanhos[index];
}
int getbigger(int *tamanhos,int size)
{
    int bigger=0;
    for(int i=0;i<size;i++)
    {
        if(bigger<tamanhos[i])
        {
            bigger=tamanhos[i];
        }

    }return bigger;
}

int main ()
{
    int arraysize=0;
    scanf("%d",&arraysize);
    arraysize= arraysize+1;
    int* grupos= (int*)malloc(sizeof(int)*arraysize);
    int* sizes= (int*)malloc(sizeof(int)*arraysize);
    for(int i=0;i<arraysize;i++)
    {
        grupos[i]=i;
        sizes[i]=1;
    }
    
    while (!feof(stdin) ) {
	char leitura[15];
    if ( scanf("%s", &leitura) == 1) {
            if(leitura[0]=='?'){
                printf("%d\n",getbigger(sizes,arraysize));
                continue;
            }
           int first= atoi(leitura);
           char temp[15];
           scanf("%s",temp);
           int second = atoi(temp);
          int pai1=findpai(first,grupos);
          int pai2=findpai(second,grupos);
          if(pai1==pai2){continue;}
          else if(pai2==second)
          {
              grupos[second]=pai1;
              int nv=sizes[second]+ sizes[pai1];
              sizes[pai1]= nv;             
             

          }
          else {
              grupos[pai2]=pai1;
              sizes[pai1]=sizes[pai1]+sizes[pai2];
             
          }         
            
        }        
    }
   


  

    return 0;
}
