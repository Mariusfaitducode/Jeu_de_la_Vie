# Jeu de la Vie

J'ai découvert le <a href="https://fr.wikipedia.org/wiki/Jeu_de_la_vie">Jeu de la Vie</a> grâce à la vidéo de <a href="https://youtu.be/S-W0NX97DB0" target="_blank">Science Etonnante</a> sur le sujet.

Le Jeu de la vie est un « jeu à zéro joueur », il ne nécessite aucune intervention du joueur lors de son déroulement.
Il s'agit d'un <strong>automate cellulaire</strong>, un modèle où chaque état conduit mécaniquement à l'état suivant à partir de règles préétablies.

Les règles sont les suivantes :
<br>
Une cellule morte (blanche) possédant exactement trois cellules voisines vivantes devient vivante (elle naît).
<br>
Une cellule vivante (noir) possédant deux ou trois cellules voisines vivantes le reste, sinon elle meurt.

Chaque cellule possède 8 cellules voisine qui sont ses cellules adjacentes.

Ce qui m'a donné envie de coder ce jeu est le fait que les règles sont simples mais peuvent amené à des résultats très imprévisibles. 

Le challenge de ce projet était de modéliser ces règles en C et d'afficher le résultat avec SDL2.
L'utilisateur à la possibilité de cliquer les cases pour les rendre morte ou vivante ainsi que de simuler les étapes suivante en appuyant sur espace.

