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

void verificaCPF(funcionario *aux, string palavra, int *ajuda){
    if(aux==NULL){
        return;
    }
    if(aux->dir!=NULL){
        verificaCPF(aux->dir, palavra, &*ajuda);
    }
    if(aux->esq!=NULL){
        verificaCPF(aux->esq, palavra, &*ajuda);
    }
    if(aux->cpf==palavra){
        *ajuda=1;
        return;
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

    int opcao, ajuda=0;

    cout<<"Cadastramento de novo funcionario!"<<endl;
    cout<<"Insira os dados pedidos a seguir"<<endl;
    cin.ignore();
    cout<<"\nNome completo:                    ";
    cin>>novo->nome;
    cout<<"\nCPF(exemplo:123.456.789-10):      ";
    cin>>novo->cpf;
    cout<<"\nEndereco:                         ";
    cin>>novo->endereco;
    cout<<"\nCargo:                            ";
    cin>>novo->cargo;
    cout<<"\nTelefone(exemplo:(33)99674-1371): ";
    cin>>novo->telefone;
    cout<<"\nData Inicio(exemplo:dd/mm/yyyy):  ";
    cin>>novo->data;
    cout<<"\nMatricula:                        ";
    cin>>novo->matricula;
    limpar();
    
    novo->dir=NULL;
    novo->esq=NULL;

    if (lista->inicio == NULL){
        lista->inicio = novo;
        novo->info=NULL;
        cout<<"funcionario cadastrado com sucesso!"<<endl;
    }else{
        cpfErro:
        verificaCPF(raiz, novo->cpf, &ajuda);
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
    busca(aux->esq);
    cout<<"Nome:      "<<aux->nome<<endl;
    cout<<"Cpf:       "<<aux->cpf<<endl;
    cout<<"Endereco:  "<<aux->endereco<<endl;
    cout<<"Cargo:     "<<aux->cargo<<endl;
    cout<<"Telefone:  "<<aux->telefone<<endl;
    cout<<"Data:      "<<aux->data<<endl;
    cout<<"Matricula: "<<aux->matricula<<endl<<endl;
    busca(aux->dir);

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
        cout<<"Nome:      "<<aux->nome<<endl;
        cout<<"Cpf:       "<<aux->cpf<<endl;
        cout<<"Endereco:  "<<aux->endereco<<endl;
        cout<<"Cargo:     "<<aux->cargo<<endl;
        cout<<"Telefone:  "<<aux->telefone<<endl;
        cout<<"Data:      "<<aux->data<<endl;
        cout<<"Matricula: "<<aux->matricula<<endl<<endl;
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
    return ajuda;
}

void removerCPF(funcionario *aux, string palavra){
    if(aux==NULL){
        return;
    }

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

    if(aux->esq==NULL && aux->dir==NULL){
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
        delete aux;
        return;
    }else{
        aux->esq->info=NULL;
        lista->inicio=aux->esq;
        delete aux;
        return;
    }
}

void remover(funcionariolista *lista){
    funcionario *aux;
    aux=lista->inicio;
    
    repetindo:
    int ajuda=0, erro;
    string palavra;
    cout<<"Insira o CPF do funcionario: ";
    cin>>palavra;
    procura(aux, palavra, &ajuda);
    if(ajuda==0){
        cout<<"Nao foi possivel localizar os dados do funcionario!"<<endl;
        cout<<"Insira novamente os dados:(1.sim/2.nao) ";
        cin>>erro;
        if(erro==1){
            limpar();
            goto repetindo;
        }else{
            return;
        }
    }else{
        if(aux->cpf==palavra){
            removerRAIZ(&*lista, palavra);
        }else{
            removerCPF(aux, palavra);
        }
        cout<<"Removido"<<endl;
    }
}

void salvando(funcionario *aux){
    if(aux==NULL){
        return;
    }
    ofstream outFile;
    outFile.open("funcionarios.txt", ios::app);
    if(!outFile){ 
        cout<<"Arquivo saida.txt nao pode ser aberto"<<endl;
        abort();
    }
    outFile<<aux->nome<<" "<<aux->cpf<<" "<<aux->endereco<<" "<<aux->cargo<<" "<<aux->telefone<<" "<<aux->data<<" "<<aux->matricula<<"\n";
    outFile.close();
    if(aux->dir!=NULL){
        salvando(aux->dir);
    }
    if(aux->esq!=NULL){
        salvando(aux->esq);
    }
}

void carregarDados(funcionariolista *lista){
    funcionario *novo, *raiz;
    novo = new funcionario;
    raiz=lista->inicio;
    novo->dir=NULL;
    novo->esq=NULL;

    ifstream inFile;
    inFile.open("funcionarios.txt", ios::in);
    if (!inFile){ 
        cout<<"Arquivo saida.txt nao pode ser aberto"<<endl;
        abort();
    }

    while(inFile>>novo->nome>>novo->cpf>>novo->endereco>>novo->cargo>>novo->telefone>>novo->data>>novo->matricula){
        if (lista->inicio == NULL){
            lista->inicio = novo;
            novo->info=NULL;
        }else{
            inserirNaArvore(raiz, novo);
        }
        novo->dir=NULL;
        novo->esq=NULL;
        novo = new funcionario;
        raiz=lista->inicio;
    }
    inFile.close();
    limpar();
    cout<<"Dados carregados com sucesso..."<<endl;
    system("pause");
}

void salvarDados(funcionariolista *lista){
    int x;
    cout<<"Deseja salva os dados: (1.sim/2.nao) ";
    cin>>x;
    if(x!=1){
        return;
    }

    funcionario *aux;
    aux=lista->inicio;
    
    ofstream outFile;
    outFile.open("funcionarios.txt", ios::out);
    if(!outFile){ 
        cout<<"Arquivo saida.txt nao pode ser aberto"<<endl;
        abort();
    }
    outFile.close();

    if(aux==NULL){
        cout<<"Nenhum Dado para salva!"<<endl;
    }else{
        salvando(aux);
    }
    cout<<"salvo com sucesso!"<<endl;
}

int main(){
    int opcao;
    int repetidor=0;

    funcionariolista F1;

    iniciofuncionario(&F1);

    carregarDados(&F1);

    for(;;){
        limpar();
        menu();
        cin>>opcao;
        limpar();
        switch (opcao){
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
            exit(0);
        break;
        }
    }
}