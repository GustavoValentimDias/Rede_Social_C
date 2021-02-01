#include "RedeSocial.h"

RedeSocial::RedeSocial(){
    this->usuarios =  new vector<Perfil*> ();
}

//Funcoes usadas na tela 1

void RedeSocial::cadastrarPessoa(){
    this->usuarios->push_back(this->interface->telaCadastrarPessoa());
}

void RedeSocial::cadastrarDepartamento(){
    if(!this->usuarios->empty())
        this->usuarios->push_back(this->interface->telaCadastrarDepartamento(this->usuarios));
    else
        cout << "Nao existem possiveis responsaveis cadastrados na rede!" << endl << endl;
}

bool RedeSocial::logarUsuario(){
    Perfil *login = this->interface->telaLogarUsuario(this->usuarios);
    if(login == NULL)
        return false;
    this->usuarioLogado = login;
    return true;
}

//Funcoes usadas na tela 2

void RedeSocial::adicionarContato(){
    Perfil *auxiliar;
    Departamento *testeDepartamento;
    Pessoa *pes, *testePessoa;
    try{
        auxiliar = this->interface->telaAdicionarContato(this->usuarios, this->usuarioLogado);
        pes = dynamic_cast<Pessoa* >(usuarioLogado);

        if (pes != NULL){
            if (auxiliar != this->usuarioLogado){
                pes->adiciona(auxiliar);
                testeDepartamento = dynamic_cast<Departamento* >(auxiliar);
                if (testeDepartamento != NULL)
                    testeDepartamento->adicionadoPor(pes);
                else{
                    testePessoa = dynamic_cast<Pessoa* >(auxiliar);
                    testePessoa->adicionadoPor(pes);
                }
            }
            else cout << endl;
        }
    }catch (logic_error* e){
        cout << endl << "Erro: " << e->what() << endl << endl;
        delete e;
    }
    catch (int){
        cout << endl;
    }
}

void RedeSocial::escreveMensagem(){
    bool curtidas = false;
    int resposta = 0;
    Pessoa* teste = dynamic_cast<Pessoa* >(usuarioLogado);

    if (teste != NULL){
        cout << "A mensagem eh privada (0 - nao, 1 - sim): ";
        cin >> resposta;
        cout << endl;
    }

    if (resposta == 0){
        cout << "A mensagem pode ser curtida? (0 - nao, 1 - sim): ";
        cin >> resposta;
        if (resposta == 1)
            curtidas = true;
        this->interface->enviarMensagem(this->usuarioLogado, curtidas);
    }
    else{
        cout << "Escolha o destino:" << endl;
        this->interface->imprimeUsuarios(this->usuarios);
        cout << "Digite um numero ou 0 para cancelar: ";
        cin >> resposta;
        if (resposta != 0)
            this->interface->enviarMensagem(teste, this->usuarios->at(resposta - 1));
    }
}

void RedeSocial::curtirMensagem(){
    int i, curtir, tamanho;
    list<Mensagem* > *aux = this->usuarioLogado->getMensagensRecebidas();
    list<Mensagem* >:: iterator iter1, iter2;
    MensagemComCurtir* teste;

    cout << '\n' << "Digite o numero da mensagem para curtir ou 0 para voltar: ";
    cin >> curtir;

    tamanho = aux->size();
    if (curtir > tamanho){
            cout << "Numero invalido!" << endl;
            return;
        }

    else if(curtir == 0){
        return;
    }

    else{
        iter1 = aux->begin();
        for (i = 1; i != curtir; i++){
            iter1++;
        }
        teste = dynamic_cast<MensagemComCurtir* >(*iter1);
        if (teste != NULL){
            teste->setCurtidas();
        }
        else{
            cout << "A mensagem nao pode ser curtida!" << endl << endl;
            return;
        }
        cout << "Mensagem curtida" << '\n' << endl;
    }
}

void RedeSocial::coordenaInterface(){
    int tela = 1, comando;
    bool teste;
    string arquivo;

    cout << "Informe o nome do arquivo: ";
    cin >> arquivo;
    this->persistencia = new PersistenciaDoPerfil(arquivo);
    try{
        this->usuarios = this->persistencia->obter();
    }catch (runtime_error* r){
            cout << "Erro: " << r->what() << endl << endl;
            usuarios = NULL;
            delete r;
    }
    while(usuarios == NULL){
        cout << "Informe o nome de um arquivo valido: ";
        cin >> arquivo;
        this->persistencia = new PersistenciaDoPerfil(arquivo);
        try{
            this->usuarios = this->persistencia->obter();
            }catch (runtime_error* r){
                cout << "Erro: " << r->what() << endl << endl;
                delete r;
            }
    }

    int tamanho = this->usuarios->size();
    if (tamanho != 0)
        cout << "Perfis carregados" << endl << endl;
    while (tela != 0){
        if(tela == 1){
            comando = this->interface->telaInicial();
            switch(comando){
                case 0: tela = 0;
                        this->persistencia->salvar(this->usuarios);
                        cout << "Perfis salvos";
                        break;
                case 1: this->cadastrarPessoa();
                        break;
                case 2: this->cadastrarDepartamento();
                        break;
                case 3:
                        teste = this->logarUsuario();
                        if (teste == true)
                            tela = 2;
                        break;
            }
        }
        else{
            comando = this->interface->telaPrincipal(this->usuarioLogado);
            switch(comando){
                case 0: tela = 1;
                        cout << endl;
                        break;
                case 1: this->interface->telaMensagensEnviadas(this->usuarioLogado);
                        break;
                case 2: this->interface->telaMensagensRecebidas(this->usuarioLogado);
                        this->curtirMensagem();
                        break;
                case 3: this->escreveMensagem();
                        break;
                case 4: this->interface->telaVerContatosAlcancaveis(this->usuarioLogado);
                        break;
                case 5: this->adicionarContato();
                        break;
                case 6: interface->telaRemoverContato(this->usuarioLogado, this->usuarioLogado->getContatos());
                        break;
            }
        }
    }
}

RedeSocial::~RedeSocial(){
    int tamanho;
    tamanho = this->usuarios->size();
    for (int i = 0; i < tamanho; i++)  //PROVAVELMENTE NAO PRECISA MAIS!!!!
        delete usuarios->at(i);
}
