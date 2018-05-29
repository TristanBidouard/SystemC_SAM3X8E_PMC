#!/bin/bash

# Ajoute
git add -A

# Commit
git commit -a -m $1
if [ $# = 1 ]
then
	# Envoi sans identifiant
	git push
else
	# Trop ou pas assez de commentaires de commentaire
	echo "Nombre de commentaires incorrect"
fi
