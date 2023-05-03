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

typedef struct funcionarioL{
    int matricula;
    string cpf;
    string nome;
    char endereco[100];
    char cargo[30];
    char telefone[15];
    char data[10];
    struct funcionarioL*dir;
    struct funcionarioL*esq;
    struct funcionarioL*info;
}funcionario;

typedef struct lista{
    funcionario *inicio;
}funcionariolista;

void iniciofuncionario(funcionariolista *lista){
    lista->inicio=NULL;
}

void limpar(){
    system("cls");
}

void menu(){
    cout<<"******************************"<<endl;
    cout<<"*1.Cadastro de Funcionarios  *"<<endl;
    cout<<"*2.Busca de Funcionario      *"<<endl;
    cout<<"*3.Remocao de Funcionario    *"<<endl;
    cout<<"*4.Mostra Todos Funcionarios *"<<endl;
    cout<<"*5.Fechar programa           *"<<endl;
    cout<<"******************************"<<endl;
    cout<<"\nEscolha o que deseja fazer: "<<endl;
}

int verificaCPF(funcionario *aux, string palavra){
    if(aux==NULL){
        return 0;
    }
    if(aux->cpf==palavra){
        return 1;
    }
    if(aux->dir!=NULL){
        return verificaCPF(aux->dir, palavra);
    }
    if(aux->esq!=NULL){
        return verificaCPF(aux->esq, palavra);
    }
}

void inserirNaArvore(funcionario *aux, funcionario *novo){
    if(novo->cpf>aux->cpf){
        if(aux->dir==NULL){
            novo->info=aux;
            aux->dir=novo;
            cout<<"funcionario cadastrado com sucesso!"<<endl;
            return;
        }else{
            inserirNaArvore(aux->dir, novo);
        }  
    }
    if(novo->cpf<aux->cpf){
        if(aux->esq==NULL){
            novo->info=aux;
            aux->esq=novo;
            cout<<"funcionario cadastrado com sucesso!"<<endl;
            return;
        }else{
            inserirNaArvore(aux->esq, novo);
        }
    }
}

void cadastro(funcionariolista *lista){
    funcionario *novo, *raiz;
    novo = new funcionario;
    raiz=lista->inicio;

    int opcao, ajuda, aux=0;

    cout<<"Cadastramento de novo funcionario!"<<endl;
    cout<<"Insira os dados pedidos a seguir"<<endl;
    cin.ignore();
    // cout<<"\nNome completo:                    ";
    // gets(novo->nome);
    cout<<"\nCPF(exemplo:123.456.789-10):      ";
    cin>>novo->cpf;
    // cout<<"\nEndereco:                         ";
    // gets(novo->endereco);
    // cout<<"\nCargo:                            ";
    // gets(novo->cargo);
    // cout<<"\nTelefone(exemplo:(33)99674-1371): ";
    // gets(novo->telefone);
    // cout<<"\nData Inicio(exemplo:dd/mm/yyyy):  ";
    // gets(novo->data);
    // cout<<"\nMatricula:                        ";
    // cin>>novo->matricula;
    limpar();
    
    novo->dir=NULL;
    novo->esq=NULL;

    if (lista->inicio == NULL){
        lista->inicio = novo;
        novo->info=NULL;
    }else{
        cpfErro:
        ajuda=verificaCPF(raiz, novo->cpf);
        if(ajuda==1){
            cout<<"O CPF informado ja se encontra cadastrado!"<<endl;
            cout<<"Deseja Inserir novamente o CPF(1.sim/2.nao): ";
            cin>>opcao;
            if(opcao==1){
                cout<<"Insira um CPF valido: ";
                cin>>novo->cpf;
                raiz=lista->inicio;
                goto cpfErro;
            }else{
                delete novo;
                free(novo);
                cout<<"Nao foi possivel cadastra funcionario"<<endl;
                cout<<"Erro Duplicate funcionarios.cpf 403!"<<endl;
                return;
            }
        }
        inserirNaArvore(raiz, novo);
    }
}

