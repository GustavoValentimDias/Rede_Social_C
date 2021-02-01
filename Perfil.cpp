#include "Perfil.h"

Perfil::Perfil(string nome){
    this->contatos = new vector<Perfil*> ();
    this->MensagensEnviadas = new list<Mensagem*> ();
    this->MensagensRecebidas = new list<Mensagem*> ();
    this->nome = nome;
    this->visitado = false;
}

string Perfil::getNome(){
    return this->nome;
}

vector<Perfil*>* Perfil::getContatos(){
    return this->contatos;
}

list<Mensagem*>* Perfil::getMensagensRecebidas(){
    return this->MensagensRecebidas;
}

list<Mensagem*>* Perfil::getMensagensEnviadas(){
    return this->MensagensEnviadas;
}

void Perfil::setContatos(vector<Perfil* >* perfis){
    this->contatos = perfis;
}

void Perfil::recebe(Mensagem* m){
    this->MensagensRecebidas->push_back(m);
}

void Perfil::envia(string texto, bool curtir){
    Mensagem* msg;
    int nContatos = this->contatos->size();
    if (curtir == true)
        msg = new MensagemComCurtir(texto, this);
    else
        msg = new Mensagem(texto, this);

    for (int i = 0; i < nContatos; i++)
        this->contatos->at(i)->recebe(msg);

    this->MensagensEnviadas->push_back(msg);
}

vector<Perfil*>* Perfil::verContatosAlcancaveis(){ //BFS
    vector<Perfil*>* usuariosAlcancaveis = new vector<Perfil*> ();
    int i, j, nContatos = this->contatos->size();
    this->visitado = true;

    for(i = 0; i < nContatos; i++){
      usuariosAlcancaveis->push_back(this->contatos->at(i));
      this->contatos->at(i)->visitado = true;
    }

    usuariosAlcancaveis->push_back(NULL);

    i = 0;
    while(usuariosAlcancaveis->at(i) != NULL){
      nContatos = usuariosAlcancaveis->at(i)->contatos->size();
      for(j = 0; j < nContatos; j++){
          if(usuariosAlcancaveis->at(i)->contatos->empty() != true && usuariosAlcancaveis->at(i)->contatos->at(j)->visitado == false){
            usuariosAlcancaveis->pop_back();
            usuariosAlcancaveis->push_back(usuariosAlcancaveis->at(i)->contatos->at(j));
            usuariosAlcancaveis->push_back(NULL);
            usuariosAlcancaveis->at(i)->contatos->at(j)->visitado = true;
        }
      }
      i++;
    }
    usuariosAlcancaveis->pop_back();

    this->visitado = false;
    nContatos = usuariosAlcancaveis->size();
    for (i = 0; i < nContatos; i++)
        usuariosAlcancaveis->at(i)->visitado = false;
    return usuariosAlcancaveis;
}

Perfil::~Perfil(){}
