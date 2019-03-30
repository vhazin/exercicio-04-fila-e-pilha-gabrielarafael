#include <stdio.h>
#include<stdlib.h>
#include <string.h>
struct no_pilha{
    int elemento;
    struct no_pilha* proximo;
};

struct pilha{
    struct no_pilha* topo;
    int num_elementos;
};
struct no_lista{
    struct pilha* stack;
    struct no_lista* proximo;
    struct no_lista* anterior;
};

struct lista_dligada{
    struct no_lista* cabeca;
};
struct lista_simples{
    struct no_simples* cabeca;
    int tamanho;
};
struct no_simples{
    struct lista_dligada* lista_duplamente;
    struct no_simples* proximo;
};
typedef struct lista_simples* l;
typedef struct lista_dligada* ponteiro_lista;
typedef struct no_lista no_lista;
typedef struct pilha* pointer_pilha;

int possui(struct no_pilha* p){
    if(p == NULL)

        return 0;
    else if(p->elemento == 1)
        return 1;
    else
        return possui(p->proximo);
}

pointer_pilha iniciar_pilha(){
    pointer_pilha pilha = malloc(sizeof(struct pilha));
    pilha->topo =NULL;
    pilha->num_elementos = 0;
    return pilha;
}
ponteiro_lista iniciar_lista(){
    ponteiro_lista lista = malloc(sizeof(struct lista_dligada));
    lista->cabeca = NULL;

    return lista;

}

ponteiro_lista add_lista(ponteiro_lista lista,pointer_pilha elementos){

    no_lista* no_inserir = malloc(sizeof(no_lista));
    no_inserir->stack = elementos;
    no_lista* no_aux = lista->cabeca;


    if(lista->cabeca == NULL){
        lista->cabeca = no_inserir;
        lista->cabeca->proximo = NULL;
        lista->cabeca->anterior= NULL;

    }
    else{
    while(no_aux->proximo!= NULL){
        no_aux = no_aux->proximo;

    }

    no_aux->proximo = no_inserir;
    no_inserir->anterior = no_aux;
    no_inserir->proximo = NULL;


    }

    return lista;
}

pointer_pilha push(int elemento,pointer_pilha pilha){

    struct no_pilha* no_p = malloc(sizeof(struct no_pilha));
    no_p->elemento = elemento;
    no_p->proximo = pilha->topo;
    pilha->topo = (pointer_pilha*)no_p;
    pilha->num_elementos++;
    return pilha;
}

pointer_pilha pop(pointer_pilha pilha){
    pilha->topo = pilha->topo->proximo;
    pilha->num_elementos--;
    return pilha;
}

int top(pointer_pilha pilha){
    return pilha->topo->elemento;
}
int achar_caminhoauxE(no_lista* no, int num){

    if(no->anterior == NULL){

        return no->stack->num_elementos -(num-1);
    }
    else if(no->anterior->stack->num_elementos<num){
       return no->stack->num_elementos -(num-1);
    }
    else{

        return(no->stack->num_elementos -num +1 + achar_caminhoauxE(no->anterior,num));
    }

}
int achar_caminhoauxD(no_lista* no,int num){
     if(no->proximo ==NULL){
        return no->stack->num_elementos -(num-1);
    }
    else if(no->proximo->stack->num_elementos<num){
        return no->stack->num_elementos -(num-1);
    }
    else{
        return( no->stack->num_elementos - num +1 + achar_caminhoauxD(no->proximo,num));
    }
}

int achar_caminho(no_lista* no){

    if(no->stack->topo->elemento != 1){

        no->stack = pop(no->stack);

        return 1 + achar_caminho(no);
        }
    else{

        if(no->proximo == NULL || no->anterior == NULL){

            return 0;

            }
        else if(no->stack->num_elementos > no->proximo->stack->num_elementos || no->stack->num_elementos > no->anterior->stack->num_elementos){

            return 0;
        }
        else{
        int d_esquerda = achar_caminhoauxE(no->anterior,no->stack->num_elementos);
        int d_direita = achar_caminhoauxD(no->proximo,no->stack->num_elementos);
        return (d_esquerda < d_direita)?d_esquerda:d_direita;
    }
}
}


int desempilha(no_lista* no){
    if(possui(no->stack->topo)==1){
        return achar_caminho(no);
    }else{
        return desempilha(no->proximo);
    }


}






l add_simples(struct lista_simples* l_s,ponteiro_lista lista_ligada){
    struct no_simples* inserir = malloc(sizeof(struct no_simples));
    inserir->lista_duplamente = lista_ligada;
    struct no_simples* aux = l_s->cabeca;
    if(l_s->cabeca == NULL){
        l_s->cabeca = inserir;
        l_s->cabeca->proximo = NULL;
    }
    else {
    while(aux->proximo !=NULL){
        aux= aux->proximo;
    }
    aux->proximo = inserir;
    inserir->proximo = NULL;
    }
    l_s->tamanho++;
    return l_s;
}
int main()
{
    int lis,stac;
    struct lista_simples* list_s= malloc(sizeof(struct lista_simples));
    list_s->cabeca =NULL;
    list_s->tamanho = 0;
    scanf("%d %d",&stac,&lis);



    while(lis!=0 && stac!=0){
        int iterador;

        pointer_pilha pilhas[lis];

        for(iterador=0;iterador<lis;iterador++){
            pilhas[iterador] = iniciar_pilha();


        }


        for(iterador = 0;iterador<lis;iterador++){

            char string[500];

            int iterador2;
            fflush(stdin);
            scanf("%s",string);
            int elementos = atoi(string);

            for(iterador2 = 0;iterador2<elementos;iterador2++){
                scanf("%s",string);
                pilhas[iterador]= push(atoi(string),pilhas[iterador]);

            }

        }




        ponteiro_lista lista_d = iniciar_lista();
        for(iterador = 0; iterador<lis ;iterador++){

          lista_d = add_lista(lista_d,pilhas[iterador]);
        }


        list_s = add_simples(list_s,lista_d);

      scanf("%d %d",&stac,&lis);
    }

    int iterador;
    struct no_simples* no_s = list_s->cabeca;
    while(no_s!= NULL){
        printf("\n%d",desempilha(no_s->lista_duplamente->cabeca));
        no_s = no_s->proximo;
    }

    return 0;
}
