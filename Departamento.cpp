#include "Departamento.h"
Departamento::Departamento(string nome, string site, Pessoa* responsavel) : Perfil(nome)
{
    this->site = site;
    this->responsavel = responsavel;
}

Departamento::Departamento(string nome, string site) : Perfil(nome){
    this->site = site;
}

string Departamento::getSite(){
    return this->site;
}

Pessoa* Departamento::getResponsavel(){
    return this->responsavel;
}

void Departamento::setResponsavel(Pessoa* responsavel){
    this->responsavel = responsavel;
}

Departamento::~Departamento()
{
    //dtor
}

void Departamento::adicionadoPor(Perfil* contato){
    this->contatos->push_back(contato);
    cout << '\n' << this->getNome() << " conectado a " << contato->getNome() << '\n' << endl;
    contato->adicionadoPor(this);
}

void Departamento::recebe(Mensagem* m){
    this->MensagensRecebidas->push_back(m);
    this->responsavel->recebe(m);
}
