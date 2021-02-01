#include "Pessoa.h"
#include <iostream>

Pessoa::Pessoa(string nome, string dataNascimento, string pais) : Perfil(nome){
    this->dataNascimento = dataNascimento;
    this->pais = pais;
}

string Pessoa::getDataNascimento (){
    return this->dataNascimento;
}

string Pessoa::getPais (){
    return this->pais;
}

void Pessoa::adiciona(Perfil* contato){
    int i, nContatos = this->contatos->size();
    for(i = 0; i < nContatos; i++){
        if(this->contatos->at(i) == contato)
           throw new logic_error("Voce ja possui este contato!");
    }
    this->contatos->push_back(contato);
    cout << '\n' << this->getNome() << " conectado a " << contato->getNome() << '\n' << endl;
}

void Pessoa::envia(string texto, Perfil* contato){
    cin.ignore(100, '\n');
    int teste = 0, nContatos;
    nContatos = this->contatos->size();
    for(int i = 0; i < nContatos; i++){
        if(this->contatos->at(i) != contato)
           teste++;
    }
    if (teste == nContatos)
        throw new logic_error("O usuario nao possui este contato!");

    cout << '\n' << "Digite a mensagem: ";
    getline(cin, texto);

    Mensagem* msg = new Mensagem(texto, this);
    contato->recebe(msg);
    this->MensagensEnviadas->push_back(msg);
    cout << "Mensagem enviada a " << contato->getNome() << endl;
}

Pessoa::~Pessoa(){
    delete MensagensEnviadas;
    delete MensagensRecebidas;
}

void Pessoa::adicionadoPor(Perfil* contato){
    string nomeContato = contato->getNome(), msg = " adicionou voce como contato." ;
    Mensagem* msgAdd = new Mensagem(nomeContato + msg, NULL);
    this->MensagensRecebidas->push_back(msgAdd);
}
