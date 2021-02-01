#include "Telas.h"

Telas::Telas(){}

void Telas::imprimeUsuarios(vector<Perfil*> *usuarios){
    int i = 0, tamanho;
    tamanho = usuarios->size(); // Nao usei diretamente pois gera um warning!
    while(i < tamanho){
        cout << i+1 << ") " << usuarios->at(i)->getNome() << endl;
        i++;
    }
}

int Telas::telaInicial(){
    int comando;

    cout << "PoliSocial" << endl;
    cout << "----------" << endl;
    cout << "1) Cadastrar pessoa" << endl;
    cout << "2) Cadastrar departamento" << endl;
    cout << "3) Logar como perfil" << endl;
    cout << "0) Terminar" << '\n' << "Comando: ";

    cin >> comando;
    cout << endl;
    return comando;
}

int Telas::telaPrincipal(Perfil* usuario){
    int comando;
    Pessoa* pes;
    Departamento* dep;
    pes = dynamic_cast<Pessoa* >(usuario);
    if (pes != NULL){
        cout << "--------------------------" << endl;
        cout << "Pessoa: " << pes->getNome() << endl;
        cout << pes->getDataNascimento() << " | " << pes->getPais() << endl;
        cout << endl << "Contatos: " << endl;
        this->imprimeUsuarios(pes->getContatos());
        cout << endl;
        cout << "--------------------------" << endl;
        cout << "Escolha uma opcao:" << '\n' << endl;
        cout << "1) Ver mensagens enviadas" << endl;
        cout << "2) Ver mensagens recebidas" << endl;
        cout << "3) Escrever mensagem" << endl;
        cout << "4) Ver contatos alcancaveis" << endl;
        cout << "5) Adicionar contato" << endl;
        cout << "6) Remover contato" << endl;
        cout << "0) Voltar" << '\n' << "Comando: ";
        cin >> comando;
        while(comando > 6 && comando < 0){
            cout << "Comando invalido, digite novamente: ";
            cin >> comando;
        }
    }
    else{
        dep = dynamic_cast<Departamento *>(usuario);
        cout << "--------------------------" << endl;
        cout << "Departamento: " << dep->getNome() << endl;
        pes = dep->getResponsavel();
        cout << "Site: "<< dep->getSite() << endl;
        cout << "Responsavel: "<< pes->getNome() << endl;
        cout << endl << "Contatos: " << endl;
        this->imprimeUsuarios(dep->getContatos());
        cout << endl;
        cout << "--------------------------" << endl;
        cout << "Escolha uma opcao:" << '\n' << endl;
        cout << "1) Ver mensagens enviadas" << endl;
        cout << "2) Ver mensagens recebidas" << endl;
        cout << "3) Escrever mensagem" << endl;
        cout << "4) Ver contatos alcancaveis" << endl;
        cout << "0) Voltar" << '\n' << "Comando: ";
        cin >> comando;
        while(comando > 4 && comando < 0){
            cout << "Comando invalido, digite novamente: ";
            cin >> comando;
        }
    }
    return comando;
}

Pessoa* Telas::telaCadastrarPessoa(){
    string novoNome, novaData, novoPais;
    cin.ignore(100, '\n');

    cout << "Informe os dados da pessoa:" << '\n' << endl;

    cout << "Nome: ";
    getline(cin, novoNome);

    cout << "Data de nascimento: ";
    getline(cin, novaData);

    cout << "Pais: ";
    getline(cin, novoPais);

    Pessoa* novoUsuario = new Pessoa(novoNome, novaData, novoPais);

    cout << '\n'<< "Pessoa cadastrada com sucesso." << '\n' << endl;
    return novoUsuario;
}

Departamento* Telas::telaCadastrarDepartamento(vector<Perfil*>* usuarios){
    int i = 0, j = 0, tamanho = usuarios->size(), comando;
    string novoNome, novoSite;
    Pessoa *novoResponsavel, *teste;
    vector<Pessoa*>* possiveisResponsaveis = new vector<Pessoa*> ();
    cin.ignore(100, '\n');

    cout << "Informe os dados do departamento:" << '\n' << endl;
    cout << "Nome: ";
    getline(cin, novoNome);
    cout << "Site: ";
    getline(cin, novoSite);
    cout << "Escolha um responsavel:" << endl;

    while (j < tamanho){
        teste = dynamic_cast<Pessoa*>(usuarios->at(j));
        if (teste != NULL){
            cout << i+1 << ") " << usuarios->at(j)->getNome() << endl;
            possiveisResponsaveis->push_back(teste);
            i++;
        }
        j++;
    }

    cout << "Digite um numero ou 0 para cancelar:  ";
    cin >> comando;

    if (comando == 0){
      cout << endl;
      return NULL;
    }

    while (comando > i){
        cout << "Digite um responsavel VALIDO: ";
        cin >> comando;
    }

    novoResponsavel = possiveisResponsaveis->at(comando - 1);
    Departamento* novoDepartamento = new Departamento(novoNome, novoSite, novoResponsavel);

    cout << '\n'<< "Departamento cadastrado com sucesso." << '\n' << endl;

    return novoDepartamento;
}

