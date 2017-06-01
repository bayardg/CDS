#include "parse.h"
#include "table.h"
#include "tableau.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <unordered_map>
#include<vector>
#include <math.h>
#include <algorithm>
#include <QApplication>
#include <QMainWindow>
#include <QTableWidget>

tableau::~tableau(){
}

tableau::tableau(int d, int TypeTab, parse& fichierParse, int argc, char **argv){

    //std::string script;
    vector<int> curves(17);
    vector<int> entities(17);
        vector<std::string> g(17);
    for(int i=0; i<17;i++){
        curves.at(i)=0;
        entities.at(i)=0;
        g.at(i)="";
    }


    table t1(0);
    table t2(0);
    table t3(0);
    table t4(0);
    table t5(0);
    table t6(0);
    table t7(0);
    table t8(0);
    table t9(0);
    int i =0;
    vector<vector<table>> t(17);

    for (int i = 0; i< 17; i++){
        t[i].resize(3, 0);
    }
    double m = 0;
    double compteur = 0;
    //
    ofstream myfile;
    ofstream myfile9;
    QApplication app(argc, argv);

    QMainWindow *window = new QMainWindow();
    QTableWidget* tab = new QTableWidget();

        if ( TypeTab == 8 ) {
            myfile.open("table8.csv");
            window->setWindowTitle(QString::fromUtf8("Tableau 8"));
            window->resize(400, 250);
        }
        if ( TypeTab == 9 ) {	myfile9.open("table9.csv");}

    for (auto& x: fichierParse.getMap())
    {
            std::string v;
        vector<double> vD1;
        vector<double> vD5;
        vector<double> vD10;
        for (auto& y : x.second){
            if (atof(y.at(3).substr(1,y.at(3).size()-2).c_str())!=0){

                m = m+atof(y.at(3).substr(1,y.at(3).size()-2).c_str());

                compteur++;

            }
            if (atof(y.at(4).substr(1,y.at(4).size()-2).c_str())!=0){
                m = m+atof(y.at(4).substr(1,y.at(4).size()-2).c_str());

                compteur++;

            }
            if (atof(y.at(5).substr(1,y.at(5).size()-2).c_str())!=0){

                m = m+atof(y.at(5).substr(1,y.at(5).size()-2).c_str());

                compteur++;

            }
            m=m/compteur;

            m = floor(m/100);
          if(atof(y.at(3).substr(1,y.at(3).size()-2).c_str())!=0){
            t1.add(atof(y.at(3).substr(1,y.at(3).size()-2).c_str()));
          } if(atof(y.at(4).substr(1,y.at(4).size()-2).c_str())!=0){
            t2.add(atof(y.at(4).substr(1,y.at(4).size()-2).c_str()));
          } if(atof(y.at(5).substr(1,y.at(5).size()-2).c_str())!=0){
            t3.add(atof(y.at(5).substr(1,y.at(5).size()-2).c_str()));}
            if (m>=16){
                if(atof(y.at(3).substr(1,y.at(3).size()-2).c_str()) !=0)
                    {t[16][0].add(atof(y.at(3).substr(1,y.at(3).size()-2).c_str()));}

                if(atof(y.at(4).substr(1,y.at(4).size()-2).c_str())!=0)
                {t[16][1].add(atof(y.at(4).substr(1,y.at(4).size()-2).c_str()));}

                if(atof(y.at(5).substr(1,y.at(5).size()-2).c_str()))
                {t[16][2].add(atof(y.at(5).substr(1,y.at(5).size()-2).c_str()));}

                curves.at(16)+=1;
                if(std::strstr(g.at(16).c_str(), y.at(2).c_str()) != NULL) {}
                else{ g.at(16) +=y.at(2)+'.'; entities.at(16)+=1;}

                //
            }
            else{

                if(atof(y.at(3).substr(1,y.at(3).size()-2).c_str())!=0)
                {t[m][0].add(atof(y.at(3).substr(1,y.at(3).size()-2).c_str()));}

                if(atof(y.at(4).substr(1,y.at(4).size()-2).c_str())!=0)
                {t[m][1].add(atof(y.at(4).substr(1,y.at(4).size()-2).c_str()));}

                if(atof(y.at(5).substr(1,y.at(5).size()-2).c_str())!=0)
                {t[m][2].add(atof(y.at(5).substr(1,y.at(5).size()-2).c_str()));}

                curves.at(m)+=1;
                if(std::strstr(g.at(m).c_str(), y.at(2).c_str()) != NULL) {}
                else{ g.at(m) +=y.at(2)+'.';entities.at(m)+=1;}

            }
            m = 0;
            compteur = 0;

            if ( myfile.is_open() ) {
          if(std::strstr(v.c_str(), y.at(2).c_str()) != NULL) {}
            else{
            vector<vector<vector<std::string>>> vec = fichierParse.getDataCountry(d,'.'+fichierParse.nbrConv(d,x.first),y.at(2).c_str());
            v+=y.at(2)+'.';
            for (auto& h : vec.at(0)){
            if(atof(h.at(0).c_str())!=0){t4.add(atof(h.at(0).c_str()));}
            if(atof(h.at(2).c_str())!=0){t5.add(atof(h.at(2).c_str()));}
            }
            for (auto& h : vec.at(1)){
            if(atof(h.at(0).c_str())!=0){t6.add(atof(h.at(0).c_str()));}
            if(atof(h.at(2).c_str())!=0){t7.add(atof(h.at(2).c_str()));}
            }
            for (auto& h : vec.at(2)){
            if(atof(h.at(0).c_str())!=0){t8.add(atof(h.at(0).c_str()));}
            if(atof(h.at(2).c_str())!=0){t9.add(atof(h.at(2).c_str()));}
            }
            double e1 = AC1(t4,t5);
            if(isnormal(e1)){vD1.push_back(e1);}
            double e5 = AC1(t6,t7);
            if(isnormal(e5)){vD5.push_back(e5);}
            double e10 = AC1(t8,t9);
            if(isnormal(e10)){vD10.push_back(e10);}
            t4.clear();
            t5.clear();
            t6.clear();
            t7.clear();
            t8.clear();
            t9.clear();

            }}
        }

            if ( myfile.is_open() ) {

                t1.trier();
                t2.trier();
                t3.trier();
        myfile<<fichierParse.nbrConv(2,x.first)<<','<<5<<','<<1<<','<<10<<std::endl;

        myfile<<"Mean"<<','<<t1.moyenne()<<','<<t2.moyenne()<<','<<t3.moyenne()<<std::endl;
        myfile<<"Median"<<','<<t1.mediane()<<','<<t2.mediane()<<','<<t3.mediane()<<std::endl;
        myfile<<"Minimum"<<','<<t1.minimum()<<','<<t2.minimum()<<','<<t3.minimum()<<std::endl;
        myfile<<"Maximum"<<','<<t1.maximum()<<','<<t2.maximum()<<','<<t3.maximum()<<std::endl;
        myfile<<"Volatility"<<','<<t1.volatilite()<<','<<t2.volatilite()<<','<<t3.volatilite()<<std::endl;
        myfile<<"Skewness"<<','<<t1.Skewness()<<','<<t2.Skewness()<<','<<t3.Skewness()<<std::endl;
        myfile<<"Kurtosis"<<','<<t1.Kurtosis()<<','<<t2.Kurtosis()<<','<<t3.Kurtosis()<<std::endl;
        myfile<<"AC1"<<','<<(double) std::accumulate(vD1.begin(),vD1.end(),0.0)/vD1.size()<<','<<(double) std::accumulate(vD5.begin(),vD5.end(),0.0)/vD5.size()<<','<<(double) std::accumulate(vD10.begin(),vD10.end(),0.0)/vD10.size()<<std::endl;



        tab = Tmain8(fichierParse.nbrConv(2,x.first), t1, t2, t3, vD1, vD5, vD10,i,tab);

        i++;

            }
        t1.clear();
        t2.clear();
        t3.clear();
}
    if ( myfile9.is_open() ) {
		myfile9<<"Group"<<","<<"1y"<<"," << "5y"<<","<< "10y" <<","<< "10y-5y" <<","<< "5y-1y" <<","<< "10y-1y"<<"#curves"<<","<<"#entities\n";
		for (int i=0 ; i<17; i++){
                        t[i][0].trier();
                        t[i][1].trier();
                        t[i][2].trier();
                        myfile9<<"("<<100*i<<"-"<<100*i+100<<")"<<","<<t[i][0].moyenne()<<","<<t[i][1].moyenne()<<","<<t[i][2].moyenne()<<","<<t[i][2].moyenne()-t[i][1].moyenne()<<","<<t[i][1].moyenne()-t[i][0].moyenne()<<","<<t[i][2].moyenne()-t[i][0].moyenne()<<","<<curves.at(i)<<","<<entities.at(i)<<"\n";

        }
    QTableWidget* r = Tmain9(t,window,curves,entities);

    window->setCentralWidget(r);
    window->show();
    app.exec();
    }
if ( myfile.is_open() ) {
    myfile.close();
    window->setCentralWidget(tab);
    window->show();
    app.exec();
}
if ( myfile9.is_open() ) {myfile9.close();}

}

