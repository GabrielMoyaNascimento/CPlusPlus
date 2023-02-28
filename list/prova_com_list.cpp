#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list>
#include <iostream>

using namespace std;

struct cliente_titular_t
{
    char nome[50];
    int codigo;
    int idade; 
};

struct cliente_dependente_t
{
    char nome[50];
    int codigo;
    int idade; 
    cliente_titular_t titular;
    
};

    FILE *fp_cliente_titular;
    FILE *fp_cliente_dependente;
	std::list<cliente_titular_t> clientes_titulares;	
    std::list<cliente_dependente_t> clientes_dependentes;
    
void cliente_titular_cadastrar ()
{
	cliente_titular_t titular;

	printf("Digite o codigo do Titular:\n");
    scanf("%i", &titular.codigo);
	
	printf("Digite o nome do Titular:\n");
    scanf("%s", titular.nome);
    
    printf("Digite a idade do Titular:\n");
    scanf("%i", &titular.idade);
    
    clientes_titulares.push_back(titular);

}

void listar_todos_clientes_titulares ()
{
	printf("\n");
	
    for (const auto& c : clientes_titulares) {
	  cout  << "Código:" << c.codigo << std::endl << "Nome: " << c.nome << std::endl << "Idade: " << c.idade << std::endl;
    }
}

void cliente_titular_alterar(){
    int codigoAlterar;
    
    //printf("Digite o Nome do Titular a ser editado: ");
    //scanf("%i", &codigo);
    
    auto it = clientes_titulares.begin();
    while (it != clientes_titulares.end())
    {
		if (it->codigo == codigoAlterar)
        {
            printf("Digite o codigo do Titular:\n");
			scanf("%i", &it->codigo);
			
			printf("Digite o nome do Titular:\n");
			scanf("%s", it->nome);
			
			printf("Digite a idade do Titular:\n");
			scanf("%i", &it->idade);
        }
        else
        {
            ++it;
        }
    }
	

    printf("Nao foi encontrado nenhum titular com esse nome...\n");
     
}

void cliente_titular_excluir(){
    int codigoExcluir;
    
    printf("Digite o Código do Titular a ser excluido: ");
    scanf(" %i", &codigoExcluir);

    auto it = clientes_titulares.begin();
    while (it != clientes_titulares.end())
    {
		if (it->codigo == codigoExcluir)
        {
            it = clientes_titulares.erase(it);
        }
        else
        {
            ++it;
        }
    }
	
	listar_todos_clientes_titulares();
}


void cliente_dependente_cadastrar ()
{
	cliente_dependente_t dependente;
	int codigoTitular;

	printf("Digite o codigo do Dependente:\n");
    scanf("%i", &dependente.codigo);
	
	printf("Digite o nome do Dependente:\n");
    scanf("%s", dependente.nome);
    
    printf("Digite a idade do Dependente:\n");
    scanf("%i", &dependente.idade);
    
    printf("Digite o código do Titular:\n");
    scanf("%i", &codigoTitular);
    
    auto it = clientes_titulares.begin();
    while (it != clientes_titulares.end())
    {
		if (it->codigo == codigoTitular)
        {
            dependente.titular= it;
        }
        else
        {
            ++it;
        }
    }
}

void listar_todos_clientes_dependentes ()
{
	printf("\n");
	
    for (const auto& c : clientes_dependentes) {
	  cout  << "Código:" << c.codigo << std::endl << "Nome: " << c.nome << std::endl << "Idade: " << c.idade << std::endl<< "Titular: " << 				c.titular.nome << std::endl;
    }
}

void cliente_dependente_alterar(){
    cliente_dependente_t dependente;
    char nome[50];
    
    fseek(fp_cliente_dependente, 0, SEEK_SET);

    printf("Digite o Nome do Dependente a ser editado: ");
    scanf(" %s", nome);
    
    while(fread(&dependente, sizeof(cliente_dependente_t), 1, fp_cliente_dependente) == 1)
    { printf("Posicao: %i\n", ftell(fp_cliente_dependente));
        
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
    char nome[50];
    
    fseek(fp_cliente_dependente, 0, SEEK_SET);

    printf("Digite o Nome do Dependente a ser excluido: ");
    scanf(" %s", nome);
    
    while(fread(&dependente, sizeof(cliente_dependente_t), 1, fp_cliente_dependente) == 1)
    { printf("Posicao: %i\n", ftell(fp_cliente_dependente));
        
        if(strcmp(dependente.nome, nome)==0){
          
            break;
        } 
        
    }
    printf("Nao foi encontrado nenhum dependente com esse nome...\n");
     
}

void menu() 
{
    int choice;
    
      do 
      {
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
        
        switch(choice)
        {
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

int main ()
{


    menu();

	return 0;
}
