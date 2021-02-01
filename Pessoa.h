#ifndef PESSOA_H
#define PESSOA_H

#include <string>
#include <iostream>
#include <stdexcept>
#include "Perfil.h"

using namespace std;

class Pessoa : public Perfil {
public:
    Pessoa(string nome, string dataNascimento, string pais);
    virtual ~Pessoa();

    string getDataNascimento ();
    string getPais ();
    void envia(string texto, Perfil* contato);
    void adiciona(Perfil* contato);
    virtual void adicionadoPor(Perfil* contato);

private:
    string dataNascimento;
    string pais;
};

#endif // PESSOA_H
