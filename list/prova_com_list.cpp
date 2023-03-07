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

	cout  <<"Digite o código do cliente:\n";

	scanf("%i", &titular->codigo);

	cout  <<"Digite o nome do cliente:\n";

	scanf("%s", titular->nome);

	cout  <<"Digite a idade do cliente:\n";

	scanf("%i", &titular->idade);

	clientes.push_back(titular);

}

void listar_todos_clientes (){

	cout  <<"\n";

	for (const auto& c : clientes) {

		cout  << "Código:" << c->codigo << std::endl << "Nome: " << c->nome << std::endl << "Idade: " << c->idade << std::endl;

	}
}

void cliente_alterar(){

	int codigoAlterar;

	cout << "Digite o código a ser editado: ";

	scanf(" %d", &codigoAlterar);

	auto it = clientes.begin();
	while (it != clientes.end()){
			cliente_t *c = *it;
			listar_todos_clientes();

		if (c->codigo == codigoAlterar){

			cout<<"Digite o nome do cliente:\n";

			cin >> c->nome;

			cout<<"Digite a idade do cliente:\n";

			cin >> c->idade;

			cout<<"Cliente alterado com sucesso!\n";

			break;

		}else{

			++it;

		}
	}

	cout<<"Nao foi encontrado nenhum cliente com esse código...\n";

}

void cliente_excluir(){

	int codigoExcluir;

	cout<<"Digite o Código a ser excluido: ";

	scanf(" %i", &codigoExcluir);

	auto it = clientes.begin();
	cliente_t *c = *it;

	while (it != clientes.end()){

		if (c->codigo == codigoExcluir){

			it = clientes.erase(it);
			delete c;
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

		cout  <<"\n ===== Clientes Cplusplus ===== \n"; 

		cout  <<"Escolha as opcoes abaixo: \n";        

		cout  <<" 1 - Cadastrar Cliente cliente \n"; 

		cout  <<" 2 - Listar todos os Clientes \n";

		cout  <<" 3 - Alterar Cliente cliente \n";

		cout  <<" 4 - Excluir Cliente cliente \n";

        cout  <<" 0 - Sair ...\n"; 

		cout  <<"Digite sua escolha: ";

		scanf("%i", &choice);

		switch(choice){

		    case 1:
				cliente_cadastrar();
				break;
			
		    case 2:
				listar_todos_clientes();
				break;
		    
		    case  3:
				cliente_alterar();
				break;
		    
		    case  4:
				cliente_excluir();
				break;

		    case  0:
				cout  <<"Encerrando o programa...";
				break;
		}  

	} while (choice != 0);

}

int main (){

	menu();

	return 0;

}
