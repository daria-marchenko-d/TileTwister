# TileTwister
## Project description
### English Version
#### 1. Project Execution Methodology

The project was developed following a structured four-stage iterative approach:

Stage 0 (Environment Setup): Configured development environment with Visual Studio Code, GCC compiler, and SDL3 library integration.

Stage 1 (Core Game Logic): Implemented the foundational 2048 mechanics in C++ using object-oriented principles. Created the game grid, movement algorithms (left, right, up, down with tile merging), random tile generation, and win/lose condition detection. Initial validation was performed through console-based testing.

Stage 2 (Graphical Implementation): Integrated SDL3 to transform the console application into a visual interface. Developed a rendering engine with window management, abstract GameObject class, and specialized Tile rendering with value-based color coding. Established keyboard input handling for directional controls.

Stage 3 (Enhanced Features): Added smooth tile movement animations and save/load functionality. Implemented special tile mechanics (blocked tiles, bonus tiles) as optional advanced features.

Stage 4 (Testing & Documentation): Conducted comprehensive integration testing to ensure system stability and absence of regression bugs. Prepared complete project documentation and GitHub repository.

####2. Technical Implementation Details

The implementation strictly followed the initial requirements:

Grid Management: 4×4 matrix with proper tile spawning (initial two tiles with values 2 or 4)

Movement Mechanics: Four-directional movement with collision detection and same-value merging

Game Flow: Automatic new tile generation after valid moves; game termination detection when grid is full with no possible merges

Visual System: SDL3-based rendering with coordinated visual representation of game state

Input Processing: Keyboard-controlled tile movement with immediate visual feedback

Extended Features: Implemented animations, persistent game state via save/load, and experimental special tile variants

####3. Architecture & Development Approach

The project employed a modular architecture separating concerns between:

Business logic (game rules, grid management)

Presentation layer (visual rendering, animations)

Input handling (user interaction translation)

Data persistence (game state saving/loading)

Development followed test-driven principles with incremental feature addition and continuous integration validation to maintain code integrity throughout the development cycle.




### French Version
#### 1. Méthodologie d'Exécution du Projet

Le projet a été développé suivant une approche itérative structurée en quatre étapes :

Étape 0 (Configuration de l'environnement) : Configuration de l'environnement de développement avec Visual Studio Code, le compilateur GCC et l'intégration de la bibliothèque SDL3.

Étape 1 (Logique de jeu principale) : Implémentation des mécaniques fondamentales du 2048 en C++ selon les principes de la programmation orientée objet. Création de la grille de jeu, des algorithmes de mouvement (gauche, droite, haut, bas avec fusion des tuiles), de la génération aléatoire de tuiles, et de la détection des conditions de victoire/défaite. Validation initiale effectuée via des tests en console.

Étape 2 (Implémentation graphique) : Intégration de SDL3 pour transformer l'application console en une interface visuelle. Développement d'un moteur de rendu avec gestion de fenêtre, classe abstraite GameObject, et rendu spécialisé des tuiles avec un codage couleur basé sur les valeurs. Mise en place de la gestion des entrées clavier pour les contrôles directionnels.

Étape 3 (Fonctionnalités avancées) : Ajout d'animations fluides des mouvements des tuiles et des fonctionnalités de sauvegarde/chargement. Implémentation des mécaniques de tuiles spéciales (tuiles bloquées, tuiles bonus) en tant que fonctionnalités avancées optionnelles.

Étape 4 (Tests et documentation) : Réalisation de tests d'intégration complets pour garantir la stabilité du système et l'absence de régressions. Préparation de la documentation complète du projet et du dépôt GitHub.

####2. Détails Techniques d'Implémentation

L'implémentation a strictement respecté les exigences initiales :

Gestion de la grille : Matrice 4×4 avec apparition appropriée des tuiles (deux tuiles initiales avec valeurs 2 ou 4)

Mécaniques de mouvement : Mouvement quadridirectionnel avec détection de collision et fusion des valeurs identiques

Déroulement du jeu : Génération automatique d'une nouvelle tuile après chaque mouvement valide ; détection de la fin de partie lorsque la grille est pleine sans fusion possible

Système visuel : Rendu basé sur SDL3 avec représentation visuelle coordonnée de l'état du jeu

Traitement des entrées : Mouvement des tuiles contrôlé par clavier avec retour visuel immédiat

Fonctionnalités étendues : Implémentation des animations, persistance de l'état du jeu via sauvegarde/chargement, et variantes expérimentales de tuiles spéciales

####3. Architecture et Approche de Développement

Le projet a employé une architecture modulaire séparant les responsabilités entre :

La logique métier (règles du jeu, gestion de la grille)

La couche de présentation (rendu visuel, animations)

La gestion des entrées (traduction des interactions utilisateur)

La persistance des données (sauvegarde/chargement de l'état du jeu)

Le développement a suivi des principes de tests pilotés avec ajout incrémental de fonctionnalités et validation d'intégration continue pour maintenir l'intégrité du code tout au long du cycle de développement.


## Files tree
TileTwister/
├── tests/
│   └── test_grid_basic.cpp
├── include/
│   ├── Constants.hpp
│   ├── Game.hpp
│   ├── GameObject.hpp
│   ├── Grid.hpp
│   ├── InputHandler.hpp
│   ├── Renderer.hpp
│   ├── Tile.hpp
│   └── Window.hpp
├── src/
│   ├── Game.cpp
│   ├── GameObject.cpp
│   ├── Grid.cpp
│   ├── InputHandler.cpp
│   ├── main.cpp
│   ├── Renderer.cpp
│   ├── Tile.cpp
│   └── Window.cpp
├── CMakeLists.txt (or Makefile)
├── README.md
└── assets/ (optional)
    ├── fonts/
    └── textures/
