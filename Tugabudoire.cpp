//
// Created by etudiant on 22-04-15.
//

#include "Tugabudoire.h"
#include <sstream>

Tugabudoire::Tugabudoire(): piston(0), emeute(false), boutons({1, 2}) {

}

void Tugabudoire::ajouterBouton(int nouveauBouton) {
    boutons.insert(nouveauBouton) ;

}

int Tugabudoire::enleverBouton() {
    if (boutons.empty()) throw std::runtime_error("Le tugabudoire n'a plus de boutons!!!") ;

    auto it = boutons.begin() ;
    int retval = *it ;
    boutons.erase(it);
    return retval ;
}

void Tugabudoire::actionnerPiston() {
    piston++ ;
    if (piston % 3) emeute = true ;
}

std::string Tugabudoire::to_string() {
    std::ostringstream os ;
    os << piston << "-" << emeute << "-" << boutons.size() ;
    return os.str() ;
}
