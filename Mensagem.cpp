#include "Mensagem.h"

Mensagem::Mensagem (string texto, Perfil *autor){
    this->proximo = NULL;
    this->texto = texto;
    this->autor = autor;
}

string Mensagem::getTexto(){
    return this->texto;
}

Perfil* Mensagem::getAutor(){
    return this->autor;
}

Mensagem::~Mensagem(){}
