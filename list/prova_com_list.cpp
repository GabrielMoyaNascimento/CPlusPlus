#include <cstdio>

#include <iostream>

#include <cstring>

using namespace std;

struct cliente_t {
  char nome[50];
  int codigo;
  int idade;
  int titular = 0;
  bool ativo = false;
};

FILE * fp_cliente;
FILE * fp_ultimo_codigo;

void cliente_cadastrar() {
  int ultimo_codigo;
  char ehTitular = 'N';
  int codigoTitular;
  cliente_t cliente;

  fseek(fp_ultimo_codigo, 0, SEEK_SET);
  fread( & ultimo_codigo, sizeof(int), 1, fp_ultimo_codigo);

  cliente.codigo = ultimo_codigo++;

  cout << "Digite o nome do cliente:\n";
  scanf("%s", cliente.nome);

  cout << "Digite a idade do cliente:\n";
  scanf("%i", & cliente.idade);

  cout << "Será o titular? (S/N) \n";
  scanf(" %c", & ehTitular);

  if (ehTitular == 'N') {
    bool titular_encontrado = false;

    do {
      cout << "Informe o código do titular: \n";
      scanf("%i", & codigoTitular);

      fseek(fp_cliente, 0, SEEK_SET);
      while (fread( & cliente, sizeof(cliente_t), 1, fp_cliente) == 1) {
        if (cliente.codigo == codigoTitular || cliente.titular == 0) {
          cliente.titular = codigoTitular;
          titular_encontrado = true;
          printf("%i", cliente.codigo);

          break;
        }
      }

      if (codigoTitular == 0) {
        return;
      }

      if (!titular_encontrado) {
        cout << "Código de titular inválido ou já tem um titular. Tente novamente ou digite 0 para retornar ao menus.\n";
      }
    } while (!titular_encontrado);
  }

  cliente.ativo = true;

  fseek(fp_cliente, 0, SEEK_END);
  fwrite( & cliente, sizeof(cliente_t), 1, fp_cliente);

  fseek(fp_ultimo_codigo, 0, SEEK_SET);
  fwrite( & ultimo_codigo, sizeof(int), 1, fp_ultimo_codigo);
}

void listar_todos_clientes() {
  cliente_t cliente;

  fseek(fp_cliente, 0, SEEK_SET);

  printf("\n");

  while (fread( & cliente, sizeof(cliente), 1, fp_cliente)) {
    if (cliente.ativo == false)
      continue;
    printf("Codigo: %i\n", cliente.codigo);
    printf("Nome: %s\n", cliente.nome);
    printf("Idade: %i\n", cliente.idade);
    cout << "Código do Titular: " << cliente.titular << "\n";
    printf("\n");
  }
  fseek(fp_cliente, 0, SEEK_END);
}

void cliente_alterar() {
  cliente_t cliente;
  int codigo;

  fseek(fp_cliente, 0, SEEK_SET);

  printf("Digite o codigo do Cliente a ser editado: ");
  scanf(" %i", & codigo);

  while (fread( & cliente, sizeof(cliente), 1, fp_cliente) == 1) {

    if (cliente.codigo == codigo) {

      fseek(fp_cliente, -sizeof(cliente_t), SEEK_CUR);

      printf("Digite seu nome:\n");
      scanf("%s", cliente.nome);

      printf("Digite a Idade:\n");
      scanf("%i", & cliente.idade);

      fwrite( & cliente, sizeof(cliente), 1, fp_cliente);

      return;

    }

  }

  printf("Nao foi encontrado nenhum cliente com esse codigo...\n");

}

void cliente_excluir() {
  cliente_t cliente;
  int codigo;

  printf("Digite o codigo do Cliente a ser excluido:\n");
  scanf("%i", & codigo);

  fseek(fp_cliente, 0, SEEK_SET);

  while (fread( & cliente, sizeof(cliente_t), 1, fp_cliente) == 1) {
    if (cliente.codigo == codigo) {

      cliente.ativo = false;

      fseek(fp_cliente, -sizeof(cliente_t), SEEK_CUR);

      fwrite( & cliente, sizeof(cliente_t), 1, fp_cliente);

      printf("Cliente excluido com sucesso!\n");

      return;
    }
  }

  printf("Nao foi encontrado nenhum cliente com esse codigo...\n");
}

FILE * abrir_criar_arquivo(char * fname) {

  FILE * fp = fopen(fname, "r+b");

  if (!fp) {
    fp = fopen(fname, "wb");

    if (!fp) {
      printf("Nao consegui criar o arquivo %s\n", fname);
      exit(1);
    }

    fclose(fp);

    fp = fopen(fname, "r+b");

    if (!fp) {
      printf("Nao consegui abrir o arquivo %s\n", fname);
      exit(1);
    }

    printf("Arquivo %s criado com sucesso\n", fname);
  }

  printf("Arquivo %s aberto\n", fname);

  return fp;
}

FILE * criar_codigo(char * fname) {

  FILE * fp = fopen(fname, "r+b");

  if (!fp) {
    fp = fopen(fname, "wb");
    int ultimo_codigo = 1;

    if (!fp) {
      printf("Nao consegui criar o arquivo %s\n", fname);
      exit(1);
    }

    fwrite( & ultimo_codigo, sizeof(int), 1, fp);
    fclose(fp);

    fp = fopen(fname, "r+b");

    if (!fp) {
      printf("Nao consegui abrir o arquivo %s\n", fname);
      exit(1);
    }

    printf("Arquivo %s criado com sucesso\n", fname);
  }

  printf("Arquivo %s aberto\n", fname);

  return fp;
}

void menu() {
  int choice;
  do {
    printf("\n ===== Clientes Cplusplus ===== \n");
    printf("Escolha as opcoes abaixo: \n");
    printf(" 1 - Cadastrar Cliente \n");
    printf(" 2 - Listar todos os Clientes \n");
    printf(" 3 - Alterar Cliente \n");
    printf(" 4 - Excluir Cliente \n");
    printf(" 0 - Sair ...\n");
    printf("Digite sua escolha: ");
    scanf("%i", & choice);

    switch (choice) {
    case 1:
      cliente_cadastrar();
      break;
    case 2:
      listar_todos_clientes();
      break;
    case 3:
      cliente_alterar();
      break;
    case 4:
      cliente_excluir();
      break;
    case 0:
      printf("Encerrando o programa...");
      break;

    }
  } while (choice != 0);

}

int main() {
  char fcliente[] = "arq-clientes.txt";
  char fultimo_codigo[] = "arq-ultimoCodigoCadastrado.txt";

  fp_cliente = abrir_criar_arquivo((char * ) fcliente);
  fp_ultimo_codigo = criar_codigo((char * ) fultimo_codigo);

  menu();

  fclose(fp_cliente);
  fclose(fp_ultimo_codigo);

  return 0;
}
