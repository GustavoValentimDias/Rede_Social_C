#ifndef PERFIL_H
#define PERFIL_H

class Mensagem;

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include "Mensagem.h"
#include "MensagemComCurtir.h"

using namespace std;

class Perfil{

public:
    Perfil(string nome);
    virtual ~Perfil();
    string getNome();
    virtual void adicionadoPor(Perfil* contato) = 0;
    virtual void envia(string texto, bool curtir);
    virtual void recebe(Mensagem* m);
    void setContatos(vector<Perfil*>* perfis);
    list<Mensagem*>* getMensagensRecebidas();
    list<Mensagem*>* getMensagensEnviadas();
    vector<Perfil*>* getContatos();
    vector<Perfil*>* verContatosAlcancaveis();

protected:
    string nome;
    vector<Perfil*>* contatos;
    list<Mensagem*>* MensagensEnviadas;
    list<Mensagem*>* MensagensRecebidas;
    bool visitado;

};

#endif // PERFIL_H
