#include <iostream>
#include "RedeSocial.h" //Inclui todas as classes usadas

using namespace std;

int main (){
    RedeSocial* PoliSocial = new RedeSocial();
    PoliSocial->coordenaInterface();
    delete PoliSocial;
    return 0;
}
