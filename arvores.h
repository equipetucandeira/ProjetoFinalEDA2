#include <string.h>
typedef struct NO *arvAVL;
typedef struct NO *arvLLRB;
typedef struct {
  char nome[50];
  char empresa[50];
  char departamento[50];
  int codigo;
  int idade;
  float salario;
} myData;

int insere_arvAVL(arvAVL *raiz, int valor, char nome[50], int idade,
                  char empresa[50], char departamento[50], float salario);
int remove_arvAVL(arvAVL *raiz, int valor);

int insere_arvoreLLRB(arvLLRB *raiz, int valor, char nome[50], int idade,
                      char empresa[50], char departamento[50], float salario);
int remove_arvoreLLRB(arvLLRB *raiz, int valor);

void confirmaInsercao(int x);

arvAVL *cria_arvAVL();
arvLLRB *cria_arvLLRB();

void preOrdem_arvore(arvAVL *raiz);
void preOrdem_arvore(arvLLRB *raiz);
