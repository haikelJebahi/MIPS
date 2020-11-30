# Projet Architecture : MIPS
Auteur : Haikel Jebahi \
Date : 30/11/2000
## Prérequis
OS : Debian Buster 10.6 \
gcc : 8.3.0 \
cmake : 3.13.4 \
git : 2.20.1
## Quick Start
````shell script
git clone https://github.com/haikelJebahi/MIPS.git
cmake CmakeLists.txt
make
./mips Projet/test.txt
````
## Informations sur le projet
Ce projet à été réalisé dans le cadre de ma L3 à l'université de Perpignan.

Le projet comporte un fichier d'essai &#8594; [test.txt](Projet/test.txt)

Les fichiers pour tester le programme devront commencer par un "main:" et finir par un ":". A l'origine le projet devait gérer les fonctions. Il a été remanier au dernier moment.

Je me suis inspiré des exemples de [University of the PACIFIC](https://ecs-network.serv.pacific.edu/ecpe-170/tutorials/example1.asm/view).

Les éléments sont d'abord enregistré un à un dans le registre. Néanmoins, seulement "add", "addi" "sub" et "exit" fourniront un résultat.

