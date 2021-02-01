#include "MensagemComCurtir.h"

MensagemComCurtir::MensagemComCurtir(string texto, Perfil *autor) : Mensagem(texto, autor){
    this->curtidas = 0;
}

int MensagemComCurtir::getCurtidas (){
    return this->curtidas;
}

void MensagemComCurtir::setCurtidas(){
    this->curtidas++;
}

MensagemComCurtir::~MensagemComCurtir(){}
