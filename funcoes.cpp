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


void limpar(){
    system("cls");
}

void iniciofuncionario(funcionariolista *lista){
    lista->inicio=NULL;
}
//menu inicial
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
//verifica se existti a busca por funcionario, dizendo 1 para ajuda que foi localizado os dados
//ou que pode prosseguir que nao quebrara o codigo
void verificaCPF(funcionario *aux, string palavra, int *ajuda){
    if(aux==NULL){
        return;
    }
    if(aux->dir!=NULL){
        verificaCPF(aux->dir, palavra, &*ajuda);//funcao recursiva
    }
    if(aux->esq!=NULL){
        verificaCPF(aux->esq, palavra, &*ajuda);
    }
    if(aux->cpf==palavra){
        *ajuda=1;
        return;
    }
}
//inserir na arvore um dado
void inserirNaArvore(funcionario *aux, funcionario *novo){
    //vai anda pela arvore ate acha uma casa vazia e cadastra os devidos ponteiros
    if(novo->cpf>aux->cpf){//verifica se deve ir para direita ou esquerda
        if(aux->dir==NULL){//caso esteja vazia ele adciona a direita
            novo->info=aux;
            aux->dir=novo;
            cout<<"funcionario cadastrado com sucesso!"<<endl;
            return;
        }else{
            inserirNaArvore(aux->dir, novo);//caso nao, ele vai para a direita e repete
        }  
    }
    if(novo->cpf<aux->cpf){//verifica se deve ir para esquerda
        if(aux->esq==NULL){//caso seja vazio adciona a esquerda
            novo->info=aux;
            aux->esq=novo;
            cout<<"funcionario cadastrado com sucesso!"<<endl;
            return;
        }else{
            inserirNaArvore(aux->esq, novo);//caso nao, ele vai para a esquerda e repete
        }
    }
}
//cadastro faza as opera~çoes basica para saber de pode inserir entao chama inserirNaArvore
void cadastro(funcionariolista *lista){
    funcionario *novo, *raiz;
    novo = new funcionario;//criação de um novo endereço de memoria
    raiz=lista->inicio;

    int opcao, ajuda=0;
    //Inserção dos dados para esse endereço
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

    if (lista->inicio == NULL){//para quando a lista for vazia
        lista->inicio = novo;
        novo->info=NULL;
        cout<<"funcionario cadastrado com sucesso!"<<endl;
    }else{
        cpfErro:
        verificaCPF(raiz, novo->cpf, &ajuda);//busca para ver se nao esta repetindo o cpf
        if(ajuda==1){//se retorna 1, o cpf ja existe e tem a opcao de altera o cpf ou sair
            cout<<"O CPF informado ja se encontra cadastrado!"<<endl;
            cout<<"Deseja Inserir novamente o CPF(1.sim/2.nao): ";
            cin>>opcao;
            if(opcao==1){
                cout<<"Insira um CPF valido: ";//caso queira altera o cpf por ter digitado errado
                cin>>novo->cpf;
                raiz=lista->inicio;
                goto cpfErro;
            }else{
                delete novo;//libera a memoria, apagando os dados desse novo cadastro.
                free(novo);
                cout<<"Nao foi possivel cadastra funcionario"<<endl;
                cout<<"Erro Duplicate funcionarios.cpf 403!"<<endl;
                return;
            }
        }
        inserirNaArvore(raiz, novo);//insere na arvore caso passe pelo teste de duplicada de cpf
    }
}
//ira mostra os dados apos informa a raiz
void busca(funcionario *aux){
    if(aux==NULL){//se existir
        return;
    }
    //a ordem sera pelo cpf e nao pelo nome, ja que a inseção e feita com base no cpf par evita dados repetidos
    busca(aux->esq);//busca a esquerda
    cout<<"Nome:      "<<aux->nome<<endl;
    cout<<"Cpf:       "<<aux->cpf<<endl;
    cout<<"Endereco:  "<<aux->endereco<<endl;
    cout<<"Cargo:     "<<aux->cargo<<endl;
    cout<<"Telefone:  "<<aux->telefone<<endl;
    cout<<"Data:      "<<aux->data<<endl;
    cout<<"Matricula: "<<aux->matricula<<endl<<endl;
    busca(aux->dir);//busca a direita

}
//fara os calculos basico para mostra os dados em busca
void mostracadastros(funcionariolista *lista){
    funcionario *aux;
    aux=lista->inicio;
    if(lista->inicio==NULL){//verifica se existe dados
       cout<<"Nenhum funcionario cadastrado!"<<endl;
    }
    busca(aux);//vai mostra todos os dados nessa funçao, pois precisa se recursiva para se mais eficiente
}
//verifica se existe o cpf para remoção
void procura(funcionario *aux, string palavra, int *ajuda){
    if(aux==NULL){
        return;
    }
    if(aux->cpf==palavra || aux->nome==palavra){//mostra os dados que serao removidos
        cout<<"Nome:      "<<aux->nome<<endl;
        cout<<"Cpf:       "<<aux->cpf<<endl;
        cout<<"Endereco:  "<<aux->endereco<<endl;
        cout<<"Cargo:     "<<aux->cargo<<endl;
        cout<<"Telefone:  "<<aux->telefone<<endl;
        cout<<"Data:      "<<aux->data<<endl;
        cout<<"Matricula: "<<aux->matricula<<endl<<endl;
        *ajuda=1;
    }
    if(aux->dir!=NULL){//recursividade para percorre a arvore pela direita
        procura(aux->dir, palavra, &*ajuda);
    }
    if(aux->esq!=NULL){//recursividade para percorre a arvore pela esquerda
        procura(aux->esq, palavra, &*ajuda);
    }
}
//busca um nome ou cpf para o usuario
void localizar(funcionariolista *lista){
    funcionario *aux;
    aux=lista->inicio;

    int opcao, ajuda=0;
    string palavra;

    if(aux==NULL){//caso nao tenha dados para busca
        cout<<"Nao ha dados para sua busca, favor cadastra os dados do funcionario!"<<endl;
    }else{
        iniciobusca:
        limpar();
        cout<<"Insira o nome/CPF para busca: ";//a busca e feita por cpf ou nome retorna ambos
        cin>>palavra;
        procura(aux, palavra, &ajuda);//verifica se existe o cpf
        if(ajuda==0){//caso nao tenha o cpf pergunta se deseja pesquisa novamente
            cout<<"Nao foi posivel localizar o funcionario, certifique-se que o nome esteja correto";
            cout<<"Nova busca?(1.sim/2.nao): ";
            cin>>opcao;
            if(opcao==1){
                goto iniciobusca;//para busca o cpf novo
            }
        }else{
            cout<<"Busca completa!"<<endl;//busca concluida
        }
    }

}
//busca o ponteiro que sera substituto no elemento removivel
funcionario* substituto(funcionario *lista){
    funcionario *ajuda = lista;
    while(ajuda->esq != NULL){//sempre ira busca o maior elemento, indo para equerda
        ajuda=ajuda->esq;//caso tenha na esquerda ele ira anda se o maior elemento
    }
    return ajuda;//retorna o elemento que sera subtituto
}
//remove um ponteiro que nao seja a raiz
void removerCPF(funcionario *aux, string palavra){
    if(aux==NULL){
        return;
    }

    if(aux->cpf==palavra){//quando acha o ponteiro
        if(aux->dir==NULL && aux->esq==NULL){//verifica se é folha
            if(aux->info->dir!=NULL){//libera o local que esta ligado a direita ou esquerd apara que posse se inserido novos dados ali
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
        if(aux->dir==NULL && aux->esq!=NULL){//caso tenha um elemento a esquerda
            if(aux->info->dir!=NULL){//busca para saber se veio da direita e liga o anterios ao elemento filho
                if(aux->info->dir->cpf==palavra){
                    aux->info->dir=aux->esq;
                    aux->esq->info=aux->info;
                }
            }
            if(aux->info->esq!=NULL){//busca para saber se veio da esquerda e liga o anterios ao elemento filho
                if(aux->info->esq->cpf==palavra){
                    aux->info->esq=aux->esq;
                    aux->esq->info=aux->info;
                }
            }

            delete aux;
            return;
        }
        if(aux->dir!=NULL && aux->esq==NULL){//caso tenha um elemento a direita
            if(aux->info->dir!=NULL){
                if(aux->info->dir->cpf==palavra){//busca para saber se veio da direita e liga o anterios ao elemento filho
                    aux->info->dir=aux->dir;
                    aux->dir->info=aux->info;
                }
            }
            if(aux->info->esq!=NULL){
                if(aux->info->esq->cpf==palavra){//busca para saber se veio da esquerda e liga o anterios ao elemento filho
                    aux->info->esq=aux->dir;
                    aux->dir->info=aux->info;
                }
            }

            delete aux;
            return;
        }

        if(aux->dir!=NULL && aux->esq!=NULL){//caso tenha 2 filho
            funcionario *sub = substituto(aux->dir);//funcao para acha o substituto
            if(sub->dir == NULL && sub->esq == NULL){//verifica se é vazia os filhos
                if(sub->cpf == aux->dir->cpf){//verifica se o elemento a se removido e pai do que sera substituto
                    sub->esq=aux->esq;
                    sub->info=aux->info;
                    aux->esq->info=sub;
                    if(aux->info->dir!=NULL){//fazendo ligaça dos ponteiro
                        if(aux->info->dir->cpf==palavra){
                            aux->info->dir=sub;
                        }
                    }
                    if(aux->info->esq!=NULL){//fazendo ligaça dos ponteiro
                        if(aux->info->esq->cpf==palavra){
                            aux->info->esq=sub;
                        }
                    }
        
                    delete aux;
                    return;
                }
                //nessa caso aqui, o substituto nao é o filho do pai, e sera feita a ligação dos ponteiros
                sub->dir=aux->dir;
                sub->esq=aux->esq;
                sub->info->esq=NULL;
                sub->info=aux->info;
                aux->dir->info=sub;
                aux->esq->info=sub;
                if(aux->info->dir!=NULL){//mantem sua ligacao dos dados
                    if(aux->info->dir->cpf==palavra){
                        aux->info->dir=sub;
                    }
                }
                if(aux->info->esq!=NULL){//mantem sua ligacao dos dados
                    if(aux->info->esq->cpf==palavra){
                        aux->info->esq=sub;
                    }
                }
    
                delete aux;
                return;
            }
            //caso tenha um elemento a direita do elemento a se subtituido faz a ligação para nao perde a cadeia de dados, 
            //ligando ele no pai do elemento que sera substituido
            sub->esq=aux->esq;
            sub->info=aux->info;
            aux->esq->info=sub;
            if(aux->info->dir!=NULL){//mantem sua ligacao dos dados
                if(aux->info->dir->cpf==palavra){
                    aux->info->dir=sub;
                }
            }
            if(aux->info->esq!=NULL){//mantem sua ligacao dos dados
                if(aux->info->esq->cpf==palavra){
                    aux->info->esq=sub;
                }
            }

            delete aux;
            return;
        }
    }

    if(aux->esq!=NULL){//percorre a esquerda ate acha o cpf para remoção
        removerCPF(aux->esq, palavra);
    }
    if(aux->dir!=NULL){//percorre a direita ate acha o cpf para remoção
        removerCPF(aux->dir, palavra);
    }
}
//remover a raiz da arvore
void removerRAIZ(funcionariolista *lista, string palavra){
    funcionario *aux;
    aux=lista->inicio;

    if(aux->esq==NULL && aux->dir==NULL){//caso so exista a raiz no codigo
        lista->inicio=NULL;
        delete aux;
        return;
    }
    if(aux->dir != NULL){//verifica se tem elemento a direita
        funcionario *sub = substituto(aux->dir);//funcao para busca o ponteiro que sera colocado no lugar da raiz, sempre indo para a direita primeiro depois full esquerda
        if(sub->dir == NULL && sub->esq == NULL){//caso seu elemento seja uma folha
            if(sub->cpf == aux->dir->cpf){//caso o elemtento seja a ligacao do que vai remover e um filho
                if(aux->esq != NULL){
                    sub->esq=aux->esq;
                    aux->esq->info=sub;
                }
                sub->info=NULL;
                lista->inicio=sub;
                delete aux;
                return;
            }
            //caso o elemento seja da ramificação mais nao seu filho
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
        //caso aqui ele e um elemento que tem um um valor a direita, mas o valor que tem q se inserido e a esquerda.
        //ele que sera o subtituto mais tem um valor a direita que deve seliga ao anterior
        if(aux->esq != NULL){
            sub->esq=aux->esq;
            aux->esq->info=sub;
        }
        sub->dir->info=sub->info;//liga o elemento  ou a cadeia a esqeuerda do elemento anterior para pode susbtituir sem perder a ligaçao
        aux->dir->info=sub;
        sub->info=NULL;
        lista->inicio=sub;
        delete aux;
        return;
    }else{//nao tem elemento a direita, ai basta dizer para raiz ser esquerda
        aux->esq->info=NULL;
        lista->inicio=aux->esq;
        delete aux;
        return;
    }
}
//funcao de remover enorme ela, para conseguir trata de todos os casos possiveis
void remover(funcionariolista *lista){
    funcionario *aux;
    aux=lista->inicio;
    
    repetindo:
    int ajuda=0, erro;
    string palavra;
    cout<<"Insira o CPF do funcionario: ";//pede o cpf pois é a chave primaria e nao se repete so tem uma por arvore
    cin>>palavra;
    procura(aux, palavra, &ajuda);//verifica a existencia da chave
    if(ajuda==0){//caso n exista pedimos novamentes o cpf que conste no banco
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
        if(aux->cpf==palavra){//caso a remoção seja da raiz essa funcao sera chamada por se especial os casos de raiz
            removerRAIZ(&*lista, palavra);
        }else{
            removerCPF(aux, palavra);//remover qualquer elemento exeto a raiz
        }
        cout<<"Removido"<<endl;//sucesso na remoçaõ
    }
}
//salva os dados que estao na arvore
void salvando(funcionario *aux){
    if(aux==NULL){
        return;
    }
    ofstream outFile;
    outFile.open("funcionarios.txt", ios::app);//abre o arquivo e salva funcionario por funcionario
    if(!outFile){ 
        cout<<"Arquivo saida.txt nao pode ser aberto"<<endl;
        abort();
    }
    outFile<<aux->nome<<" "<<aux->cpf<<" "<<aux->endereco<<" "<<aux->cargo<<" "<<aux->telefone<<" "<<aux->data<<" "<<aux->matricula<<"\n";
    outFile.close();//fecha arquivo
    if(aux->dir!=NULL){//percore a arvore pela direita
        salvando(aux->dir);
    }
    if(aux->esq!=NULL){//percorre  arvore pela esquerda
        salvando(aux->esq);
    }
}
//carrega os dados da base de dados
void carregarDados(funcionariolista *lista){
    funcionario *novo, *raiz;
    novo = new funcionario;
    raiz=lista->inicio;
    novo->dir=NULL;
    novo->esq=NULL;

    ifstream inFile;//funcao padrao para abertura em modo leitura de um arquivo
    inFile.open("funcionarios.txt", ios::in);
    if (!inFile){ 
        cout<<"Arquivo saida.txt nao pode ser aberto"<<endl;
        abort();
    }

    while(inFile>>novo->nome>>novo->cpf>>novo->endereco>>novo->cargo>>novo->telefone>>novo->data>>novo->matricula){
        //manter e cria a arvore binaria na existencia de dados 
        if (lista->inicio == NULL){
            lista->inicio = novo;
            novo->info=NULL;
        }else{
            inserirNaArvore(raiz, novo);//insere na arvore binaria os dados
        }
        novo->dir=NULL;
        novo->esq=NULL;
        novo = new funcionario;
        raiz=lista->inicio;
    }
    inFile.close();//fecha arquivo
    limpar();
    cout<<"Dados carregados com sucesso..."<<endl;
    system("pause");
}
//verifica se deseja salva ante de fechar o programa
void salvarDados(funcionariolista *lista){
    int x;
    cout<<"Deseja salva os dados: (1.sim/2.nao) ";//caso nao queira salva as alteraçoes feira digie qualque coisa diferente de 1
    cin>>x;
    if(x!=1){
        return;
    }

    funcionario *aux;
    aux=lista->inicio;
    
    ofstream outFile;//vai apaga o arquivo e deixa-lo  vazio
    outFile.open("funcionarios.txt", ios::out);
    if(!outFile){ 
        cout<<"Arquivo saida.txt nao pode ser aberto"<<endl;
        abort();
    }
    outFile.close();

    if(aux==NULL){
        cout<<"Nenhum Dado para salva!"<<endl;//caso nao tenha dados
    }else{
        salvando(aux);//ira sala os dados pela funcao
    }
    cout<<"salvo com sucesso!"<<endl;
}