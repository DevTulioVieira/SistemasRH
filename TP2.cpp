#include <iostream>
#include <iomanip>
#include <time.h>
#include <fstream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <windows.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "lista.hpp"
#include "funcoes.cpp"

using namespace std;

int main(){
    int opcao;

    funcionariolista F1;//cria a estrutura de dados

    iniciofuncionario(&F1);

    carregarDados(&F1);//carregar os dados do funcionarios salvos

    for(;;){//mantem loop ate fecha o programa
        limpar();
        menu();//chama o menu
        cin>>opcao;
        limpar();
        switch (opcao){//para trabalho com a opçao desejada da opcao selecionada
        case 1:
            cadastro(&F1);
            system("pause");
        break;

        case 2:
            localizar(&F1);
            system("pause");
        break;

        case 3:
            remover(&F1);
            system("pause");
        break;

        case 4:
            mostracadastros(&F1);
            system("pause");
        break;

        case 5:
            salvarDados(&F1);
            exit(0);//finaliza o programa saindo do loop e fechando o mesmo
        break;
        }
    }
}