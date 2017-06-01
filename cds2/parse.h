#ifndef PARSEH
#define PARSEH
/*!
 * \file parse.h
 * \brief Fichier contenant la classe parse
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>


using namespace std;
/*! \namespace parse
 *
 * Classe parse permettant de parser le fichier de format csv
 */
class parse{
 private:
  unordered_map <int, vector<vector<string>>> map; /*!< objet unordered_map dont les clés sont les notes financières*/
  unordered_map <string, vector<vector<string>>> mapPays; /*!< objet unordered_map dont les clés sont les pays*/
  int choix;              /*!< le choix de notation*/
 public:
  /*!
   *  \brief Constructeur
   *
   *  parse le fichier entrée en paramètre en tenant compte de la notaton choisie.
   *
   *  \param d : la  notation choisie
   *  \param myFile: le fichier à parser
   */
  parse(int d, string myFile);
  /*!
   *  \brief Destructeur
   *
   *  Destructeur de la classe parse
   */
  ~parse();
  /*!
   *  \brief Constructeur
   *
   *  Constructeur par défaut
   *
   */
  parse();
  /*!
   *  \brief Constructeur
   *
   *  Constructeur par recopie
   *
   *  \param &p : objet parse
   */
  parse(const parse &p);
  /*!
   *  \brief Opérateur d'affectation
   *
   *  Opérateur d'affectation
   *
   *  \param &V: un objet parse
   *  \return un objet resultant de l'affectation
   */
  parse & operator=(const parse &V);
  /*!
   *  \brief Moyenne des notes des agences financières
   *
   *  Méthode prenant en paramètre un vecteur de string correpondant à une ligne du fichier csv et renvoyant la moyenne des notes des agences financières.
   *
   *  \param v : un vecteur de string
   *  \return la moyenne des notes des agences financières
   */
  int moyenne(vector<string> v);
  /*!
   *  \brief entier correspondant à la note financière
   *
   *  Méthode renvoyant l'etier correspondant à la note financière selon le choix de la notation.
   *
   *  \param d : Le choix de la notation
   *  \param str: la note financière
   *  \return l'entier correspondant à la note financière.
   */
  int nbr_Corr(int d, string str);
  /*!
   *  \brief Accesseur sur map
   *
   *  Méthode renvoyant map.
   *  \return map.
   */
  unordered_map <int, vector<vector<string>>> getMap(){return map;}
  /*!
   *  \brief Accesseur sur mapPays
   *
   *  Méthode renvoyant mapPays.
   *  \return mapPays.
   */
  unordered_map <string, vector<vector<string>>> getMapPays(){return mapPays;}
  /*!
   *  \brief la note financière correspondant à l'entier
   *
   *  Méthode renvoyant la note financière correspondant à l'entier pris en paramètre selon le choix de la notation.
   *
   *  \param d : Le choix de la notation
   *  \param nbr: l'entier
   *  \return la note financière correspondant à l'entier.
   */
  string nbrConv(int d, int nbr);
  /*!
   *  \brief Convertit la date en un nombre
   *
   *  Méthode convertissant la date en un nombre tel que les jours ont un poids de 1, les mois un poids de 100 et les années un poids de 10000.
   *
   *  \param str : un objet string contenant la date de la forme dd-mm.-yy
   *  \return un entier correspondant à la date.
   */
  static double dateConv(string str);
  /*!
   *  \brief Retourne un vecteur de vecteurs contenant les données du pays
   *
   *  Méthode Retourne un vecteur de vecteurs contenant les triples (CDS à la date t, t, CDS à la date t-1) pour les maturités 1an, 5 ans et 10 an.
   *
   *  \param d : le choix de notation prix
   *  \param strNote : la note financière
   *  \param strCountry : le pays choisi
   *  \return un vecteur de vecteurs contenant les données du pays.
   */
  vector<vector<vector<string> > > getDataCountry(int d, string strNote, string strCountry); //c pour le nom du pays, d pour le numero de l'agence financière et str pour la note des agences financières
};

#endif
