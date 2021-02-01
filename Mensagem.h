#ifndef MENSAGEM_H
#define MENSAGEM_H

class Perfil;

#include <string>
#include <iostream>

using namespace std;

class Mensagem {  //Ver o setconteudo e os construtores!!!!!!
public:
    Mensagem (string texto, Perfil *autor);
    virtual ~Mensagem();
    Perfil* getAutor();
    string getTexto();

protected:
    string texto;
    Perfil *autor;
    Mensagem *proximo; // (VER) PROVAVELMENE NAO SERA MAIS NECESSARIO!!

};

#endif // MENSAGEM_H
