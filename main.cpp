#include <iostream>
#include "Tugabudoire.h"

int main() {
    auto t = new Tugabudoire ;

    t->actionnerPiston() ;
    t->ajouterBouton(4) ;
    std::cout << t->to_string() << std::endl ;
    std::cout << "Bouton enlevé: " << t->enleverBouton() << std::endl ;
    std::cout << t->to_string() << std::endl ;

    delete t ;
    return 0;
}
