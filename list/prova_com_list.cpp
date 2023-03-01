#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <list>

#include <iostream>



using namespace std;



struct cliente_t{

	char nome[50];

	int codigo;

	int idade; 
	cliente_t *titular;
};



std::list<cliente_t*> clientes;



    

void cliente_cadastrar (){

	cliente_t *titular = new cliente_t;



	cout  <<"Digite o codigo do Titular:\n";

	scanf("%i", &titular->codigo);

	

	cout  <<"Digite o nome do Titular:\n";

	scanf("%s", titular->nome);

    

	cout  <<"Digite a idade do Titular:\n";

	scanf("%i", &titular->idade);

    

	clientes.push_back(titular);



}



void listar_todos_clientes (){

	printf("\n");

	

	for (const auto& c : clientes) {

		cout  << "Código:" << c->codigo << std::endl << "Nome: " << c->nome << std::endl << "Idade: " << c->idade << std::endl;

	}

}



void cliente_alterar(){

	int codigoAlterar;

    

	cout << "Digite o código do Titular a ser editado: ";

	scanf(" %d", &codigoAlterar);

    

	auto it = clientes.begin();
	printf(it);

//	while (it != clientes.end()){

//		if (it.codigo == codigoAlterar){

//			cout<<"Digite o nome do Titular:\n";

//			cin >> it->nome;

//			

//			cout<<"Digite a idade do Titular:\n";

//			cin >> it->idade;

//			

//			cout<<"Titular alterado com sucesso!\n";

//			break;

//		}else{

//			++it;

//		}

	}

	

	cout<<"Nao foi encontrado nenhum titular com esse código...\n";

     

}



void cliente_excluir(){

	int codigoExcluir;

    

	cout<<"Digite o Código do Titular a ser excluido: ";

	scanf(" %i", &codigoExcluir);



	auto it = clientes.begin();

	while (it != clientes.end()){

		if (it->codigo == codigoExcluir){

			it = clientes.erase(it);
			delete it;
			break;

		}else{

			++it;

		}

	}

	listar_todos_clientes();

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

				cliente_dependente_alterar();

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

	menu();

	return 0;

}