QTableWidget* tableau::Tmain9(vector<vector<table> > &t, QMainWindow *window, vector<int> &curves, vector<int> &entities)
{

        window->setWindowTitle(QString::fromUtf8("Tableau 9"));
        window->resize(400, 250);

    QTableWidget* table = new QTableWidget();


    table->setRowCount(19);
    table->setColumnCount(10);

    table->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    //Set Header Label Texts Here
    table->setHorizontalHeaderLabels(QString(";;;;;;;;;").split(";"));


    table->setItem(0,0,new QTableWidgetItem(QString("Average CDS premium (bps)")));
    table->setSpan(0,0,1,4);
    table->setItem(0,4,new QTableWidgetItem(QString("Average Slope (bps)")));
    table->setSpan(0,4,1,5);
    table->item(0,0)->setBackground(Qt::gray);
    table->item(0,4)->setBackground(Qt::gray);
            table->setItem(1,0,new QTableWidgetItem(QString("Group")));
            table->item(1,0)->setBackground(Qt::gray);
            table->setItem(1,1,new QTableWidgetItem(QString("1Y")));
            table->item(1,1)->setBackground(Qt::gray);
            table->setItem(1,2,new QTableWidgetItem(QString("5Y")));
            table->item(1,2)->setBackground(Qt::gray);
            table->setItem(1,3,new QTableWidgetItem(QString("10Y")));
            table->item(1,3)->setBackground(Qt::gray);
            table->setItem(1,4,new QTableWidgetItem(QString("10Y-5Y")));
            table->item(1,4)->setBackground(Qt::gray);
            table->setItem(1,5,new QTableWidgetItem(QString("5Y-1Y")));
            table->item(1,5)->setBackground(Qt::gray);
            table->setItem(1,6,new QTableWidgetItem(QString("10Y-1Y")));
            table->item(1,6)->setBackground(Qt::gray);
    table->setItem(1,7,new QTableWidgetItem(QString("#curves")));
    table->item(1,7)->setBackground(Qt::gray);
    table->setItem(1,8,new QTableWidgetItem(QString("#entities")));
    table->item(1,8)->setBackground(Qt::gray);
    //Add Table items here
    for (int i=2 ; i<19; i++){
    std::string str = '('+100*i+'-'+100*i+100+"bps)";
    table->setItem(i,0,new QTableWidgetItem(QString("(%1-%2bps)").arg(100*(i-2)).arg(100*(i-2)+100)));
    table->setItem(i,1,new QTableWidgetItem(QVariant(t[i-2][0].moyenne()).toString()));
    table->setItem(i,2,new QTableWidgetItem(QVariant(t[i-2][1].moyenne()).toString()));
    table->setItem(i,3,new QTableWidgetItem(QVariant(t[i-2][2].moyenne()).toString()));
    table->setItem(i,4,new QTableWidgetItem(QVariant(t[i-2][2].moyenne()-t[i-2][1].moyenne()).toString()));
    table->setItem(i,5,new QTableWidgetItem(QVariant(t[i-2][1].moyenne()-t[i-2][0].moyenne()).toString()));
    table->setItem(i,6,new QTableWidgetItem(QVariant(t[i-2][2].moyenne()-t[i-2][0].moyenne()).toString()));
    table->setItem(i,7,new QTableWidgetItem(QVariant(curves.at(i-2)).toString()));
    table->setItem(i,8,new QTableWidgetItem(QVariant(entities.at(i-2)).toString()));
    }
    //table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    return table;
}


