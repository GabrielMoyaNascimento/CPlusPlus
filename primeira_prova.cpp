#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list>
#include <iostream>

using namespace std;

struct cliente_titular_t{
	char nome[50];
	int codigo;
	int idade; 
	bool ativo;
};

struct cliente_dependente_t{
	char nome[50];
	int codigo;
	int idade; 
	bool ativo;
	// titular
};

FILE *fp_cliente_titular;
FILE *fp_cliente_dependente;
    
void cliente_titular_cadastrar (){
	cliente_titular_t titular;

	printf("Digite o codigo do Titular:\n");
    	scanf("%i", &titular.codigo);
	
	printf("Digite o nome do Titular:\n");
    	scanf("%s", titular.nome);
    
    	printf("Digite a idade do Titular:\n");
    	scanf("%i", &titular.idade);
    
    	titular.ativo = true;

	fseek(fp_cliente_titular, 0, SEEK_END);

	fwrite(&titular, sizeof(cliente_titular_t), 1, fp_cliente_titular);
}

void listar_todos_clientes_titulares (){
	cliente_titular_t titular;

	fseek(fp_cliente_titular, 0, SEEK_SET);

	printf("\n");

	while (fread(&titular, sizeof(cliente_titular_t), 1, fp_cliente_titular)) {
		if (!titular.ativo) {
			continue;
		}
		printf("Codigo: %i\n", titular.codigo);
		printf("Nome: %s\n",  titular.nome);
		printf("Idade: %i\n",  titular.idade);
		printf("\n");
	}
}

void cliente_titular_alterar(){
	cliente_titular_t titular;
	char nome[50];
    
	fseek(fp_cliente_titular, 0, SEEK_SET);

	printf("Digite o Nome do Titular a ser editado: ");
	scanf(" %s", nome);
    
	while(fread(&titular, sizeof(cliente_titular_t), 1, fp_cliente_titular) == 1)
		{ printf("Posicao: %i\n", ftell(fp_cliente_titular));
        
		if(strcmp(titular.nome, nome)==0){
		fseek(fp_cliente_titular, 0, SEEK_SET);
		printf("Digite seu nome:\n");
		scanf("%s", titular.nome);

		printf("Digite a Idade:\n");
		scanf("%i", &titular.idade);
        
		fwrite(&titular, sizeof(cliente_titular_t), 1, fp_cliente_titular);
		fseek(fp_cliente_titular, 0, SEEK_END);
		break;
		} 
        
	}
	printf("Nao foi encontrado nenhum titular com esse nome...\n");
     
}

void cliente_titular_excluir() {
	cliente_titular_t titular;
	int codigo;

	printf("Digite o codigo do Titular a ser excluido:\n");
	scanf("%i", &codigo);

	fseek(fp_cliente_titular, 0, SEEK_SET);

	while (fread(&titular, sizeof(cliente_titular_t), 1, fp_cliente_titular) == 1) {
		if (titular.codigo == codigo) {
			titular.ativo = false;
			fseek(fp_cliente_titular, -sizeof(cliente_titular_t), SEEK_CUR);
			fwrite(&titular, sizeof(cliente_titular_t), 1, fp_cliente_titular);
			printf("Titular excluido com sucesso!\n");
			return;
		}
	}

	printf("Nao foi encontrado nenhum titular com esse codigo...\n");
}


void cliente_dependente_cadastrar (){
	cliente_dependente_t dependente;

	printf("Digite o codigo do Dependente:\n");
	scanf("%i", &dependente.codigo);
	
	printf("Digite o nome do Dependente:\n");
	scanf("%s", dependente.nome);
    
	printf("Digite a idade do Dependente:\n");
	scanf("%i", &dependente.idade);
    
	dependente.ativo = true;

	fseek(fp_cliente_dependente, 0, SEEK_END);

	fwrite(&dependente, sizeof(cliente_dependente_t), 1, fp_cliente_dependente);

}

void listar_todos_clientes_dependentes (){
	cliente_dependente_t dependente;

	fseek(fp_cliente_dependente, 0, SEEK_SET);

	printf("\n");

	while (fread(&dependente, sizeof(cliente_dependente_t), 1, fp_cliente_dependente)) {
		if (!dependente.ativo) {
			continue;
		}
    		printf("Codigo: %i \n",  dependente.codigo);
    		printf("Nome: %s \n",  dependente.nome);
    		printf("Idade: %i \n", dependente.idade);
		printf("\n");
	}
}

