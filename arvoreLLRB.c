#include <stdio.h>
#include <stdlib.h>
#include "arvores.h"
#define RED 1
#define BLACK 0

struct NO{
    int codigo;
    char nome[50];
    int idade;
    char empresa[50];
    char departamento[50];
    float salario;
    struct NO *esq;
    struct NO *dir;
    int cor;
};

int consulta_arvoreLLRB(arvLLRB *raiz, int valor){
    if(raiz == NULL){
        return 0;
    }
    struct NO *atual = *raiz;
    while(atual != NULL){
        if(valor == atual->codigo){
            return 1;
        }
        if(valor > atual->codigo){
            atual = atual->dir;
        }else{
            atual = atual->esq;
        }
    }
    return 0;
}

arvLLRB *cria_arvLLRB(){
    arvLLRB *raiz = (arvLLRB*) malloc(sizeof(arvLLRB));
    if(raiz != NULL){
        *raiz = NULL;
    }
    return raiz;
}

int cor(struct NO *H){
    if(H == NULL){
        return BLACK;
    }else{
        return H->cor;
    }
}

void trocaCor(struct NO *H){
    H->cor = !H->cor;
    if(H->esq != NULL){
        H->esq->cor = !H->esq->cor;
    }
    if(H->dir != NULL){
        H->dir->cor = !H->dir->cor;
    }
}

struct NO *rotacionaEsquerda(struct NO *A){
    struct NO *B = A->dir;
    A->dir = B->esq;
    B->esq = A;
    B->cor = A->cor;
    A->cor = RED;
    return B;
};

struct NO *rotacionaDireita(struct NO *A){
    struct NO *B = A->esq;
    A->esq = B->dir;
    B->dir = A;
    B->cor = A->cor;
    A->cor = RED;
    return B;
};

struct NO *move2EsqRED(struct NO *H){
    trocaCor(H);
    if(cor(H->dir->esq) == RED){
        H->dir = rotacionaDireita(H->dir);
        H = rotacionaEsquerda(H);
        trocaCor(H);
    }
    return H;
};

struct NO *move2DirRED(struct NO *H){
    trocaCor(H);
    if(cor(H->esq->esq) == RED){
        H = rotacionaDireita(H);
        trocaCor(H);
    }
    return H;
};

struct NO *balancear(struct NO *H){
    if(cor(H->dir) == RED){
        H = rotacionaEsquerda(H);
    }
    if(H->esq != NULL && cor(H->dir) == RED && cor(H->esq->esq) == RED){
        H = rotacionaEsquerda(H);
    }
    if(cor(H->esq) == RED && cor(H->dir) == RED){
        trocaCor(H);
    }
    return H;
};


struct NO *insereNO(struct NO *H, int valor, int *resp, char nome[50], int idade, char empresa[50], char departamento[50], float salario){
    if(H == NULL){
        struct NO *novo;
        novo = (struct NO*) malloc(sizeof(struct NO));
        if(novo == NULL){
            *resp = 0;
            return NULL;
        }
        novo->codigo = valor;
        novo->idade = idade;
        novo->salario = salario;
        strcpy(novo->nome, nome);
        strcpy(novo->empresa, empresa);
        strcpy(novo->departamento, departamento);
        novo->cor = RED;
        novo->dir = NULL;
        novo->esq = NULL;
        *resp = 1;
        return novo;
    }
    if(valor == H->codigo){
        *resp = 0;
    }else{
        if(valor < H->codigo){
            H->esq = insereNO(H->esq, valor, resp, nome, idade, empresa, departamento, salario);
        }else{
            H->dir = insereNO(H->dir, valor, resp, nome, idade, empresa, departamento, salario);
        }
    }
    if(cor(H->dir) == RED && cor(H->esq) == BLACK){
        H = rotacionaEsquerda(H);
    }
    if(cor(H->esq) == RED && cor(H->esq->esq) == RED){
        H = rotacionaDireita(H);
    }
    if(cor(H->esq) == RED && cor(H->dir) == RED){
        trocaCor(H);
    }
    return H;
};
struct NO *removeMenor(struct NO *H){
    if(H->esq == NULL){
        free(H);
        return NULL;
    }
    if(cor(H->esq) == BLACK && cor(H->esq->esq) == BLACK){
        H = move2EsqRED(H);
    }
    H->esq = removeMenor(H->esq);
    return balancear(H);
};
struct NO *procuraMenor(struct NO *atual){
    struct NO *no1 = atual;
    struct NO *no2 = atual->esq;
    while(no2 != NULL){
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
};
struct NO *removeNO(struct NO *H, int valor){
    if(valor < H->codigo){
        if(cor(H->esq) == BLACK && cor(H->esq->esq) == BLACK){
            H = move2EsqRED(H);
        }
        H->esq = removeNO(H->esq, valor);
    }else{
        if(cor(H->esq) == RED){
            H = rotacionaDireita(H);
        }
        if(valor == H->codigo && (H->dir == NULL)){
            free(H);
            return NULL;
        }
        if(cor(H->dir) == BLACK && cor(H->dir->esq) == BLACK){
            H = move2DirRED(H);
        }
        if(valor == H->codigo){
            struct NO *x = procuraMenor(H->dir);
            H->codigo = x->codigo;
            H->dir = removeMenor(H->dir);
        }else{
            H->dir = removeNO(H->dir, valor);
        }
    }
    return balancear(H);
};

int remove_arvoreLLRB(arvLLRB *raiz, int valor){
    if(consulta_arvoreLLRB(raiz, valor)){
        struct NO *H = *raiz;
        *raiz = removeNO(H, valor);
        if(*raiz != NULL){
            (*raiz)->cor = BLACK;
        }
        return 1;
    }else{
        return 0;
    }
}

int insere_arvoreLLRB(arvLLRB *raiz, int valor, char nome[50], int idade, char empresa[50], char departamento[50], float salario){
    int resp;
    *raiz = insereNO(*raiz, valor, &resp, nome, idade, empresa, departamento, salario);
    if((*raiz) != NULL){
        (*raiz)->cor = BLACK;
    }
    return resp;
}



