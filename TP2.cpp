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
        cout<<"funcionario cadastrado com sucesso!"<<endl;
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
    if(lista->inicio==NULL){
       cout<<"Nenhum funcionario cadastrado!"<<endl;
    }
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

funcionario* substituto(funcionario *lista){
    funcionario *ajuda = lista;

    while(ajuda->esq != NULL){
        ajuda=ajuda->esq;
    }
    cout<<ajuda->cpf<<" No *"<<endl;
    return ajuda;
}

void removerCPF(funcionario *aux, string palavra){
    if(aux==NULL){
        return;
    }
    cout<<"Cheguei papai"<<endl;
    cout<<aux->cpf<<endl;
    cout<<palavra<<endl;

    if(aux->cpf==palavra){
        if(aux->dir==NULL && aux->esq==NULL){
            if(aux->info->dir!=NULL){
                if(aux->info->dir->cpf==palavra){
                    aux->info->dir=NULL;
                }
            }
            if(aux->info->esq!=NULL){
                if(aux->info->esq->cpf==palavra){
                    aux->info->esq=NULL;
                }
            }
            cout<<aux->cpf<<"Removeu"<<endl;
            delete aux;
            return;
        }
        if(aux->dir==NULL && aux->esq!=NULL){
            if(aux->info->dir!=NULL){
                if(aux->info->dir->cpf==palavra){
                    aux->info->dir=aux->esq;
                    aux->esq->info=aux->info;
                }
            }
            if(aux->info->esq!=NULL){
                if(aux->info->esq->cpf==palavra){
                    aux->info->esq=aux->esq;
                    aux->esq->info=aux->info;
                }
            }
            cout<<aux->cpf<<"Removeu"<<endl;
            delete aux;
            return;
        }
        if(aux->dir!=NULL && aux->esq==NULL){
            if(aux->info->dir!=NULL){
                if(aux->info->dir->cpf==palavra){
                    aux->info->dir=aux->dir;
                    aux->dir->info=aux->info;
                }
            }
            if(aux->info->esq!=NULL){
                if(aux->info->esq->cpf==palavra){
                    aux->info->esq=aux->dir;
                    aux->dir->info=aux->info;
                }
            }
            cout<<aux->cpf<<"Removeu"<<endl;
            delete aux;
            return;
        }

        if(aux->dir!=NULL && aux->esq!=NULL){
            funcionario *sub = substituto(aux->dir);
            cout<<aux->cpf<<endl;
            cout<<sub->cpf<<endl;
            if(sub->dir == NULL && sub->esq == NULL){
                if(sub->cpf == aux->dir->cpf){
                    sub->esq=aux->esq;
                    sub->info=aux->info;
                    aux->esq->info=sub;
                    if(aux->info->dir!=NULL){
                        if(aux->info->dir->cpf==palavra){
                            aux->info->dir=sub;
                        }
                    }
                    if(aux->info->esq!=NULL){
                        if(aux->info->esq->cpf==palavra){
                            aux->info->esq=sub;
                        }
                    }
                    cout<<aux->cpf<<"Removeu"<<endl;
                    delete aux;
                    return;
                }
                sub->dir=aux->dir;
                sub->esq=aux->esq;
                sub->info->esq=NULL;
                sub->info=aux->info;
                aux->dir->info=sub;
                aux->esq->info=sub;
                if(aux->info->dir!=NULL){
                    if(aux->info->dir->cpf==palavra){
                        aux->info->dir=sub;
                    }
                }
                if(aux->info->esq!=NULL){
                    if(aux->info->esq->cpf==palavra){
                        aux->info->esq=sub;
                    }
                }
                cout<<aux->cpf<<"Removeu"<<endl;
                delete aux;
                return;
            }
            
            sub->esq=aux->esq;
            sub->info=aux->info;
            aux->esq->info=sub;
            if(aux->info->dir!=NULL){
                if(aux->info->dir->cpf==palavra){
                    aux->info->dir=sub;
                }
            }
            if(aux->info->esq!=NULL){
                if(aux->info->esq->cpf==palavra){
                    aux->info->esq=sub;
                }
            }
            cout<<aux->cpf<<"Removeu"<<endl;
            delete aux;
            
            return;
        }
    }

    if(aux->esq!=NULL){
        removerCPF(aux->esq, palavra);
    }
    if(aux->dir!=NULL){
        removerCPF(aux->dir, palavra);
    }
}

void removerRAIZ(funcionariolista *lista, string palavra){
    funcionario *aux;
    aux=lista->inicio;

    if(aux->info==NULL){
        if(aux->esq==NULL && aux->dir==NULL){
            cout<<aux->cpf<<"Removeu1"<<endl;
            lista->inicio=NULL;
            delete aux;
            return;
        }
        if(aux->dir != NULL){
            funcionario *sub = substituto(aux->dir);
            if(sub->dir == NULL && sub->esq == NULL){
                if(sub->cpf == aux->dir->cpf){
                    if(aux->esq != NULL){
                        sub->esq=aux->esq;
                        aux->esq->info=sub;
                    }
                    sub->info=NULL;
                    lista->inicio=sub;
                    cout<<aux->cpf<<"Removeu2"<<endl;
                    delete aux;
                    return;
                }
                aux->dir->info=sub;
                sub->info->esq=NULL;
                sub->dir=aux->dir;
                if(aux->esq != NULL){
                    sub->esq=aux->esq;
                    aux->esq->info=sub;
                }
                sub->info=NULL;
                lista->inicio=sub;
                cout<<aux->cpf<<"Removeu3"<<endl;
                delete aux;
                return;
            }
            if(aux->esq != NULL){
                sub->esq=aux->esq;
                aux->esq->info=sub;
            }
            sub->dir->info=sub->info;
            aux->dir->info=sub;
            sub->info=NULL;
            lista->inicio=sub;
            cout<<aux->cpf<<"Removeu4"<<endl;
            delete aux;
            return;
        }else{
            aux->esq->info=NULL;
            lista->inicio=aux->esq;
            cout<<aux->cpf<<" Removeu5"<<endl;
            delete aux;
            return;
        }
    }
}

void remover(funcionariolista *lista){
    funcionario *aux;
    aux=lista->inicio;

    int ajuda=1, removido=0;
    string palavra;
    cout<<"Insira o CPF do funcionario: ";
    cin>>palavra;
    // ajuda=verificaCPF(aux, palavra);
    if(ajuda==0){
        cout<<"Nao foi possivel localizar os dados do CPF, verifique se esta correto!"<<endl;
    }else{
        if(aux->info==NULL){
            cout<<"removendo raiz"<<endl;
            removerRAIZ(&*lista, palavra);
        }else{
            removerCPF(aux, palavra);
        }
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
            system("pause");
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