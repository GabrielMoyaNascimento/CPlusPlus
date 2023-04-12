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

void cliente_cadastrar() {
    static int ultimo_codigo = 0;
    char ehTitular = 'N';
    int codigoTitular;
    cliente_t *cliente = new cliente_t;
    cliente->codigo = ++ultimo_codigo;
    cout << "Digite o nome do cliente:\n";
    scanf("%s", cliente->nome);
    cout << "Digite a idade do cliente:\n";
    scanf("%i", &cliente->idade);
    cout << "Será o titular? (S/N) \n";
    scanf(" %c", &ehTitular);
    if (ehTitular == 'S') {
        cliente->titular = NULL;
    } else {
    	do {
		    cout << "Informe o código do titular: \n";
		    scanf("%i", &codigoTitular);
		    for (auto it = clientes.begin(); it != clientes.end(); it++) {
		        if ((*it)->codigo == codigoTitular && (*it)->titular == NULL) {
		            cliente->titular = *it;
		            break;
		        }
		    }
		    
		    if(codigoTitular == 0) {
				delete cliente;
		    
		    	return;
		    }
		    
		    if (cliente->titular == NULL) {
		        cout << "Titular inválido ou já possui um titular ou informe 0 para voltar ao menu\n";
		    }
    	} while(cliente->titular == NULL);
    }
    cout << "\n";
    clientes.push_back(cliente);
}


	

void listar_todos_clientes (){

	cout  <<"\n";

	for (const auto c : clientes) {

		cout  << "Código:" << c->codigo << std::endl << "Nome: " << c->nome << std::endl << "Idade: " << c->idade << std::endl;
		cout << "\n";

	}
}

void cliente_alterar(){

	int codigoAlterar;

	cout << "Digite o código a ser editado: ";

	scanf(" %d", &codigoAlterar);

	auto it = clientes.begin();
	for (auto it = clientes.begin(); it != clientes.end(); ++it) {
	
		cliente_t *c = *it;

		if (c->codigo == codigoAlterar) {
		
		    cout << "Digite o nome do cliente:\n";
		    cin >> c->nome;

		    cout << "Digite a idade do cliente:\n";
		    cin >> c->idade;

		    cout << "Cliente alterado com sucesso!\n";
		    return;
		    
		}
	}


	cout<<"Nao foi encontrado cliente com esse código...\n";

}

void cliente_excluir(){
	int codigoExcluir;
	cout << "Digite o código do cliente a ser excluído: ";
	cin >> codigoExcluir;

	auto it = clientes.begin();
	while (it != clientes.end()) {
		cliente_t *c = *it;

		if (c->codigo == codigoExcluir) {
		    if (c->titular == NULL) {
		        bool temDependentes = false;
		        for (const auto c2 : clientes) {
		            if (c2->titular == c) {
		                temDependentes = true;
		                break;
		            }
	            }
		        if (temDependentes) {
		            cout << "O cliente não pode ser excluído porque é um titular e tem dependentes." << endl;
		        } else {
		            delete *it;
		            it = clientes.erase(it);
		            cout << "Cliente excluído com sucesso!" << endl;
		        }

		    }else {
		        delete *it;
		        it = clientes.erase(it);
		        cout << "Cliente excluído com sucesso!" << endl;
		    }
		    break;
		} else {
		    it++;
		}
	}

	listar_todos_clientes();

}



void menu() {

	int choice;

    	do {

		cout  <<"\n ===== Clientes Cplusplus ===== \n"; 

		cout  <<"Escolha as opcoes abaixo: \n";        

		cout  <<" 1 - Cadastrar Cliente \n"; 

		cout  <<" 2 - Listar todos os Clientes \n";

		cout  <<" 3 - Alterar Cliente \n";

		cout  <<" 4 - Excluir Cliente \n";

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
