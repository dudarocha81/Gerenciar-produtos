#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 2

struct Produto {
  int codigo, quantidadeEstoq;
  char titulo[50];
  float preco;
} produtos[TAM];

void imprimeMenu() {

  printf("Menu de Opções\n");
  printf("1. Cadastrar produto.\n");
  printf("2. Alterar produto.\n");
  printf("3. Excluir produto.\n");
  printf("4. Dar baixa na quantidade do produto.\n");
  printf("5. Listar produtos.\n");
  printf("6. Pesquisar produto pelo título.\n");
  printf("7. Listar 10 produtos mais vendidos.\n");
  printf("8. Listar 10 produtos me maior quantidade no estoque.\n");
  printf("9. Sair.\n");
}

void novoProduto() {
  char nome[50];
  int cod, i;
  FILE *arq = fopen("texto.txt", "r+"); 

  if (arq == NULL) {
    printf("\nErro na abertura do arquivo!");
    return;
  }

  getchar();

  for (i = 0; i < TAM; i++) {
  
    printf("Digite o código do %d produto: ", i + 1);
    scanf("%d", &produtos[i].codigo);
    getchar();
    printf("Digite o nome do %d produto: ", i + 1);
    fgets(produtos[i].titulo, sizeof(produtos[i].titulo), stdin);
    printf("Digite o preço do %d produto: ", i + 1);
    scanf("%f", &produtos[i].preco);
    getchar();
    printf("Digite a quantidade em estoque do %d produto: ", i + 1);
    scanf("%d", &produtos[i].quantidadeEstoq);
    getchar();
    printf("\n");

    fprintf(arq, "\n/////////////////////////////////////////////\n");
    fprintf(arq, "\nNome do produto: %s", produtos[i].titulo);
    fprintf(arq, "\nCodigo do produto: %d", produtos[i].codigo);
    fprintf(arq, "\nPreço do produto: R$: %.2f", produtos[i].preco);
    fprintf(arq, "\nQuantidade em estoque: %d\n", produtos[i].quantidadeEstoq);
    
    if (i >= TAM) {
      printf("Limite de produtos excedido.\n");
      break;
    }
  }
  fclose(arq);
}

      void alterar() {
        int cod, op, aux = 0;
        FILE *arq = fopen("texto.txt", "r+");

        if (arq == NULL) {
            printf("\nErro na abertura do arquivo!");
            return;
        }

        printf("Digite o código do produto que deseja alterar: \n");
        scanf("%d", &cod);

        for (int i = 0; i < TAM; i++) {
            fscanf(arq, "Nome do produto: %[^\n]\n", produtos[i].titulo);
            fscanf(arq, "Codigo do produto: %d\n", &produtos[i].codigo);
            fscanf(arq, "Preço do produto: R$: %f\n", &produtos[i].preco);
            fscanf(arq, "Quantidade em estoque: %d\n", &produtos[i].quantidadeEstoq);

            if (cod == produtos[i].codigo) {
                fseek(arq, i * sizeof(struct Produto), SEEK_SET); 

                printf("Digite a opção que deseja alterar:\n");
                printf("1. Título\n");
                printf("2. Preço\n");
                printf("3. Quantidade em estoque\n");
                scanf("%d", &op);

 switch (op) {
   case 1:
     printf("Digite o novo nome do produto: ");
     getchar(); 
     fgets(produtos[i].titulo, sizeof(produtos[i].titulo), stdin);
     break;
   case 2:
     printf("Digite o novo preço do produto: ");
     scanf("%f", &produtos[i].preco);
     break;
   case 3:
     printf("Digite a nova quantidade em estoque do produto: ");
     scanf("%d", &produtos[i].quantidadeEstoq);
     break;
   default:
     printf("Opção inválida.\n");
     break;
            }

              fseek(arq, ftell(arq) - strlen(produtos[i].titulo) - 60, SEEK_SET);
              fprintf(arq, "Nome do produto: %s\n", produtos[i].titulo);
              fprintf(arq, "Codigo do produto: %d\n", produtos[i].codigo);
              fprintf(arq, "Preço do produto: R$: %.2f\n", produtos[i].preco);
              fprintf(arq, "Quantidade em estoque: %d\n", produtos[i].quantidadeEstoq);

            aux = 1; 
            break;
        }
    }

    if (aux == 0) {
        printf("Produto não encontrado.\n");
    }

    fclose(arq);
}

