#ifndef TELAS_H
#define TELAS_H


#include <iostream>
#include <string>
#include <vector>
#include <list>

#include "Pessoa.h"
#include "Departamento.h"
#include "Mensagem.h"
#include "MensagemComCurtir.h"

using namespace std;

class Telas{
public:
    Telas();
    virtual ~Telas();
    int telaInicial();
    Pessoa* telaCadastrarPessoa();
    Departamento* telaCadastrarDepartamento(vector<Perfil*>* usuarios);
    Perfil* telaLogarUsuario(vector<Perfil*>* usuarios);
    int telaPrincipal(Perfil* usuario);
    void telaMensagensEnviadas(Perfil* usuario);
    void telaMensagensRecebidas(Perfil* usuario);
    void enviarMensagem (Perfil* usuarioLogado, bool curtidas);
    void enviarMensagem (Pessoa* usuarioLogado, Perfil* alvo);
    void telaVerContatosAlcancaveis(Perfil* usuarioLogado);
    Perfil* telaAdicionarContato(vector<Perfil*>* usuarios, Perfil* usuarioLogado);
    void telaRemoverContato(Perfil* usuarioLogado, vector<Perfil*>* contatos);
    void imprimeUsuarios(vector<Perfil*> *usuarios);

};

#endif
