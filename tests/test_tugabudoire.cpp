#include <gtest/gtest.h>
#include "Tugabudoire.h"

TEST(Tugabudoire_test, constructor_noexcept) {
    EXPECT_NO_THROW(Tugabudoire t) ;
}

class TugabudoireTest : public ::testing::Test {
protected:
    Tugabudoire tug_1 ;
    Tugabudoire tug_2 ;
    Tugabudoire tug_3 ;


    void SetUp() override {
        tug_2.enleverBouton() ;
        tug_2.enleverBouton() ;

        tug_3.ajouterBouton(12) ;
    }
};

TEST_F(TugabudoireTest, constructeur_affecte_bonnes_valeurs) {
    Tugabudoire tug ;
    EXPECT_EQ("0-0-2", tug.to_string()) ;
}

TEST_F(TugabudoireTest, enlever_bouton_vide_exception) {
    EXPECT_ANY_THROW(tug_2.enleverBouton()) ;
}

TEST_F(TugabudoireTest, ajouter_bouton_nombre_boutons_mis_a_jour) {
    EXPECT_EQ("0-0-3", tug_3.to_string()) ;
}


