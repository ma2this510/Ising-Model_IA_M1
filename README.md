# Projet de IA : le Modèle D'ising
Sorbonne Université - Master 1 : Physique Fondamentale et Application - Intelligence Artificielle
**Auteurs** : G. Carvalho - A. Cremel-Schlemer - M. Panet

### Explication des fichiers
- `./Rapport/` : Dossier contenant le rapport du projet
- `./data/` : Dossier contenant les données fournis
- `./mydata/` : Dossier contenant les données générés par nos programmes
- `./gen_new_method/` : Dossier contenant les codes et données liés à l'autoencoder et Adversary Neural Network
- `./simulation/` : Dossier contenant les codes et données liés à la simulation de l'Ising
- `Ising_total.ipynb` : Notebook contenant tout les codes en liens avec le Rapport
- `Ising_total_update_Anatole.ipynb` : Notebook contenant tout les codes en liens avec le Rapport (Anatole)
- `Ising_CNN.ipynb` : Notebook contenant le code des modéles sur les états individuels des spins (Partie 3.2)
- `Ising_projet.ipynb` : Notebook contenant le code des modéles sur la moyenne des états des spins (Partie 3.1)
- `main_compare.ipynb` : Notebook comparant nos jeux de données avec ceux fournis
- `main_img.ipynb` : Notebook générant l'image de l'état des spins en fct de la température (Outdated)
- `data_anatole.ipynb` : Notebook verifiant le premier jeu de données généré par Anatole
- `ising_github.py` : Script générant des données en fct de la température accéléré avec *numba* (Inspiration d'un github : **Trouver le lien**)
- `ising_base.ipynb` : Notebook générant des données avec méthode d'Ising (Anatole)
- `ising_accelerated.ipynb` : Notebook générant des données avec méthode d'Ising accéléré (Anatole)
- `Ising_1-2_figure.ipynb` : Notebook générant les graphiques de la partie 1.2
- `ising2D.py` : Script générant des données avec méthode d'Ising (cf. [f-legrand](https://www.f-legrand.fr/scidoc/docmml/sciphys/physistat/ising2d/ising2d.html) )
- `main.cpp` : Script générant des données avec méthode d'Ising avec C++
- `ising.cpp` : Fonction générant des données utilisant la méthode de Métropolis en C++ (lié à `main.cpp`)
- `ising.h` : Header de `ising.cpp`
- `test_mag.py` : Script testant la magnétisation des données générés par `main.cpp`
- `test_moment.py` : Script testant le moment des données générés par `main.cpp`
- `Violin_plot.py` : Script générant les graphiques de la partie 3.2 