#include "PersistenciaDoPerfil.h"
#include <fstream>
#include "Departamento.h"
#include <algorithm>

PersistenciaDoPerfil::PersistenciaDoPerfil(string arquivo)
{
    this->nomeDoArquivo = arquivo;
}

vector<Perfil*>* PersistenciaDoPerfil::obter(){
    ifstream inFile;
    vector <Perfil*>* perfis = new vector<Perfil*>();
    vector <int> *posicaoDepartamentos = new vector<int>();
    Pessoa *pes;
    Departamento *dep;
    int i = 0;
    inFile.open((this->nomeDoArquivo).c_str());
    if (inFile.fail()){
        cerr << "Arquivo nao encontrado! Deseja criar um novo ?(1-sim, 2-nao): ";
        int j = 0;
        cin >> j;
        while(j != 1 && j != 2){
            cout << "Opcao invalida, tente denovo. (1-sim, 2-nao): ";
            cin >> j;
        }
        if(j == 2) return NULL;
        else return perfis;

    }
    else{
        string nome, data, dado;
        int teste1 = 0, teste2 = 0;
        while (inFile){
            getline(inFile, dado);
            while (dado != "#"){
                if (dado == "P"){
                    getline(inFile, nome);
                    getline(inFile, data);
                    getline(inFile, dado);
                    pes = new Pessoa(nome, data, dado);
                    perfis->push_back(pes);
                }
                else if (dado == "D"){
                    getline(inFile, nome);
                    getline(inFile, dado);
                    dep = new Departamento(nome, dado);
                    perfis->push_back(dep);
                    posicaoDepartamentos->push_back(i);
                }
                else{
                    throw new runtime_error("Arquivo com formato invalido!");
                }
                getline(inFile, dado);
                i++;
            }
            int nContatos, contato, responsavel;
            vector<Perfil*> *aux = new vector<Perfil*>();
            while (teste1 < i && inFile){
                inFile >> nContatos;
                while (teste2 < nContatos && inFile){
                    inFile >> contato;
                    aux->push_back(perfis->at(contato - 1));
                    teste2++;
                }
                perfis->at(teste1)->setContatos(aux);
                teste2 = 0;
                if(find(posicaoDepartamentos->begin(), posicaoDepartamentos->end(), teste1) != posicaoDepartamentos->end()){
                    inFile >> responsavel;
                    dep = dynamic_cast <Departamento* >(perfis->at(teste1));
                    pes = dynamic_cast <Pessoa* >(perfis->at(responsavel - 1));
                    dep->setResponsavel(pes);
                }
                if(inFile){
                    perfis->at(teste1)->setContatos(aux);
                    aux = new vector<Perfil*>();
                    teste1++;
                }
            }
        }
        inFile.close();
        return perfis;
    }
}

void PersistenciaDoPerfil::salvar(vector<Perfil*>* perfis){
    ofstream onFile;
    vector <Perfil*> *nAmigos;
    Departamento *dep;
    Pessoa *pes;
    int nUsuarios = perfis->size(), nContatos, i, j, k;
    onFile.open((this->nomeDoArquivo).c_str());
    if (onFile.fail())
        cerr << "Arquivo nao encontrado!!" << endl;
    else{
        for (i = 0; i < nUsuarios; i++){
            pes = dynamic_cast<Pessoa*>(perfis->at(i));
            if (pes !=  NULL){
                onFile << "P" << '\n';
                onFile << pes->getNome() << '\n';
                onFile << pes->getDataNascimento() << '\n';
                onFile << pes->getPais() << '\n';
            }
            else{
                dep = dynamic_cast<Departamento*>(perfis->at(i));
                onFile << "D" << '\n';
                onFile << dep->getNome() << '\n';
                onFile << dep->getSite() << '\n';
            }
        }
        if (nUsuarios != 0)
            onFile << "#" << '\n';
        for (i = 0; i < nUsuarios; i++){
            pes = dynamic_cast<Pessoa*>(perfis->at(i));
            if (pes !=  NULL){
                nContatos = pes->getContatos()->size();
                nAmigos = pes->getContatos();
                onFile << nContatos;
                if (nContatos != 0)
                    onFile << " ";
                for (j = 0; j < nContatos; j++){
                    k = 0;
                    while (nAmigos->at(j) != perfis->at(k))
                        k++;
                    onFile << k + 1;
                    if (j != nContatos - 1)
                        onFile << " ";
                }
            }
            else{
                dep = dynamic_cast<Departamento*>(perfis->at(i));
                nContatos = dep->getContatos()->size();
                nAmigos = dep->getContatos();
                pes = dep->getResponsavel();
                onFile << nContatos << " ";
                for (j = 0; j < nContatos; j++){
                    k = 0;
                    while (nAmigos->at(j) != perfis->at(k))
                        k++;
                    onFile << k + 1 << " ";
                }
                k = 0;
                while (pes != perfis->at(k))
                    k++;
                onFile << k + 1;
            }
            if (i != nUsuarios - 1)
                onFile << '\n';
        }
        onFile.close();
    }
}

PersistenciaDoPerfil::~PersistenciaDoPerfil()
{
    //dtor
}
