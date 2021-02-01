#ifndef MENSAGEMCOMCURTIR_H
#define MENSAGEMCOMCURTIR_H

#include "Mensagem.h"
#include <iostream>

using namespace std;

class MensagemComCurtir : public Mensagem
{
    public:
        MensagemComCurtir(string texto, Perfil *autor);
        virtual ~MensagemComCurtir();
        int getCurtidas ();
        void setCurtidas ();

    private:
        int curtidas;
};

#endif // MENSAGEMCOMCURTIR_H