void busca(funcionario *aux){
    if(aux==NULL){
        return;
    }
    // cout<<"\nNome: "<<aux->nome<<endl;
    busca(aux->esq);
    cout<<"Cpf: "<<aux->cpf<<endl;
    busca(aux->dir);
    //fgbdicaeh ordem de teste
}

void mostracadastros(funcionariolista *lista){
    funcionario *aux;
    aux=lista->inicio;
    busca(aux);
}

void procura(funcionario *aux, string palavra, int *ajuda){
    if(aux==NULL){
        return;
    }
    if(aux->cpf==palavra || aux->nome==palavra){
        cout<<"Resultado da busca! "<<endl;
        // cout<<"Nome: "<<aux->nome<<endl;
        cout<<"Cpf: "<<aux->cpf<<endl;
        // cout<<"Cpf: "<<aux->cpf<<endl;
        // cout<<"Cpf: "<<aux->cpf<<endl;
        *ajuda=1;
    }
    if(aux->dir!=NULL){
        procura(aux->dir, palavra, &*ajuda);
    }
    if(aux->esq!=NULL){
        procura(aux->esq, palavra, &*ajuda);
    }
}

void localizar(funcionariolista *lista){
    funcionario *aux;
    aux=lista->inicio;

    int opcao, ajuda=0;
    string palavra;

    if(aux==NULL){
        cout<<"Nao ha dados para sua busca, favor cadastra os dados do funcionario!"<<endl;
    }else{
        iniciobusca:
        limpar();
        cout<<"Insira o nome/CPF para busca: ";
        cin>>palavra;
        procura(aux, palavra, &ajuda);
        if(ajuda==0){
            cout<<"Nao foi posivel localizar o funcionario, certifique-se que o nome esteja correto";
            cout<<"Nova busca?(1.sim/2.nao): ";
            cin>>opcao;
            if(opcao==1){
                goto iniciobusca;
            }
        }else{
            cout<<"Busca completa!"<<endl;
        }
    }

}

int removerCPF(funcionario *aux, string palavra){
    if(aux==NULL){
        return 0;
    }
    if(aux->cpf==palavra){
        if(aux->dir==NULL && aux->esq==NULL){
            if(aux->info->dir->cpf==palavra){
                aux->info->dir=NULL;
            }
            if(aux->info->esq->cpf==palavra){
                aux->info->esq=NULL;
            }
            free(aux);
        }
        if(aux->dir==NULL && aux->esq==NULL){
            if(aux->info->dir->cpf==palavra){
                aux->info->dir=NULL;
            }
            if(aux->info->esq->cpf==palavra){
                aux->info->esq=NULL;
            }
            free(aux);
        }


        return 1;
    }
    if(aux->dir!=NULL){
        return removerCPF(aux->dir, palavra);
    }
    if(aux->esq!=NULL){
        return removerCPF(aux->esq, palavra);
    }
}
void remover(funcionariolista *lista){
    funcionario *aux;
    aux=lista->inicio;

    int ajuda=0, removido=0;
    string palavra;
    cout<<"Insira o CPF do funcionario: ";
    cin>>palavra;
    ajuda=verificaCPF(aux, palavra);
    if(ajuda==0){
        cout<<"Nao foi possivel localizar os dados do CPF, verifique se esta correto!"<<endl;
    }else{
        removido=removerCPF(aux, palavra);
    }

}

int main(){
    int opcao;
    int repetidor=0;

    funcionariolista F1;

    iniciofuncionario(&F1);

    for(;;){
        limpar();
        menu();
        cin>>opcao;
        limpar();
        switch (opcao){
        case 1:
            cadastro(&F1);
            system("pause");
            system("cls");
        break;

        case 2:
            localizar(&F1);
        break;

        case 3:
            remover(&F1);
        break;

        case 4:
            mostracadastros(&F1);
            system("pause");
        break;

        case 5:
            exit(0);
        break;
        }
    }
}