void cliente_dependente_alterar(){
	cliente_dependente_t dependente;
	char nome[50];
    
	fseek(fp_cliente_dependente, 0, SEEK_SET);

	printf("Digite o Nome do Dependente a ser editado: ");
	scanf(" %s", nome);
    
	while(fread(&dependente, sizeof(cliente_dependente_t), 1, fp_cliente_dependente) == 1){ 
		printf("Posicao: %i\n", ftell(fp_cliente_dependente));
        	if(strcmp(dependente.nome, nome)==0){
            		fseek(fp_cliente_dependente, 0, SEEK_SET); 
            		printf("Digite seu nome:\n");
            		scanf("%s", dependente.nome);

            		printf("Digite a Idade:\n");
            		scanf("%i", &dependente.idade);

        
           		fwrite(&dependente, sizeof(cliente_dependente_t), 1, fp_cliente_dependente);
            		fseek(fp_cliente_dependente, 0, SEEK_END);
            		break;
       	 	} 
        
    	}
    	printf("Nao foi encontrado nenhum dependente com esse nome...\n");
     
}

void cliente_dependente_excluir(){
	cliente_dependente_t dependente;
	int codigo;

	printf("Digite o codigo do Dependente a ser excluido:\n");
	scanf("%i", &codigo);

	fseek(fp_cliente_dependente, 0, SEEK_SET);

	while (fread(&dependente, sizeof(cliente_dependente_t), 1, fp_cliente_dependente) == 1) {
		if (dependente.codigo == codigo) {
			dependente.ativo = false;
			fseek(fp_cliente_dependente, -sizeof(cliente_dependente_t), SEEK_CUR);
			fwrite(&dependente, sizeof(cliente_dependente_t), 1, fp_cliente_dependente);
			printf("Dependente excluido com sucesso!\n");
			return;
		}
	}
	printf("Nao foi encontrado nenhum dependente com esse nome...\n");
     
}

FILE* abrir_criar_arquivo (char *fname, FILE *fp){

	fp = fopen(fname, "r+b");

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

void menu() {
	int choice;
	do {
		printf("\n ===== Clientes Cplusplus ===== \n"); 
		printf("Escolha as opcoes abaixo: \n");
        
		printf(" ----------- Titular -------------- \n");
        
		printf(" 1 - Cadastrar Cliente Titular \n"); 
		printf(" 2 - Listar todos os Clientes Titulares \n");
		printf(" 3 - Alterar Cliente Titular \n");
		printf(" 4 - Excluir Cliente Titular \n");
        
		printf(" ----------- Depentente ------------\n");
        
		printf(" 5 - Cadastrar Cliente Dependente \n");
		printf(" 6 - Listar todos Clientes Dependentes \n");
		printf(" 7 - Alterar Cliente Dependente \n");
		printf(" 8 - Excluir Cliente Dependente \n");
        
		printf(" 0 - Sair ...\n"); 
		printf("Digite sua escolha: ");
		scanf("%i", &choice);
        
	switch(choice){
		case 1:
			cliente_titular_cadastrar();
			break;
		case 2:
			listar_todos_clientes_titulares();
			break;
		case  3:
			cliente_titular_alterar();
			break;
		case  4:
			cliente_titular_excluir();
			break;
		case 5:
			cliente_dependente_cadastrar();
			break;
		case 6:
			listar_todos_clientes_dependentes();
			break;
		case 7:
			cliente_titular_alterar();
			break;
		case 8:
			cliente_dependente_excluir();
			break;    
		case  0:
			printf("Encerrando o programa...");
			break;
    
	}  
	} while (choice != 0);
    
}

int main (){
	char fclientetitular[] = "arq-clientes-titulares.txt";
	char fclientedependente[] = "arq-clientes-dependentes.txt";

	fp_cliente_titular = abrir_criar_arquivo((char*)fclientetitular, fp_cliente_titular);
	fp_cliente_dependente = abrir_criar_arquivo((char*)fclientedependente, fp_cliente_dependente);
    
	menu();

	return 0;
}
