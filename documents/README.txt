Le compilateur à utiliser est MSVC2013 car mingw ne peut pas permettre au programme de détecter le format audio du fichier qu'on passe en paramètre.

Pour utiliser la lib fftw avec MSVC2013, il faut générer les fichiers .lib à partir des fichiers .def fournit avec fftw.
Pour faire ça, il faut ouvrir un terminal et indiquer les commande (en modifiant les chemins d'accès si nécessaire) :
D:\Programmes\VisualStudio2013\VC\bin\lib.exe /OUT:D:\Programmes\fftw-3.3.4\libfftw3-3.lib /def:D:\Programmes\fftw-3.3.4\libfftw3-3.def
D:\Programmes\VisualStudio2013\VC\bin\lib.exe /OUT:D:\Programmes\fftw-3.3.4\libfftw3f-3.lib /def:D:\Programmes\fftw-3.3.4\libfftw3f-3.def
D:\Programmes\VisualStudio2013\VC\bin\lib.exe /OUT:D:\Programmes\fftw-3.3.4\libfftw3l-3.lib /def:D:\Programmes\fftw-3.3.4\libfftw3l-3.def