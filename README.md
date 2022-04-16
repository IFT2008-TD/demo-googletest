# Exemple d'intégration de Googletest à un projet C++

## Installation et utilisation du projet

- Naviguez jusqu'au répertoire CLionProjects: ```cd ~/CLionProjects```
- Faites la commande: ```git clone https://github.com/IFT2008-Googletest_Exemple```
- Double-cliquez sur l'exécutable jetbrains-toolbox
- Choisissez CLion
- Choisissez Nouveau Projet
- Donnez au projet exactement le nom du dépôt cloné: IFT2008-Googletest_Exemple
- CLion vous avertira que ce répertoire n'est pas vide, et demandera s'il doit créer un projet 
à-partir de sources existantes.  Répondez OUI.
- Le projet est prêt à être construit et exécuté.  Pour choisir d'exécuter les tests ou le programme 
principal, choisissez dans le menu déroulant à-côté du petit marteau vert: All CTest pour les tests
et monprojet pour le programme principal.

## Structure du projet

Le projet comporte un programme principal et utilise une classe, il s'agit de la classe Tugabudoire, qui est garantie 
100% sans intérêt et complètement inutile.  Cette classe comporte quelques attributs de types divers, et des méthodes 
qui font des opérations bidons sur ces attributs.  De plus, la méthode to_string affiche certaines informations qui sont
utilisés dans les tests unitaires.

Le répertoire principal du projet comprend donc:

- main.cpp: le fichier comprenant le programme principal
- Tugabudoire.cpp: l'implantation de la classe Tugabudoire
- Tugabudoire.h: le fichier d'en-tête de la classe Tugabudoire

Le code relatif aux tests unitaires est dans le sous-répertoire /tests.  Celui-ci ne contient qu'un seul fichier source, 
soit celui des tests:

- test_tugabudoire.cpp

## Directives de compilation et intégration de Googletest

Les directives de compilation sont contenues dans les fichiers CMakelists.txt.  Il faut comprendre que l'environnement de 
programmation CLion n'est en fait qu'un éditeur.  Il ne fait aucune compilation ni édition de liens.  Pour ce faire, il 
délègue toutes ces tâches à d'autres programmes:

- Cmake: Agit comme un chef d'orcheste.  Cet utilitaire utilise les CMakelists.txt pour générer d'autres fichiers de configuration
utilisés par l'utilitaire ninja pour bâtir le ou les programmes finaux.
- Ninja: Appelle le compilateur avec ses propres fichiers de configurations, c'est lui qui demande au compilateur de compiler
tel ou tel fichier, avec telles options, et de lier le tout avec telles librairies.
- gcc: GNU C Compiler est le compilateur appelé par Ninja.
- GDB: c'est le débogueur invoqué par CLion lorsqu'on fait une séance de débogage.

Donc toutes les tâches de compilation sont contrôlées initialement par CMake et les CMakelists.txt.  Ces fichiers sont hiérarchiques:
un projet peut avoir un CMakelists.txt principal, et dans des sous-répertoires, avoir des CMakelists.txt subalternes sous 
le contrôle du premier.  C'est exactement notre cas, notre projet comporte:
- CMakelists.txt: le ficher de configuration principal du projet.
- test/Cmakelists.txt: un sous-projet qui contrôle comment seront compilés et exécutés les tests unitaires.

### CMakelists.txt principal

Ce fichier est le fichier de directives principal du projet.  Il contient les directives de compilation pour élaborer le
produit fini: le fichier exécutable du projet.
```
cmake_minimum_required(VERSION 3.14)
project(monprojet)

set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
googletest
URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(monprojet main.cpp Tugabudoire.cpp)

enable_testing()

add_subdirectory(tests)
```

La première directive qu'il contient est cmake_minimum_required et sert à indiquer quelle version de CMake peut être employée
pour construire le projet.

Ensuite la directive project(monProjet) identifie le nom du projet, et le présent fichier CMakelists.txt comme fichier
principal du projet.  

Ensuite, la variable SET_CXX_STANDARD est réglée à 11, ce qui veut dire que le standard de C++ que le compilateur va
appliquer est C++11.

Les trois directives suivantes:

- include(Fetchcontent)
- Fetchcontent_declare
- Fetchcontent_MakeAvailable

servent à inclure la libraire Googletest dans notre projet.  Le dépôt Git (identifié par le très long numéro de commit) de Googletest
sera cloné dans un sous-répertoire du projet et sera disponible à être compilé au besoin.  La libraire Googletest sera donc
intégrée à notre projet sous forme de fichiers source qui devront eux aussi être compilés.

La directive add_executable sert à identifier l'étape de compilation principale du projet: les fichiers main.cpp et Tugabudoire.cpp
seront compilés afin de produire un fichier exécutable appelé monprojet.

La directive add_testing sert à avertir CMake que des tests unitaires sont inclus dans le projet, et l'utilitaire de lecture
des tests, appelé CTest, sera activé.

Finalement la directive include_subdirectory avertit CMake de fouiller dans le sous-répertoire tests afin d'y trouver d'autres
directives.

### test/Cmakelists.txt

Ce fichier contrôle un sous-projet du projet principal qui contient les tests unitaires.

```
set(TEST_SOURCES test_tugabudoire.cpp ${PROJECT_SOURCE_DIR}/Tugabudoire.cpp ${PROJECT_SOURCE_DIR}/Tugabudoire.h)

add_executable(
       test_tugabudoire
       ${TEST_SOURCES}
)

target_include_directories(test_tugabudoire PRIVATE ${PROJECT_SOURCE_DIR} )

target_link_libraries(
       test_tugabudoire
        gtest_main
        gtest
        pthread
)

include(GoogleTest)
gtest_discover_tests(test_tugabudoire)
```
La directive set(TEST_SOURCES ...) définit une nouvelle variable, appelée TEST_SOURCES, qui contient une liste de fichiers:

- test_tugabudoire.cpp
- ${PROJECT_SOURCE_DIR}/Tugabudoire.cpp
- ${PROJECT_SOURCE_DIR}/Tugabudoire.h

Ici, la variable PROJECT_SOURCE_DIR est une variable prédéfinie de CMake qui identifie le chemin du répertoire principal du 
projet principal.  Vu qu'actuellement on est dans le sous-répertoire tests, CMake ne trouverait pas le fichier Tugabudoire.cpp
par-exemple.  On doit donc indiquer son chemin.  Cette syntaxe indique qu'il se trouve dans le répertoire principal du projet.

La directive add_executable stipule qu'on doive compiler les fichiers contenus dans la variable TEST_SOURCES afin de produire
un exécutable appelé test_tugabudoire.

La directive target_include_directories sert à retrouver les fichiers spécifiés par #include.  Voici le début de test_tugabudoire.cpp:

```
#include <gtest/gtest.h>
#include "Tugabudoire.h"
```

Le problème est que vu qu'on est dans le sous-répertoire tests, le compilateur ne trouvera pas de fichier Tugabudoire.h et 
la compilation va échouer.  Cette directive l'avertit de chercher dans le répertoire principal du projet afin d'y trouver des 
fichiers inclus.

La directive target_link_libraries s'adresse à l'éditeur de liens: elle lui donne le nom des librairies gtest et gtest_main qui
résultent de la compilation du code de Googletest.  La libraire pthread, quant à elle, est une librairie standard de Unix.

La directive include(Googletest) indique qu'il faut inclure la libraire Googletest dans la compilation des tests.

La directive gtest_discover_tests demande à CTest de reconnaître chaque test qui est demandé dans l'exécutable test_tugabudoire