QTableWidget* tableau::Tmain8(string note,table& t1, table& t2, table& t3, vector<double>& vD1, vector<double>& vD5, vector<double>& vD10, int i,QTableWidget* table){

    table->setRowCount(81);
    table->setColumnCount(8);
    //table->setTextElideMode(Qt::ElideNone);

    table->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    //Set Header Label Texts Here
    table->setHorizontalHeaderLabels(QString(";;;;;;;").split(";"));
    int d=0;
        if (9*i<81){
            d=0;
        }
        else{d=4;i=i-9;}
        table->setItem(9*i,0+d,new QTableWidgetItem(QVariant(note.c_str()).toString()));
        table->item(9*i,0+d)->setBackground(Qt::gray);
        table->setItem(9*i,1+d,new QTableWidgetItem(QString("5Y")));
        table->setItem(9*i,2+d,new QTableWidgetItem(QString("1Y")));
        table->setItem(9*i,3+d,new QTableWidgetItem(QString("10Y")));
        table->item(9*i,1+d)->setBackground(Qt::gray);
        table->item(9*i,2+d)->setBackground(Qt::gray);
        table->item(9*i,3+d)->setBackground(Qt::gray);

        table->setItem(9*i+1,0+d,new QTableWidgetItem(QString("Moyenne")));
        table->item(9*i+1,0+d)->setBackground(Qt::gray);
        table->setItem(9*i+1,1+d,new QTableWidgetItem(QVariant(t1.moyenne()).toString()));
        table->setItem(9*i+1,2+d,new QTableWidgetItem(QVariant(t2.moyenne()).toString()));
        table->setItem(9*i+1,3+d,new QTableWidgetItem(QVariant(t3.moyenne()).toString()));

        table->setItem(9*i+2,0+d,new QTableWidgetItem(QString("Mediane")));
        table->item(9*i+2,0+d)->setBackground(Qt::gray);
        table->setItem(9*i+2,1+d,new QTableWidgetItem(QVariant(t1.mediane()).toString()));
        table->setItem(9*i+2,2+d,new QTableWidgetItem(QVariant(t2.mediane()).toString()));
        table->setItem(9*i+2,3+d,new QTableWidgetItem(QVariant(t3.mediane()).toString()));

        table->setItem(9*i+3,0+d,new QTableWidgetItem(QString("Minimum")));
        table->item(9*i+3,d)->setBackground(Qt::gray);
        table->setItem(9*i+3,1+d,new QTableWidgetItem(QVariant(t1.minimum()).toString()));
        table->setItem(9*i+3,2+d,new QTableWidgetItem(QVariant(t2.minimum()).toString()));
        table->setItem(9*i+3,3+d,new QTableWidgetItem(QVariant(t3.minimum()).toString()));

        table->setItem(9*i+4,0+d,new QTableWidgetItem(QString("Maximum")));
        table->item(9*i+4,0+d)->setBackground(Qt::gray);
        table->setItem(9*i+4,1+d,new QTableWidgetItem(QVariant(t1.maximum()).toString()));
        table->setItem(9*i+4,2+d,new QTableWidgetItem(QVariant(t2.maximum()).toString()));
        table->setItem(9*i+4,3+d,new QTableWidgetItem(QVariant(t3.maximum()).toString()));

        table->setItem(9*i+5,0+d,new QTableWidgetItem(QString("Volatilite")));
        table->item(9*i+5,0+d)->setBackground(Qt::gray);
        table->setItem(9*i+5,1+d,new QTableWidgetItem(QVariant(t1.volatilite()).toString()));
        table->setItem(9*i+5,2+d,new QTableWidgetItem(QVariant(t2.volatilite()).toString()));
        table->setItem(9*i+5,3+d,new QTableWidgetItem(QVariant(t3.volatilite()).toString()));

        table->setItem(9*i+6,0+d,new QTableWidgetItem(QString("Skewness")));
        table->item(9*i+6,0+d)->setBackground(Qt::gray);
        table->setItem(9*i+6,1+d,new QTableWidgetItem(QVariant(t1.Skewness()).toString()));
        table->setItem(9*i+6,2+d,new QTableWidgetItem(QVariant(t2.Skewness()).toString()));
        table->setItem(9*i+6,3+d,new QTableWidgetItem(QVariant(t3.Skewness()).toString()));

        table->setItem(9*i+7,0+d,new QTableWidgetItem(QString("Kurtosis")));
        table->item(9*i+7,d)->setBackground(Qt::gray);
        table->setItem(9*i+7,1+d,new QTableWidgetItem(QVariant(t1.Kurtosis()).toString()));
        table->setItem(9*i+7,2+d,new QTableWidgetItem(QVariant(t2.Kurtosis()).toString()));
        table->setItem(9*i+7,3+d,new QTableWidgetItem(QVariant(t3.Kurtosis()).toString()));

        table->setItem(9*i+8,0+d,new QTableWidgetItem(QString("AC1")));
        table->item(9*i+8,d)->setBackground(Qt::gray);
        table->setItem(9*i+8,1+d,new QTableWidgetItem(QVariant((double) std::accumulate(vD1.begin(),vD1.end(),0.0)/vD1.size()).toString()));
        table->setItem(9*i+8,2+d,new QTableWidgetItem(QVariant((double) std::accumulate(vD5.begin(),vD5.end(),0.0)/vD5.size()).toString()));
        table->setItem(9*i+8,3+d,new QTableWidgetItem(QVariant((double) std::accumulate(vD10.begin(),vD10.end(),0.0)/vD10.size()).toString()));
       // }
        if(d==4){i+=9;}
    return table;
}