void excluir() {
  int cod, i, aux = 0;
  FILE *arq = fopen("texto.txt", "r");
  FILE *temp = fopen("temp.txt", "w");

  if (arq == NULL || temp == NULL) {
    printf("\nErro na abertura do arquivo!");
    return;
  }

  printf("Digite o código do produto que deseja excluir: ");
  scanf("%d", &cod);

  for (i = 0; i < TAM; i++) {
    if (fscanf(arq, "Codigo do produto: %d", &produtos[i].codigo) != 1) {
      break; 
    }
    fscanf(arq, "\nNome do produto: %[^\n]",
           produtos[i].titulo); 
    fscanf(arq, "\nPreço do produto: R$: %f",
           &produtos[i].preco); 
    fscanf(arq, "\nQuantidade em estoque: %d",
           &produtos[i].quantidadeEstoq); 

    if (produtos[i].codigo == cod) {
      aux = 1; // Flag para saber se achou o produto
      printf("Produto a ser excluído: %s\n", produtos[i].titulo);
    } else {
      fseek(arq, (i * sizeof(produtos[0])), SEEK_SET);
      fprintf(temp, "Codigo do produto: %d\n", produtos[i].codigo);
      fprintf(temp, "Nome do produto: %s\n", produtos[i].titulo);
      fprintf(temp, "Preço do produto: R$: %.2f\n", produtos[i].preco);
      fprintf(temp, "Quantidade em estoque: %d\n\n",
              produtos[i].quantidadeEstoq);
    }
  }

  if (aux == 0) {
    printf("Produto não encontrado.\n");
  }

  fclose(arq);
  fclose(temp);

  remove("texto.txt");
  rename("temp.txt", "texto.txt");
}

void mostrar() {
  char ler;
  FILE *arq = fopen("texto.txt", "r");

  if (arq == NULL) {
    printf("\nErro na abertura do arquivo!");
    return;
  }

  while ((ler = fgetc(arq)) != EOF) {
    printf("%c", ler);
  }

  fclose(arq);
}

void darBaixa() {
  FILE *arq = fopen("texto.txt", "a+");
  int cod, qntd, i;

  if (arq == NULL) {
    printf("\nErro na abertura do arquivo!");
    return;
  }

  printf("Informe o código do produto: \n");
  scanf("%d", &cod);
  getchar();
  
  for (i = 0; i < TAM; i++) {
    if (produtos[i].codigo == cod) {
      printf("Nome do produto: %s\n", produtos[i].titulo);
      printf("Codigo do produto: %d\n", produtos[i].codigo);

      printf("\nDigite a nova quantidade de estoque do produto: ");
      getchar();
      scanf("%d", &produtos[i].quantidadeEstoq);
      // atualizar arq
      fseek(arq, i * sizeof(struct Produto), SEEK_SET);
      fprintf(arq, "a nova quantidade do produto %s é %d", produtos[i].titulo, produtos[i].quantidadeEstoq);
    }
  }
  fclose(arq);
}

void pesquisarTitulo() {
  char nome[50];
  int i;
  FILE *arq = fopen("texto.txt", "r");

  printf("Digite o nome do produto:\n"); getchar();
  fgets(nome, 50, stdin);

  for (i = 0; i < TAM; i++) {
    if (strcmp(nome, produtos[i].titulo) == 0) {
      printf("Nome do produto: %s n", produtos[i].titulo);
      printf("Codigo do produto: %d\n", produtos[i].codigo);
      printf("Preço do produto: R$: %.2f\n", produtos[i].preco);
      printf("Quantidade em estoque: %d\n", produtos[i].quantidadeEstoq);
    }
  }
  fclose(arq);
}

int main(void) {
  int op;

  imprimeMenu();

  do {
    printf("\n//////////////////////////////////////////////////////////////\n\n");
    printf("Digite a Opção: ");
    scanf("%d", &op);

    switch (op) {
    case 1:
      novoProduto();
      break;
    case 2:
      alterar();
      break;
    case 3:
      excluir();
      break;
    case 4:
     darBaixa();
      break;
    case 5:
      mostrar();
      break;
    case 6:
      pesquisarTitulo(); 
      break;
      case 7:
      exit(0); 
      break;
    }
  } while (op != 0);

  return 0;
}

