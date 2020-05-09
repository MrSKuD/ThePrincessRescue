The Princess Rescue
===================
Elaboration d’un jeu de plateforme 2D dans le cadre du cours de Programmation C++ de l’Institut Supérieur de l’Electronique et du Numérique de Rennes.

Prérequis
---------

Afin d'exécuter le programme, il est nécessaire d'avoir un compilateur C++ ainsi que la bibliothèque Qt5. Une solution est d'installer le programme Qt Creator qui possède à la fois le compilateur C++ et les bibliothèques nécessaires.
Vous pouvez le télécharger via [le lien suivant](https://www.qt.io/download). Cette solution est **TRES CONSEILLEE** car des bogues de taille de fenêtre apparaissent fréquemment en utilisant d'autres outils (Xming nottament).
Une version avec installateur pour pouvoir jouer directement est disponible [ici]() (lien non actif pour le moment).

Installation
------------
Avec Qt Creator :
*	Téléchargez tous les fichiers dans dossier nommé `QTProject`
*	Ouvrez le projet avec Qt Creator
*	Compilez le projet en mode Debug
*	Placer le fichier `timer.txt` dans le répertoire de travail `/build-QTProject-Desktop_Qt_5_14_2_MinGW_64_bit-Debug` /!\ **APRES PREMIERE COMPILATION EN MODE DEBUG** /!\
*	Jouez en lançant le projet ! 

Navigation Fichier
------------------
*	La totalité des fichiers sources sont dans le répertoire du projet
*	Tous les éléments graphiques sont placés dans le répertoire `img/`
*	Les éléments sonores sont placés dans le répertoire `sound/`
*	L’icône de l’exécutable `icone.ico` est placée avec les fichiers sources


Compatibilité
-------------

*   PC sous le système d’exploitation **Windows 10** (64 bits si utilisation du jeu via l'installateur) 
*   Ecran d'une résolution minimale **Full HD (1920x1080)**.



Jeu
---
Le jeu est composé d'un seule et unique niveau. On y incarne un chevalier dont le but est de sauver la princesse. Pour cela il doit récupérer une clé afin de la délivrer tout en évitant obstacles et ennemis. 
Jeu 1                       |                   Jeu 2     |          Jeu 3
:-------------------------:|:-------------------------:|:----------------:
![image1][1]               |  ![image1][2]             | ![image1][3]

Selon les évènements au cours de la partie, différents menus vont s'afficher.
Ecran titre                |         Menu Pause              
:-------------------------:|:-------------------------:
![image1][4]  |  ![image1][5]                           

Ecran défaite              |       Ecran victoire            
:-------------------------:|:-------------------------:
![image1][6]               |  ![image1][7]             
### Commandes

Avancer        |Reculer         | Sauter/Monter  | Pause
-------------  | -------------- | -------------- | -------
Flèche Droite  | Flèche Gauche  | Flèche du Haut | Echap


### Langage

Le jeu est en **anglais** uniquement.

### Meilleur score

Le meilleur score est stocké dans le fichier texte `timer.txt` à placer dans le répertoire de travail `/build-QTProject-Desktop_Qt_5_14_2_MinGW_64_bit-Debug` /!\ **APRES PREMIERE COMPILATION EN MODE DEBUG** /!\ .


Améliorations
-------------
### Bogues
*	Lorsque un menu est affiché (pause/défaite/victoire), l'utilsateur peut en appuyant sur les flèches directionnelles se déplacer dans la fenêtre. Le problème peut être résolu en assignant d'autres touches pour le déplacement du personnage. Chose qui ici ne me ferait pas respecter le cahier des charges.
*	L'affichage du timer dans le menu de victoire à parfois un bogue. C'est un problème aléatoire qui arrive sur certains ordinateurs alors que d'autres pas du tout. 

### Fonctionnalités
*	Permettre à l'utilisateur de choisir ses touches de jeux.
*	Permettre à l'utilisateur de choisir la résolution du jeu (nottament plein écran pour une meilleure expérience).
*	Pour la version du jeu avec installateur, le fichier de sauvegarde du meilleur score `timer.txt` peut être modifié par l'utilisateur et ce dernier peut donc tricher. Le fichier peut être masqué mais si il l'est, le jeu ne peux pas modifier son contenu. Il faudrait utiliser un autre type de fichier pour sécuriser cela. 

N’hésitez pas à me signaler tout bogue qui viendrais entraver l’expérience utilisateur. Toute aide pour perfectionner ce projet est la bienvenue ! 

Outils utilisés
---------------
*   IDE : Qt Creator 4.11.2 (Community)
*   Framework : Qt 5.14.2
*   Compilateur : MinGW 7.3.0 64-bit

Contact
-------
Mail : enzo.moulin@isen-ouest.yncrea.fr
Site web : http://www.enzomoulin.com

[1]: https://i.ibb.co/ckf1vzy/jeu1.png
[2]: https://i.ibb.co/yfc2p79/jeu2.png
[3]: https://i.ibb.co/qj3r5v8/jeu3.png
[4]: https://i.ibb.co/Dwq9fsn/accueil.png
[5]: https://i.ibb.co/7zxMzRN/pause.png
[6]: https://i.ibb.co/yh96y6n/lose.png
[7]: https://i.ibb.co/BfPGg7Q/win.png
