#include "table.h"
#include <math.h>

table::~table(){
    this->clear();
}

table::table(int n){
	dim = n;
	for (int i =0;i<n;i++){
        this->myList.push_back(0.0);
	}
}

void table::display (std::ostream& str){
	for (std::list<double>::iterator it=myList.begin(); it!=myList.end();++it){
		std::cout<<*it<<"\n";
	}
}

double table::get (int indice){
	int i=0;
	double res = 0.0;
	for (std::list<double>::iterator it=myList.begin(); it!=myList.end();++it){
		res=*it;
		if (i==indice){
			break;
		}
		i++;
	}
	return res;
}


double table::minimum(){
	return get(0);
}

double table::maximum(){
	return get(dim-1);
}

void table::add(double d){
	dim++;
    this->myList.push_back(d);
}

void table::trier(){
	this->myList.sort();
}

double table::mediane(){
	if (dim%2 == 0){
		return (get(dim/2-1)+get(dim/2))/2;
	}
	else{
		return get((dim-1)/2);
	}
}

double table::moyenne(){
	double S = 0;
	for (std::list<double>::iterator it=myList.begin(); it!=myList.end();++it){
        if(*it!=0){S=S+*it;}
	}
	return S/dim;
}

double table::volatilite(){
	double m = moyenne();
	m=m*m;
	double S =0;
	for (std::list<double>::iterator it=myList.begin(); it!=myList.end();++it){
        if(*it!=0){S=S+(*it)*(*it);}
	}
	S=S/dim;
	return sqrt(S-m);
}

double table::Skewness(){
	double m = moyenne();
	double v=volatilite();
	double S = 0.0;
	for (std::list<double>::iterator it=myList.begin(); it!=myList.end();++it){
        if(*it!=0){S=S+(*it-m)*(*it-m)*(*it-m);}
	}
	return S/(dim*v*v*v);
}

double table::Kurtosis(){
	double m = moyenne();
	double v=volatilite();
	double S = 0.0;
	for (std::list<double>::iterator it=myList.begin(); it!=myList.end();++it){
        if(*it!=0){S=S+(*it-m)*(*it-m)*(*it-m)*(*it-m);}
	}
	return S/(dim*v*v*v*v);
}

void table::clear(){
	dim = 0;
	myList.clear();
}

double AC1(table t1, table t2){
	double res = 0;
	int N = std::max(t1.dim,t2.dim);
	double moyenne1 = 0;
	double moyenne2 = 0;
	int compteur = 0;
	double aux1=0;
	double aux2=0;
	int i=0;
	while (i<N){
		aux1 = t1.get(i);
		aux2= t2.get(i);
		if (aux1!=0 && aux2!=0){
			compteur++;
			moyenne1 = moyenne1 + aux1;
			moyenne2 = moyenne2 +aux2;
			i++;
		}
		else{
			i++;
			continue;
		}
	}
	moyenne1 = moyenne1/compteur;
	moyenne2 = moyenne2/compteur;
	for (int i=0; i<N; i++){
		res = res + (t1.get(i)-moyenne1)*(t2.get(i)-moyenne2);
	}
	res = res / N;
	res = res/(t1.volatilite()*t2.volatilite());
	return res;
}
