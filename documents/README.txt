Le compilateur � utiliser est MSVC2013 car mingw ne peut pas permettre au programme de d�tecter le format audio du fichier qu'on passe en param�tre.

Pour utiliser la lib fftw avec MSVC2013, il faut g�n�rer les fichiers .lib � partir des fichiers .def fournit avec fftw.
Pour faire �a, il faut ouvrir un terminal et indiquer les commande (en modifiant les chemins d'acc�s si n�cessaire) :
D:\Programmes\VisualStudio2013\VC\bin\lib.exe /OUT:D:\Programmes\fftw-3.3.4\libfftw3-3.lib /def:D:\Programmes\fftw-3.3.4\libfftw3-3.def
D:\Programmes\VisualStudio2013\VC\bin\lib.exe /OUT:D:\Programmes\fftw-3.3.4\libfftw3f-3.lib /def:D:\Programmes\fftw-3.3.4\libfftw3f-3.def
D:\Programmes\VisualStudio2013\VC\bin\lib.exe /OUT:D:\Programmes\fftw-3.3.4\libfftw3l-3.lib /def:D:\Programmes\fftw-3.3.4\libfftw3l-3.def