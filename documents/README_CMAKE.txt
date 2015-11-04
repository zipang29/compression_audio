Pour que CMake fonctionne sur windows :
-Aller dans "paramètres systèmes avancés" puis dans "variables d'environnement"
-Dans les variables système, chercher la variable PATH et y ajouter le chemin vers
les compilateurs dont il y a besoin : en l'occurence, pour ce projet, on a besoin de 
mingw pour Qt ou bien MSVC2013.
Il faut donc ajouter ces adresses dans la variables path pour que CMake arrive à retrouver
les fichiers dont il a besoin :
Pour MSVC2013 par exemple : D:\Programmes\Qt\5.5\msvc2013\bin
Pour MINGW par exemple : D:\Programmes\Qt\5.5\mingw492_32\bin

CMake devrait ensuite fonctionner normalement.