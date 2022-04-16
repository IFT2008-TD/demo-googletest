//
// Created by etudiant on 22-04-15.
//

#ifndef MYPROJECT_TUGABUDOIRE_H
#define MYPROJECT_TUGABUDOIRE_H

#include <set>
#include <string>


class Tugabudoire {
private:
    int piston ;
    bool emeute ;
    std::set<int> boutons ;

public:
    Tugabudoire() ;

    void ajouterBouton(int = 0) ;
    int enleverBouton() ;

    void actionnerPiston() ;

    std::string to_string() ;


};


#endif //MYPROJECT_TUGABUDOIRE_H
