#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// Constantes do menu
#define CADASTRAR_VENDEDOR 1
#define REMOVER_VENDEDOR 2
#define ATUALIZAR_VENDEDOR 3
#define LISTAR_VENDEDORES 4
#define LISTAR_VENDEDORES_SENIOR 5
#define LISTAR_VENDEDORES_PLENO_SENIOR_80_DE_FREQUENCIA 6
#define LISTAR_VENDEDORES_JUNIOR_FREQUENCIA_ABAIXO_60 7
#define PROCURAR_VENDEDOR_POR_MATRICULA 8
#define SAIR 9

// Tipagem vendedor
typedef struct Nivel {
  int id;
  char* nome;
} Nivel;

typedef struct TipoVenda {
  float credito;
  float debito;
  float prazo;
  float avista;
} TiposVendas;

typedef struct Vendedor {
  int matricula;
  char nome[60];
  int faltas;
  struct Nivel nivel;
  struct TipoVenda tipoVenda;
  float salario;
} Vendedor;

// Funções
float somarVendas(struct TipoVenda tipoVenda) {
  return tipoVenda.debito + tipoVenda.credito + tipoVenda.prazo + tipoVenda.avista;
}

struct Nivel nivelVendedor(float vendas) {
    struct Nivel nivel;

    if(vendas < 5000) {
      nivel.id = 1;
      nivel.nome = "Junior";
    }

    if(vendas > 5000) {
      nivel.id = 2;
      nivel.nome = "Plenio";
    };

    if(vendas > 10000) {
      nivel.id = 3;
      nivel.nome = "Senior";
    };

    return nivel;
}

void mostarVendedor(struct Vendedor vendedor) {
  printf("Matricula: %0.d \n", vendedor.matricula);
  printf("Nome: %s \n", vendedor.nome);
  printf("Faltas: %0.d \n", vendedor.faltas);
  printf("Nivel: %s \n", vendedor.nivel.nome);
  printf("Vendas credito: %2.f \n", vendedor.tipoVenda.credito);
  printf("Vendas debito: %2.f \n", vendedor.tipoVenda.debito);
  printf("Vendas prazo: %2.f \n", vendedor.tipoVenda.prazo);
  printf("Vendas avista: %2.f \n", vendedor.tipoVenda.avista);
}

void menu() {
  printf("-‍😉😜--------------------🤷‍♂️😜- \n");
  printf("   Escolhar uma opção \n");
  printf("-😉--------------------️😜- \n");

  char opcao[80];

  snprintf(opcao, 50, "%d%s", CADASTRAR_VENDEDOR, " - Cadastrar vendendor\n");
  printf("%s", opcao);

  snprintf(opcao, 50, "%d%s", REMOVER_VENDEDOR, " - Remover vendendor\n");
  printf("%s", opcao);

  snprintf(opcao, 50, "%d%s", ATUALIZAR_VENDEDOR, " - Atualizar vendendor\n");
  printf("%s", opcao);

  snprintf(opcao, 50, "%d%s", LISTAR_VENDEDORES, " - Listar vendendores\n");
  printf("%s", opcao);

  snprintf(opcao, 50, "%d%s", LISTAR_VENDEDORES_SENIOR, " - Listar vendedores Senior\n");
  printf("%s", opcao);

  snprintf(opcao, 80, "%d%s",  LISTAR_VENDEDORES_PLENO_SENIOR_80_DE_FREQUENCIA, " - Listar vendendores pleno/senior com 80% de frequência\n");
  printf("%s", opcao);

  snprintf(opcao, 80, "%d%s", LISTAR_VENDEDORES_JUNIOR_FREQUENCIA_ABAIXO_60, " - Listar vendedores junior com frequência abaixo de 60%\n");
  printf("%s", opcao);

  snprintf(opcao, 50, "%d%s", PROCURAR_VENDEDOR_POR_MATRICULA, " - Procurar Vendedor por matricula\n");
  printf("%s", opcao);

  snprintf(opcao, 50, "%d%s", SAIR, " - Sair\n");
  printf("%s", opcao);
}

