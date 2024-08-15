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
typedef myData T;

void libera_NO(struct NO *no);
int RadixSortLSD(T *array, const size_t size);
int insere_arvAVL(arvAVL *raiz, int valor, char nome[50], int idade,
                  char empresa[50], char departamento[50], float salario);
int remove_arvAVL(arvAVL *raiz, int valor);

int insere_arvoreLLRB(arvLLRB *raiz, int valor, char nome[50], int idade,
                      char empresa[50], char departamento[50], float salario);
int remove_arvoreLLRB(arvLLRB *raiz, int valor);

void confirmaInsercao(int x);

void liberar_arvAVL(arvAVL *raiz);
void liberar_arvLLRB(arvLLRB *raiz);

arvAVL *cria_arvAVL();
arvLLRB *cria_arvLLRB();

void preOrdem_arvore(arvAVL *raiz);
