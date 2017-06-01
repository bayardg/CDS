#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <QApplication>
#include <QMainWindow>
#include <QTableWidget>

#ifndef TABLEAUH
#define TABLEAUH

using namespace std;
/*! \namespace tableau
 *
 * Classe permettant la création et l'affichage des tableaux
 */
class tableau{
 public:
  tableau(int d, int TypeTab, parse &fichierParse, int argc, char **argv);
  ~tableau();
  QTableWidget *Tmain9(vector<vector<table>>& t, QMainWindow *window, vector<int>& curves, vector<int>& entities);
  QTableWidget* Tmain8(string note, table& t1, table& t2, table& t3, vector<double>& vD1, vector<double>& vD5, vector<double>& vD10, int i, QTableWidget *table);
};

#endif
