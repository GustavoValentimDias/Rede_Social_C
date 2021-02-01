#ifndef DEPARTAMENTO_H
#define DEPARTAMENTO_H

#include "Pessoa.h"
#include <iostream>

using namespace std;

class Departamento : public Perfil
{
public:
    Departamento(string nome, string site, Pessoa* responsavel);
    Departamento(string nome, string site);
    virtual ~Departamento();
    string getSite();
    Pessoa* getResponsavel();
    virtual void recebe(Mensagem* m);
    virtual void adicionadoPor(Perfil* contato);
    void setResponsavel(Pessoa* responsavel);

private:
    string site;
    Pessoa* responsavel;
};

#endif // DEPARTAMENTO_H