struct Vendedor atualizarVendedor(struct Vendedor vendedor){
  printf("Matricula: ");
  scanf("%d", &vendedor.matricula);
  printf("Nome: ");
  scanf("%s", vendedor.nome);
  printf("Faltas: ");
  scanf("%d", &vendedor.faltas);
  printf("Vendas debito: ");
  scanf("%f", &vendedor.tipoVenda.debito);
  printf("Vendas credito: ");
  scanf("%f", &vendedor.tipoVenda.credito);
  printf("Vendas prazo: ");
  scanf("%f", &vendedor.tipoVenda.prazo);
  printf("Vendas avista: ");
  scanf("%f", &vendedor.tipoVenda.avista);
  vendedor.nivel = nivelVendedor(somarVendas(vendedor.tipoVenda));
  return vendedor;
}

struct Vendedor criarVendedor(struct Vendedor vendedor, struct Vendedor arrayVendedores[4]){
  printf("Matricula: ");
  scanf("%d", &vendedor.matricula);

  if(vendedor.matricula == 0) {
    printf("\nMatricula não pode ser zero\n\n");
    return vendedor;
  }

  for(int i = 0; i < 4; i++) {
    if(arrayVendedores[i].matricula == vendedor.matricula){
      printf("\nMatricula já cadastrada\n\n");
      vendedor.matricula = 0;
      return vendedor;
    }
  }

  printf("Nome: ");
  scanf("%s", vendedor.nome);
  printf("Faltas: ");
  scanf("%d", &vendedor.faltas);
  printf("Vendas debito: ");
  scanf("%f", &vendedor.tipoVenda.debito);
  printf("Vendas credito: ");
  scanf("%f", &vendedor.tipoVenda.credito);
  printf("Vendas prazo: ");
  scanf("%f", &vendedor.tipoVenda.prazo);
  printf("Vendas avista: ");
  scanf("%f", &vendedor.tipoVenda.avista);
  vendedor.nivel = nivelVendedor(somarVendas(vendedor.tipoVenda));
  return vendedor;
}

struct Vendedor deletarVendedor(struct Vendedor vendedor) {
  vendedor.matricula = 0;
  vendedor.faltas = 0;
  strcpy(vendedor.nome, "0");
  vendedor.tipoVenda.debito = 0;
  vendedor.tipoVenda.credito = 0;
  vendedor.tipoVenda.prazo = 0;
  vendedor.tipoVenda.avista = 0;
  vendedor.nivel.id = 0;
  vendedor.nivel.nome = 0;
  return vendedor;
}

