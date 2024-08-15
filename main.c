#include "arvores.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <stdbool.h>

void carregaArquivoArvAVL(arvAVL *raizAVL, FILE *arquivo);
void carregaArquivoLLRB(arvLLRB *raizLLRB, FILE *arquivo);
myData retornaData(char *linha);
FILE *abreArquivo(char nomeArquivo[50]);
int ordenaArquivo(FILE *arquivo);

int main() {
    int escolhaArquivo, escolhaArvore;
    char arquivoNome[50];
    arvAVL *raizAVL;
    arvLLRB *raizLLRB;
    FILE *arquivo;

    raizAVL = cria_arvAVL();
    raizLLRB = cria_arvLLRB();

    while (1) {
        printf("\nEscolha o arquivo para carregar:\n");
        printf("1. Arquivo desordenado\n");
        printf("2. Arquivo ordenado\n");
        printf("Outro. Sair\n");
        printf("Escolha uma opcao: ");
        if (scanf("%d", &escolhaArquivo) != 1) {
            break;
        }
        getchar(); // Limpa o buffer de entrada

        if (escolhaArquivo == 1) {
            strcpy(arquivoNome, "massaDados.csv");
        } else if (escolhaArquivo == 2) {
            arquivo = fopen("massaDados.csv", "r");
            if (!ordenaArquivo(arquivo)) {
                printf("Erro ao ordenar o arquivo.\n");
                continue;
            }
            strcpy(arquivoNome, "sorted_massaDados.csv");
        } else {
            printf("Saindo do programa.\n");
            break;
        }

        arquivo = abreArquivo(arquivoNome);

        printf("\nEscolha a arvore para inserir os dados:\n");
        printf("1. Arvore AVL\n");
        printf("2. Arvore LLRB\n");
        printf("Outro. Sair\n");
        printf("Escolha uma opcao: ");
        if (scanf("%d", &escolhaArvore) != 1) {
            break;
        }
        getchar(); // Limpa o buffer de entrada

        if (escolhaArvore == 1) {
            carregaArquivoArvAVL(raizAVL, arquivo);
            //preOrdem_arvAVL(raizAVL);
        } else if (escolhaArvore == 2) {
            carregaArquivoArvLLRB(raizLLRB, arquivo);

        } else {
            printf("Saindo do programa.\n");
            break;
        }
    }

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

myData retornaData(char *linha) {
  myData data;
    data.codigo = atoi(strtok(linha, ";"));
    strcpy(data.nome, strtok(NULL, ";"));
    data.idade = atoi(strtok(NULL, ";"));
    strcpy(data.empresa, strtok(NULL, ";"));
    strcpy(data.departamento, strtok(NULL, ";"));
    data.salario = atof(strtok(NULL, "\n"));

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
    data = retornaData(aux);
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
    data = retornaData(aux);
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
  if (size <= 0) {
    printf("O arquivo não contém dados suficientes!\n");
    return 0;
  }
  v = (myData *)calloc(size, sizeof(myData));
  if (v == NULL) {
        printf("Erro ao alocar memória!\n");
        return 0;
    }
  rewind(arquivo);
  size--;
  if (fgets(aux, sizeof(aux), arquivo) == NULL) {
        printf("Erro ao ler o cabeçalho do arquivo!\n");
        free(v);
        return 0;
    }

  while (fgets(aux, sizeof(aux), arquivo)) {
    v[i] = retornaData(aux);
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
