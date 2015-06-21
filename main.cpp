#include <iostream>
#include <string>
#include <cstdlib>  //Pour atoi(): convertir une chaine en int.
#include <vector>   //Pour utiliser le type vector<string>.
#include <sstream>  //Pour utiliser le type stringstream.
#include <cctype>

using namespace std;

//////////////////////////////////////////////////
//Ecrire un nombre sous une forme literale.
//version 1.0c, par Youssouf
//19 Mars 2014, nzomedia2@yahoo.fr
/////////////////////////////////////////////////
/////////// A faire:
//  Faire face au cas oU on a un caracter non digital en entree.
//
/////////////////////////////////////////////////



void afficherAide(char *nomProgramme)
{
    cout << "Ecrire un nombre sous forme literale.\nUsage:\n";
    cout << nomProgramme << " <nombre>\nExemple:\n" << nomProgramme << " 192768\n\n";
}


//Fonction pour convertir un char ou une chaine de chiffres en un nombre entier:
int to_int(const char caractere_digital)
{
    return ((int) caractere_digital) - 48;
}
int to_int(const char *nombre)
{
    return atoi(nombre);
}
int to_int(const string &nombre)
{
    return atoi(nombre.c_str());
}



int main(int argc, char *argv[])
{

    stringstream resultat;    //Contient des bouts de conversion.

    if(argc != 2)
    { cerr << "you0x\n";
        afficherAide(argv[0]);
        exit(-1);
    }
    else
    {
        long long tmp;

        if(!(stringstream(argv[1]) >> tmp))
        {
            cout << "Nombre invalide.\n";
            exit(-1);
        }
        else if(tmp < 0)
        {
            cout << "Nombre (negatif) invalide.\n";
            exit(-1);
        }
        else if(tmp == 0)
        {
            //resultat << "zero";
        }
    }
    string sortie;              //Contient le resutat retournE a la fin de la conversion.
    string nombre(argv[1]);  //le nombre a convertir

    //Tableau des nombres uniques strictement inferieurs à 20:
    char unite1[20][9] = {"", "un", "deux", "trois", "quatre", "cinq", "six", "sept", "huit", "neuf", "dix", "onze", "douze", "treise", "quatorze", "quinze", "seize", "dix-sept", "dixhuite", "dixneuf"};

    //Tableau des disaines:
    char unite2[9][20] = { "vingt", "trente", "quarante", "cinquante", "soixante", "soixante", "quatre-vingt", "quatre-vingt"};

    //Tableau des unités par pas de miliers:
    char unite3[5][9] = {"", "mille", "million", "milliard", "billiard"};      //on peut ajouter d'autres puissances.



    string str_nombre(nombre);         //Variable pour avoir nombre.size() et concatener des 0 à nombre pour le rendre divisible par 3.
    int i;                                  //Compteur.

    //On ajoute des zero en debut chaine pour pouvoir la diviser
    //en groupes de 3 caracteres grace a substr():
    while((str_nombre.size() % 3) != 0)
    {
        str_nombre = "0"+str_nombre;
    }

    int nbTercet = str_nombre.size() / 3;      //Nombre de groupe de 3 chiffres dans le nombres, on l'utilise pour le tableau des miliers.


    vector<string> tabTercet;           //Tableau des groupes de 3 chiffres.
    for(i = 0; i < nbTercet; i++)
    {
        tabTercet.push_back(str_nombre.substr(i*3, 3));
    }

    int nombre_int; //tampon temporaire pour convertir un nombre literal en chiffres.


    //Boucle principale:
    //Pour chaque groupe de 3 chiffres, on convertit le 1er element en lettres (avec le tableau unite1),
    //puis on selectionne les deux derniers pour les convertir:
    //     -si le nombre formé par les deux dernier est inferieur à 20, on prend sa conversion dans le tableau unite1.
    //     -sinon on le choisi dans unite2 (il y a deux cas speciaux où l'ecriture change: si le nombre = 9x et 7x).
    //
    //Apres avoir converti les deux derniers elements (donc le groupe de trois), on attribut une unité au groupe en miliers.

    for(i = 0; i < tabTercet.size(); i++)
    {
        if(to_int(tabTercet.at(i)) > 0)
        {
            //Le premier chiffre parmis les trois:
            nombre_int = to_int(tabTercet.at(i).at(0));

            if(nombre_int == 1)         //cas special,( ex. 100 = cent, on affiche pas "un cent").
                resultat << "cent ";
            else if(nombre_int > 1)     //On affiche ici le chiffre et l'unité cent (ex. 500 = cinq cent)
            {
                resultat << unite1[nombre_int] << " cent ";
            }


            //Les deux derniers chiffres:
            nombre_int = to_int(tabTercet.at(i).substr(1,2));

            if(nombre_int < 20)         //Si leur valeur est plus petit que 20, on le prend dans unite1.
            {
                resultat << unite1[nombre_int] << " ";
            }
            else                        //Sinon on doit le prendre dans unite2.
            {
                nombre_int = to_int(tabTercet.at(i).at(1));         //On peut afficher la premiere partie, mais la deuxieme a deux cas speciaux.
                resultat << unite2[nombre_int-2] << "";


                if(nombre_int == 7 || nombre_int == 9)            //   -si le deuxieme chiffre vaut 7 ou 9, alors on doit lire une dixaine.
                {
                    nombre_int = to_int(tabTercet.at(i).at(2)) + 10;  //on ajoute 10, pour lire les disaines dans le tableau unite2.
                }
                else
                    nombre_int = to_int(tabTercet.at(i).at(2));   //   - sinon, on affiche directement la valeur du troisieme chiffres, depuis le tableau unite1.


                //Affichage:
                if(to_int(tabTercet.at(i).at(2)) == 1)
                    resultat << "-et";          //ex: trente-et-un.
                resultat << "-" << unite1[nombre_int] << " ";
            }

            //On a terminé de convertir le groupe de trois chiffres, on lui met une unité en milliers:
                resultat << unite3[nbTercet-i-1] << " ";
        }
    }// fin boucle principale.

    //On retourne le resultat:
    sortie = resultat.str();

    //si la chaine est vide, on retourne zero:
    if(sortie.empty())
        sortie = "zero";
    cout << sortie << endl;
    return 0;
}

