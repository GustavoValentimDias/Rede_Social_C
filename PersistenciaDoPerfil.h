#ifndef PERSISTENCIADOPERFIL_H
#define PERSISTENCIADOPERFIL_H
#include <iostream>
#include <string>
#include <vector>
#include "Perfil.h"
#include <stdexcept>

using namespace std;

class PersistenciaDoPerfil
{
    public:
        PersistenciaDoPerfil(string arquivo);
        virtual ~PersistenciaDoPerfil();
        vector<Perfil*>* obter();
        void salvar(vector<Perfil*>* perfis);
    protected:
    private:
        string nomeDoArquivo;
};

#endif // PERSISTENCIADOPERFIL_H
