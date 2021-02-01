#ifndef REDESOCIAL_H
#define REDESOCIAL_H

#include "Telas.h"

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "PersistenciaDoPerfil.h"

using namespace std;

class RedeSocial {
public:
    RedeSocial();
    ~RedeSocial();
    void coordenaInterface(); //deixar essa
    void cadastrarPessoa(); //deixar essa
    void cadastrarDepartamento(); //deixar essa
    bool logarUsuario(); //deixar essa
    void adicionarContato(); //deixar essa
    void deletarContato(); //deixar essa
    void escreveMensagem(); //deixar essa
    void curtirMensagem(); //deixar essa

private:
    vector<Perfil*>* usuarios;
    Perfil* usuarioLogado;
    Telas* interface;
    PersistenciaDoPerfil* persistencia;
};

#endif // REDESOCIAL_H
