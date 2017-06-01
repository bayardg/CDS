#ifndef TABLEH
#define TABLEH

#include <list>
#include<iostream>

using namespace std;
/*! \namespace table
 *
 * Classe permettant d'effectuer les calculs nécessaires aux tableaux
 */
class table{
	private:
	public:
		std::list<double> myList;
        int dim;
		table(int n);
        ~table();
		void display (std::ostream& str);
        double moyenne();
        double mediane();
        double minimum();
        double maximum();
        double volatilite();
        double Skewness() ;
        double Kurtosis() ;
        void add(double d);
        void trier();
        void clear();
        double get(int indice);

};

double AC1(table t1, table t2);

#endif

