#include <stdio.h>
#include <stdlib.h>
#include "arvores.h"

struct NO{
    int codigo;
    char nome[50];
    int idade;
    char empresa[50];
    char departamento[50];
    float salario;
    int alt;
    struct NO *esq;
    struct NO *dir;
};


arvAVL *cria_arvAVL(){
    arvAVL *raiz = (arvAVL*) malloc(sizeof(arvAVL));
    if(raiz != NULL){
        *raiz = NULL;
    }
    return raiz;
}
void libera_NO(struct NO *no){
    if(no == NULL){
        return;
    }
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

void liberar_arvAVL(arvAVL *raiz){
    if(raiz == NULL){
        return;
    }
    libera_NO(*raiz);
    free(raiz);
}



int vazia_arvAVL(arvAVL *raiz){
    if(raiz == NULL){
        return 1;
    }
    if(*raiz == NULL){
        return 1;
    }
    return 0;
}


int altura_arvAVL(arvAVL *raiz){
    if(raiz == NULL){
        return 0;
    }
    if(*raiz == NULL){
        return 0;
    }
    int alt_esq = altura_arvAVL(&((*raiz)->esq));
    int alt_dir = altura_arvAVL(&((*raiz)->dir));
    if(alt_esq > alt_dir){
        return (alt_esq + 1);
    }else{
        return(alt_dir + 1);
    }
}


int totalNO_arvAVL(arvAVL *raiz){
    if(raiz == NULL){
        return 0;
    }
    if(*raiz == NULL){
        return 0;
    }
    int alt_esq = totalNO_arvAVL(&((*raiz)->esq));
    int alt_dir = totalNO_arvAVL(&((*raiz)->dir));
    return(alt_esq + alt_dir + 1);

}

void preOrdem_arvAVL(arvAVL *raiz){
    if(raiz == NULL){
        return;
    }
    if(*raiz != NULL){
        printf("%d\n", (*raiz)->codigo);
        preOrdem_arvAVL(&((*raiz)->esq));
        preOrdem_arvAVL(&((*raiz)->dir));
    }
}

void emOrdem_arvAVL(arvAVL *raiz){
    if(raiz == NULL){
        return;
    }
    if(*raiz != NULL){
        emOrdem_arvAVL(&((*raiz)->esq));
        printf("%d\n", (*raiz)->codigo);
        emOrdem_arvAVL(&((*raiz)->dir));
    }
}

void posOrdem_arvAVL(arvAVL *raiz){
    if(raiz == NULL){
        return;
    }
    if(*raiz != NULL){
        posOrdem_arvAVL(&((*raiz)->esq));
        posOrdem_arvAVL(&((*raiz)->dir));
        printf("%d\n", (*raiz)->codigo);
    }
}




int consulta_arvAVL(arvAVL *raiz, int valor){
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


int alt_no(struct NO *no){
    if(no == NULL){
        return -1;
    }else{
        return no->alt;
    }
}

int maior(int x, int y){
    if(x > y){
        return (x);
    }else{
        return (y);
    }
}

int fatorBalanceamento_NO(struct NO *no){
    return abs(alt_no(no->esq) - alt_no(no->dir));
}

void rotacaoLL(arvAVL *A){
    struct NO *B;
    B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    (*A)->alt = maior(alt_no((*A)->esq), alt_no((*A)->dir)) + 1;
    B->alt = maior(alt_no(B->esq), (*A)->alt) + 1;
    *A  = B;
}

void rotacaoRR(arvAVL *A){
    struct NO *B;
    B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = (*A);
    (*A)->alt = maior(alt_no((*A)->esq), alt_no((*A)->dir)) + 1;
    B->alt = maior(alt_no(B->dir), (*A)->alt) + 1;
    (*A) = B;
}

void rotacaoLR(arvAVL *A){
    rotacaoRR(&(*A)->esq);
    rotacaoLL(A);
}

void rotacaoRL(arvAVL *A){
    rotacaoLL(&(*A)->dir);
    rotacaoRR(A);
}

void confirmaInsercao(int x){
	if(!x){
		printf("Erro ao inserir elemento!\n");

	}

}

int insere_arvAVL(arvAVL *raiz, int valor, char nome[50], int idade, char empresa[50], char departamento[50], float salario){
	int res;
	if(*raiz == NULL){
		struct NO *novo;
		novo = (struct NO*) malloc(sizeof(struct NO));
		if(novo == NULL){
			return 0;
		}
		novo->codigo = valor;
		novo->idade = idade;
		novo->salario = salario;
		strcpy(novo->nome, nome);
        strcpy(novo->empresa, empresa);
		strcpy(novo->departamento, departamento);
		novo->alt = 0;
		novo->esq = NULL;
		novo->dir = NULL;
		*raiz = novo;
		return 1;
	}
	struct NO *atual = *raiz;
	if(valor < atual->codigo){
		if((res = insere_arvAVL(&(atual->esq), valor, nome, idade, empresa, departamento, salario)) == 1){
			if(fatorBalanceamento_NO(atual) >= 2){
				if(valor < (*raiz)->esq->codigo){
					rotacaoLL(raiz);
				}else{
					rotacaoLR(raiz);
				}
			}
		}
	}else{
		if(valor > atual->codigo){
			if((res = insere_arvAVL(&(atual->dir), valor, nome, idade, empresa, departamento, salario)) == 1){
				if(fatorBalanceamento_NO(atual) >= 2){
					if((*raiz)->dir->codigo < valor){
						rotacaoRR(raiz);
					}else{
						rotacaoRL(raiz);
					}
				}
			}
		}else{
			printf("Elemento %d ja existe. Insercao duplicada!\n", valor);
			return 0;
		}
	}
	atual->alt = maior(alt_no(atual->esq), alt_no(atual->dir)) + 1;
	return res;

}
struct NO *procuramenor(struct NO *atual){
	struct NO *no1 = atual;
	struct NO *no2 = atual->esq;
	while(no2 != NULL){
		no1 = no2;
		no2 = no2->esq;
	}
	return no1;
}
int remove_arvAVL(arvAVL *raiz, int valor){

	if(*raiz == NULL){
		return 0;
	}
	int res;
	if(valor < (*raiz)->codigo){
		if((res = remove_arvAVL(&(*raiz)->esq, valor)) == 1){
			if(fatorBalanceamento_NO(*raiz) >= 2){
				if(alt_no((*raiz)->dir->esq) <= alt_no((*raiz)->dir->dir)){
				rotacaoRR(raiz);
				}else{
				rotacaoRL(raiz);
				}
			}
		}
	}
	if((*raiz)->codigo < valor){
		if((res = remove_arvAVL(&(*raiz)->dir, valor)) == 1){
			if(fatorBalanceamento_NO(*raiz) >= 2){
				if(alt_no((*raiz)->esq->dir) <= alt_no((*raiz)->esq->esq)){
					rotacaoLL(raiz);
				}else{
					rotacaoLR(raiz);
				}
			}
		}
	}
	if((*raiz)->codigo == valor){
		if((*raiz)->esq == NULL || (*raiz)->dir == NULL){
			struct NO *no_velho = (*raiz);
			if((*raiz)->esq != NULL){
				*raiz = (*raiz)->esq;
			}else{
				*raiz = (*raiz)->dir;
			}
			free(no_velho);
		}else{
			struct NO *temp = procuramenor((*raiz)->dir);
			(*raiz)->codigo = temp->codigo;
			remove_arvAVL(&(*raiz)->dir, (*raiz)->codigo);
			if(fatorBalanceamento_NO(*raiz) >= 2){
				if(alt_no((*raiz)->esq->dir) <= alt_no((*raiz)->esq->esq)){
					rotacaoLL(raiz);
				}else{
					rotacaoLR(raiz);
				}
			}
		}
		if(*raiz != NULL){
			(*raiz)->alt = maior(alt_no((*raiz)->esq), alt_no((*raiz)->dir)) + 1;
		}
		return 1;
	}
	if(*raiz != NULL){
		(*raiz)->alt = maior(alt_no((*raiz)->esq), alt_no((*raiz)->dir)) + 1;
	}
	return res;

}