// Início da aplicação
int main(){
  int menuOpcoes;
  int pesquisaMatricula;
  bool temVendedor = false;
  struct Vendedor vendedor[4] = { };

  while (menuOpcoes != 9) {
    menu();
    scanf("%d", &menuOpcoes);

    switch (menuOpcoes)
    {
      case CADASTRAR_VENDEDOR:
        printf("Cadastrar vendendor: \n");
        temVendedor = false;
        // Verificar array de vendedor
        for(int i = 0; i < 4; i++) {
          if(vendedor[i].matricula == 0){
            temVendedor = true;
            vendedor[i] = criarVendedor(vendedor[i], vendedor);

            if(vendedor[i].matricula != 0) {
              printf("\n\n------- Vendedor Cadastado  -------- \n");
              mostarVendedor(vendedor[i]);
              printf("\n--------------- \n\n");
            }

            break;
          }
        }

        if(temVendedor == false){
          printf("Não é possivel fazer o cadastro! \n");
        }
      break;

      case REMOVER_VENDEDOR:
        printf("Remover vendendor: \n");

        temVendedor = false;
        for(int i = 0; i < 4; i++) {
          if(vendedor[i].matricula != 0){
            temVendedor = true;
          }
        }

        if(temVendedor == false) {
          printf("\nNão existe vendendor cadastado para remover \n\n");
          continue;
        }

        printf("Informe a matricula: ");
        scanf("%d", &pesquisaMatricula);

        temVendedor = false;
        for(int i = 0; i < 4; i++) {
          if(vendedor[i].matricula == pesquisaMatricula){
            vendedor[i] = deletarVendedor(vendedor[i]);
            printf("Vendedor removido! \n");
            temVendedor = true;
          }
        }

        if(temVendedor == false) {
          printf("matricula não encontrada! \n");
        }

      break;

      case ATUALIZAR_VENDEDOR:
        printf("Atualizar vendendor: \n");
        temVendedor = false;
        for(int i = 0; i < 4; i++) {
          if(vendedor[i].matricula != 0){
            temVendedor = true;
          }
        }

        if(temVendedor == false) {
          printf("\nNão existe vendendor cadastado para atualizar \n\n");
          continue;
        }

        printf("Informe a matricula: ");
        scanf("%d", &pesquisaMatricula);
        temVendedor = false;

        for(int i = 0; i < 4; i++) {
          if(vendedor[i].matricula == pesquisaMatricula){
            vendedor[i] = atualizarVendedor(vendedor[i]);
            printf("Vendedor Atualizado! \n");
            temVendedor = false;
          }
        }
        if(!temVendedor) {
          printf("\n\n Matrícula não encontrada! \n\n");
        }

      break;

      case LISTAR_VENDEDORES:
        printf("Listar vendendores: \n");
        temVendedor = false;

        for(int i = 0; i < 4; i++) {
          if(vendedor[i].matricula != 0) {
            temVendedor = true;
            printf("\n \n------- Informações do vendedor -------- \n\n");
            mostarVendedor(vendedor[i]);
            printf("\n--------------- \n\n");

          }
        }

        if(temVendedor == false) {
          printf("\n \n------- Nenhum vendedor encontrado -------- \n\n");
        }
      break;

      case LISTAR_VENDEDORES_SENIOR:
        printf("Listar vendedores Senior: \n");
        temVendedor = false;

        for(int i = 0; i < 4; i++) {
          if(vendedor[i].nivel.id == 3){
            temVendedor = true;

            printf("\n \n------- Informações do vendedor -------- \n\n");
            mostarVendedor(vendedor[i]);
            printf("\n--------------- \n\n");
          }
        }

        if(temVendedor == false) {
          printf("\n \n------- Nenhum vendedor encontrado -------- \n\n");
        }
      break;

      case LISTAR_VENDEDORES_PLENO_SENIOR_80_DE_FREQUENCIA:
        printf("Listar vendendores pleno ou senior com frequência acima de 80: \n");
        temVendedor = false;
        for(int i = 0; i < 4; i++) {
          if((vendedor[i].nivel.id == 2 || vendedor[i].nivel.id == 3) && (26 - vendedor[i].faltas) >= 20) {
            temVendedor = true;
            mostarVendedor(vendedor[i]);
          }
        }

        if(temVendedor == false){
          printf("\n \n------- Nenhum vendedor encontrado -------- \n\n");
        }
      break;

      case LISTAR_VENDEDORES_JUNIOR_FREQUENCIA_ABAIXO_60:
        printf("Listar vendedores junior com frequência de abaixo 60: \n");
        temVendedor = false;
        for(int i = 0; i < 4; i++) {
          if((26 - vendedor[i].faltas) <= 15 && vendedor[i].matricula == 1) {
            temVendedor = true;
            mostarVendedor(vendedor[i]);
          }
        }

        if(temVendedor == false){
          printf("\n \n------- Nenhum vendedor encontrado -------- \n\n");
        }
      break;

      case PROCURAR_VENDEDOR_POR_MATRICULA:
        printf("Procurar vendedor: \n");

        temVendedor = false;
        for(int i = 0; i < 4; i++) {
          if(vendedor[i].matricula != 0){
            temVendedor = true;
          }
        }

        if(temVendedor == false) {
          printf("\nNão existe vendendor cadastado para procurar \n\n");
          continue;
        }

        printf("Informe a matricula: ");
        scanf("%d", &pesquisaMatricula);

        temVendedor = false;
        for(int i = 0; i < 4; i++) {
          if(vendedor[i].matricula == pesquisaMatricula){
            printf("\n\n------- Informações do vendedor -------- \n\n");
            mostarVendedor(vendedor[i]);
            printf("\n--------------- \n\n");
            temVendedor = true;
          }
        }

        if(temVendedor == false){
          printf("\n\n------- Vendedor não encontrado -------- \n\n");
        }
      break;

      case SAIR:
        printf("Saindo!🏃‍♂️🏃‍♀️👋 \n \n");
      break;

      default:
        printf("Opção informada não é valida! \n \n");
    }

  }

  return 0;
}