#include "arvores.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

void carregaArquivoArvAVL(arvAVL *raizAVL, FILE *arquivo);
void carregaArquivoLLRB(arvLLRB *raizLLRB, FILE *arquivo);
myData retornaData(FILE *arquivo);
FILE *abreArquivo(char nomeArquivo[50]);
int ordenaArquivo(FILE *arquivo);

int main() {

  int x;
  arvAVL *raizAVL;
  arvLLRB *raizLLRB;
  FILE *arquivo;

  raizAVL = cria_arvAVL();
  raizLLRB = cria_arvLLRB();

  arquivo = abreArquivo("massaDados.csv");

  x = ordenaArquivo(arquivo);
  if (x) {
    printf("Ordenado com sucesso");
  } else {
    printf("Falha ao ordenar");
  }

  // carregaArquivoArvAVL(raizAVL, arquivo);
  // carregaArquivoArvLLRB(raizLLRB, arquivo);

  // chamar AVL ou LLRB. Para executar os dois, seria necesseário abrir o
  // arquivo novamente.

  return 0;
}

FILE *abreArquivo(char nomeArquivo[50]) {
  FILE *arquivo;
  arquivo = fopen(nomeArquivo, "r");

  if (arquivo != NULL) {
    printf("Arquivo aberto com sucesso!\n");
  } else {
    printf("Erro ao carregar o arquivo!\n");
    system("pause");
    exit(1);
  }

  return arquivo;
}

myData retornaData(FILE *arquivo) {
  char aux[300];
  myData data;
  if (fgets(aux, sizeof(aux), arquivo)) {
    data.codigo = atoi(strtok(aux, ";"));
    strcpy(data.nome, strtok(NULL, ";"));
    data.idade = atoi(strtok(NULL, ";"));
    strcpy(data.empresa, strtok(NULL, ";"));
    strcpy(data.departamento, strtok(NULL, ";"));
    data.salario = atof(strtok(NULL, "\n"));
  }
  return data;
}

void carregaArquivoArvAVL(arvAVL *raizAVL, FILE *arquivo) {
  struct timeval antes, depois;
  double deltaT = 0;

  char aux[300];
  int jump = 1;
  myData data;

  printf("\nAbrindo dados e inserindo na arvore AVL...");
  gettimeofday(&antes, NULL);

  while (fgets(aux, sizeof(aux), arquivo)) {
    if (jump) {
      jump = 0;
      continue;
    }
    data = retornaData(arquivo);
    insere_arvAVL(raizAVL, data.codigo, data.nome, data.idade, data.empresa,
                  data.departamento, data.salario);
  }

  gettimeofday(&depois, NULL);

  deltaT = (depois.tv_sec - antes.tv_sec) +
           (depois.tv_usec - antes.tv_usec) / 1000000.0;

  printf("\nTempo de execucao AVL: %f segundos\n", deltaT);

  fclose(arquivo);
}

void carregaArquivoArvLLRB(arvLLRB *raizLLRB, FILE *arquivo) {
  struct timeval antes, depois;
  double deltaT = 0;
  myData data;
  char aux[300];
  int jump = 1;

  printf("Abrindo dados e inserindo na arvore LLRB...");
  gettimeofday(&antes, NULL);

  while (fgets(aux, sizeof(aux), arquivo)) {
    if (jump) {
      jump = 0;
      continue;
    }
    data = retornaData(arquivo);
    insere_arvoreLLRB(raizLLRB, data.codigo, data.nome, data.idade,
                      data.empresa, data.departamento, data.salario);
  }

  gettimeofday(&depois, NULL);

  deltaT = (depois.tv_sec - antes.tv_sec) +
           (depois.tv_usec - antes.tv_usec) / 1000000.0;

  printf("\nTempo de execucao LLRB: %f segundos\n", deltaT);
  fclose(arquivo);
}

int ordenaArquivo(FILE *arquivo) {
  char aux[300];
  myData *v;
  int size = 0;
  int jump = 1;
  int i = 0;

  while (fgets(aux, sizeof(aux), arquivo)) {
    size++;
  }
  v = (myData *)calloc(size, sizeof(myData));

  rewind(arquivo);
  while (fgets(aux, sizeof(aux), arquivo)) {
    if (jump) {
      jump = 0;
      continue;
    }
    v[i] = retornaData(arquivo);
    i++;
  }
  RadixSortLSD(v, size);

  FILE *sortedFile = fopen("sorted_massaDados.csv", "w");
  if (sortedFile == NULL) {
    printf("Erro ao criar arquivo ordenado!\n");
    free(v);
    return 0;
  }

  fprintf(sortedFile, "codigo;nome;idade;empresa;departamento;salario\n");

  for (int j = 0; j < size; j++) {
    fprintf(sortedFile, "%d;%s;%d;%s;%s;%.2f\n", v[j].codigo, v[j].nome,
            v[j].idade, v[j].empresa, v[j].departamento, v[j].salario);
  }

  fclose(sortedFile);
  free(v);
  return 1;
}