Perfil* Telas::telaLogarUsuario(vector<Perfil*>* usuarios){
    int comando, tamanho = usuarios->size();

    if(usuarios->empty()){
        cout << "Nao existem usuarios cadastrados na rede!" << endl << endl;
        return NULL;
    }

    cout << "Escolha um dos perfis:" << '\n' << endl;

    this->imprimeUsuarios(usuarios);

    cout << '\n' << "Digite um numero ou 0 para voltar: ";
    cin >> comando;

    while(comando > tamanho || comando < 0){
      cout << "Comando invalido, digite novamente: ";
      cin >> comando;
    }

    if (comando == 0){
        return NULL;
        cout << endl;
    }

    return (usuarios->at(comando - 1));
}

void Telas::telaRemoverContato(Perfil *usuarioLogado, vector<Perfil*>* contatos){
    int comando, tamanho = contatos->size();
    Pessoa *teste;
    string msgAux;

    if (tamanho == 0){
        cout << "Voce nao possui contatos!" << endl;
        return;
    }

    cout << "Escolha um contato para remover" << endl;
    this->imprimeUsuarios(usuarioLogado->getContatos());
    cout << endl << "Digite um numero ou 0 para voltar: ";
    cin >> comando;

    if (comando == 0)
        return;

    while(comando > tamanho || comando < 0){
        cout << "Comando invalido, digite novamente: ";
        cin >> comando;
    }
    cout << "Contato com " << contatos->at(comando - 1)->getNome() << " removido" << endl << endl;
    teste = dynamic_cast<Pessoa*>(contatos->at(comando - 1));
    string msg = usuarioLogado->getNome();
    msg = msg + " removeu voce como contato.";
    Mensagem* msgFinal = new Mensagem(msg, NULL);
    if(teste == NULL){
        Departamento *dep = dynamic_cast<Departamento*>(contatos->at(comando - 1));
        dep->recebe(msgFinal);
    }
    else teste->recebe(msgFinal);
    contatos->erase(contatos->begin() + comando - 1);
}

void Telas::telaMensagensEnviadas(Perfil* usuario){

    int i = 1;

    cout << '\n' << "Mensagens Enviadas" << endl;
    cout << "------------------" << endl;

    list<Mensagem*>* aux = usuario->getMensagensEnviadas();
    list<Mensagem*>::iterator iter;
    MensagemComCurtir* teste; //Testa se a mensagem tem curtir ou n�o

    for(iter = aux->begin(); iter != aux->end(); iter++){
        cout << i << ") " << (*iter)->getTexto();
        teste = dynamic_cast<MensagemComCurtir *>(*iter);
        if (teste != NULL)
            cout << " (" << teste->getCurtidas() << " curtidas)";
        cout << endl;
        i++;
  }
  cout << endl;
}


void Telas::telaMensagensRecebidas(Perfil* usuario){
    int i = 1;
    cout << '\n' << "Mensagens Recebidas" << endl;
    cout << "-------------------" << endl;

    Perfil* autor;
    list<Mensagem*> *aux = usuario->getMensagensRecebidas();
    list<Mensagem*>::iterator iter;
    MensagemComCurtir *teste; //Testa se a mensagem tem curtir

    for(iter = aux->begin(); iter != aux->end(); iter++){
        cout << i << ") " << (*iter)->getTexto();
        teste = dynamic_cast<MensagemComCurtir *>(*iter);
        if (teste != NULL)
            cout << " (" << teste->getCurtidas() << " curtidas)";
        autor = (*iter)->getAutor();
        if (autor != NULL)
            cout << " - " << autor->getNome() << endl;
        cout << endl;
        i++;
    }
}

void Telas::enviarMensagem(Perfil* usuarioLogado, bool curtidas)
{
    string msg;
    cin.ignore(100, '\n');

    cout << '\n' << "Digite a mensagem: ";
    getline(cin, msg);

    usuarioLogado->envia(msg, curtidas);

    cout << '\n' << "Mensagem enviada para todos os contatos" << '\n' << endl;
}

void Telas::enviarMensagem(Pessoa* usuarioLogado, Perfil* alvo){
    string msg;
    try{
    usuarioLogado->envia(msg, alvo);
    }catch (logic_error* e){
        cout << endl << "Erro: " << e->what() << endl << endl;
        delete e;
    }
}


void Telas::telaVerContatosAlcancaveis(Perfil* usuarioLogado){
    int tamanho;
    vector <Perfil* > *contatosAlcancaveis = new vector<Perfil* > ();
    cout << "Contatos alcancaveis" << endl;
    cout << "--------------------" << endl;
    contatosAlcancaveis = usuarioLogado->verContatosAlcancaveis();
    tamanho = contatosAlcancaveis->size();
    for (int i = 0; i < tamanho ; i++)
        cout << contatosAlcancaveis->at(i)->getNome() << endl;
}

Perfil* Telas::telaAdicionarContato(vector<Perfil*>* usuarios, Perfil* usuarioLogado){
    int comando, nUsuarios = usuarios->size();
    cout << '\n' << "Adicionar contato:" << endl;
    this->imprimeUsuarios(usuarios);

    cout << "Escolha um contato para adicionar ou 0 para voltar: ";
    cin >> comando;

    if(comando == 0)
        throw 1;

    else if (comando > nUsuarios){
        cout << "Numero invalido!" << endl;
        throw 1;
    }


    if (usuarios->at(comando - 1) == usuarioLogado)
        throw new logic_error("Nao adicione voce mesmo!");

    return usuarios->at(comando - 1);
}

Telas::~Telas(){}
