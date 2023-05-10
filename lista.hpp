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

using namespace std;

#ifndef LISTA_H
#define LISTA_H

//estrutura basica para armazenar infomação do funcionario
typedef struct funcionarioL{
    int matricula;
    string cpf;
    string nome;
    string endereco;
    string cargo;
    string telefone;
    string data;
    struct funcionarioL*dir;
    struct funcionarioL*esq;
    struct funcionarioL*info;
}funcionario;

typedef struct lista{
    funcionario *inicio;
}funcionariolista;
//inicia a arvore

void limpar();

void menu();

void verificaCPF(funcionario *aux, string palavra, int *ajuda);

void inserirNaArvore(funcionario *aux, funcionario *novo);

void cadastro(funcionariolista *lista);

void busca(funcionario *aux);

void procura(funcionario *aux, string palavra, int *ajuda);

void localizar(funcionariolista *lista);

funcionario* substituto(funcionario *lista);

void removerCPF(funcionario *aux, string palavra);

void removerRAIZ(funcionariolista *lista, string palavra);

void remover(funcionariolista *lista);

void salvando(funcionario *aux);

void carregarDados(funcionariolista *lista);

void salvarDados(funcionariolista *lista);

#endif