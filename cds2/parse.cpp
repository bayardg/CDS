#include "parse.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <unordered_map>
#include<vector>
#include <math.h>
#include <algorithm>
using namespace std;
parse::~parse()
{
    map.clear();
    mapPays.clear();
}
parse::parse(const parse &p){
    this->map=p.map;
    this->mapPays=p.mapPays;
}
parse & parse::operator=(const parse &V){
    this->map=V.map;
    this->mapPays=V.mapPays;
    return *this;
}
parse::parse(int d, string myFile)
{
    choix =d;
    ifstream indata(myFile.c_str());
    string line;
    getline(indata,line);
    while(getline(indata,line)){
        istringstream str(line);
        vector<string> values;
        string data;
        string eData="";
        int k=0;
        while(getline(str,data,',')){
            if(std::count(data.begin(),data.end(),'"')%2==1){
                k+=1;}
            else{ k=0;
                data=data+'.';
            }
            if (k==1){
                eData = data;
            }
            else{
                k=0;
                values.push_back(eData+"."+data);
                eData ="";
            }
        }
        int m;
        if (choix==4){
            m = parse::moyenne(values);} //moyenne
        else if(choix==1){
            m = parse::nbr_Corr(1,values.at(6).c_str());} // agence 1 (Moody’s Analytics) seulement
        else if(choix==2){
            m = parse::nbr_Corr(2,values.at(7).c_str());} // agence 2 (Standard & Poors) seulement
        else if(choix==3){
            m = parse::nbr_Corr(3,values.at(8).c_str());} // agence 3 (Fitch Ratings) seulement
        map[m].push_back(values);
        values.push_back(std::to_string(m));
        mapPays[values.at(2).c_str()].push_back(values);
    }
    indata.close();
}

int parse::moyenne(vector<string> v)
{
    double i = double (nbr_Corr(1,v.at(6).c_str())+nbr_Corr(2,v.at(7).c_str())+nbr_Corr(3,v.at(8).c_str()))/3.0;
    return (double)floor(i)+0.5>i ? floor(i) : floor(i)+1;
}

int parse::nbr_Corr(int d,string str){
    if (d==1 || d==2 || d==4){
        if(str.compare(1,3,"AAA")==0){ return 19;}
        else if(str.compare(1,3,"AA+")==0){ return 18;}
        else if(str.compare(1,3,"AA-")==0){ return 16;}
        else if(str.compare(1,2,"AA")==0){ return 17;}
        else if(str.compare(1,2,"A+")==0){ return 15;}
        else if(str.compare(1,2,"A-")==0){ return 13;}
        else if(str.compare(1,1,"A")==0){ return 14;}
        else if(str.compare(1,4,"BBB+")==0){ return 12;}
        else if(str.compare(1,4,"BBB-")==0){ return 10;}
        else if(str.compare(1,3,"BBB")==0){ return 11;}
        else if(str.compare(1,3,"BB+")==0){ return 9;}
        else if(str.compare(1,3,"BB-")==0){ return 7;}
        else if(str.compare(1,2,"BB")==0){ return 8;}
        else if(str.compare(1,2,"B+")==0){ return 6;}
        else if(str.compare(1,2,"B-")==0){ return 4;}
        else if(str.compare(1,1,"B")==0){ return 5;}
        else if(str.compare(1,4,"CCC+")==0 && d==2){ return 3;}
        else if(str.compare(1,4,"CCC-")==0 && d==2){ return 3;}
        else if(str.compare(1,3,"CCC")==0){ return 3;}
        else if(str.compare(1,2,"CC")==0){ return 2;}
        else if(str.compare(1,1,"C")==0){ return 2;}
        else if(str.compare(1,2,"RD")==0 && d==1){ return 1;}
        else if(str.compare(1,1,"D")==0){ return 1;}
        else if(str.compare(1,2,"SD")==0 && d==2){ return 1;}
        else if(str.compare(1,2,"NR")==0){ return 0;}
    }
    else if(d==3){
        if(str.compare(1,3,"Aaa")==0){ return 19;}
        else if(str.compare(1,3,"Aa1")==0){ return 18;}
        else if(str.compare(1,3,"Aa2")==0){ return 17;}
        else if(str.compare(1,3,"Aa3")==0){ return 16;}
        else if(str.compare(1,2,"A1")==0){ return 15;}
        else if(str.compare(1,2,"A2")==0){ return 14;}
        else if(str.compare(1,2,"A3")==0){ return 13;}
        else if(str.compare(1,4,"Baa1")==0){ return 12;}
        else if(str.compare(1,4,"Baa2")==0){ return 11;}
        else if(str.compare(1,4,"Baa3")==0){ return 10;}
        else if(str.compare(1,3,"Ba1")==0){ return 9;}
        else if(str.compare(1,3,"Ba2")==0){ return 8;}
        else if(str.compare(1,3,"Ba3")==0){ return 7;}
        else if(str.compare(1,2,"B1")==0){ return 6;}
        else if(str.compare(1,2,"B2")==0){ return 5;}
        else if(str.compare(1,2,"B3")==0){ return 4;}
        else if(str.compare(1,4,"Caa1")==0){ return 3;}
        else if(str.compare(1,4,"Caa2")==0){ return 3;}
        else if(str.compare(1,4,"Caa3")==0){ return 3;}
        else if(str.compare(1,2,"Ca")==0){ return 2;}
        else if(str.compare(1,1,"C")==0){ return 1;}
        else if(str.compare(1,2,"NR")==0){ return 0;}
    }
    std::cout << "Agence inconnue ou notation incorrecte : " << str.c_str() <<std::endl;
    return 0;
}

string parse::nbrConv(int d, int nbr){    //Cette methode devra faire correspondre à chaque entier une note
    if(d==3){
        if(nbr==19){ return "Aaa";}
        if(nbr==18){ return "Aa1";}
        if(nbr==17){ return "Aa2";}
        if(nbr==16){ return "Aa3";}
        if(nbr==15){ return "A1";}
        if(nbr==14){ return "A2";}
        if(nbr==13){ return "A3";}
        if(nbr==12){ return "Baa1";}
        if(nbr==11){ return "Baa2";}
        if(nbr==10){ return "Baa3";}
        if(nbr==9){ return "Ba1";}
        if(nbr==8){ return "Ba2";}
        if(nbr==7){ return "Ba3";}
        if(nbr==6){ return "B1";}
        if(nbr==5){ return "B2";}
        if(nbr==4){ return "B3";}
        if(nbr==3){ return "Caa1";}
        if(nbr==2){ return "Ca";}
        if(nbr==1){ return "C";}
        if(nbr==0){ return "NR";}
}
    else{
        if(nbr==19){ return "AAA";}
        if(nbr==18){ return "AA+";}
        if(nbr==17){ return "AA";}
        if(nbr==16){ return "AA-";}
        if(nbr==15){ return "A+";}
        if(nbr==14){ return "A";}
        if(nbr==13){ return "A-";}
        if(nbr==12){ return "BBB+";}
        if(nbr==11){ return "BBB";}
        if(nbr==10){ return "BBB-";}
        if(nbr==9){ return "BB+";}
        if(nbr==8){ return "BB";}
        if(nbr==7){ return "BB-";}
        if(nbr==6){ return "B+";}
        if(nbr==5){ return "B";}
        if(nbr==4){ return "B-";}
        if(nbr==3){ return "CCC";}
        if(nbr==2){ return "CC";}
        if(nbr==1){ return "D";}
        if(nbr==0){ return "NR";}
}
 return "wrong number";
}

double parse::dateConv(string str){
    double v=0;
    if(std::strstr(str.c_str(),"janv.") != NULL){
        v+=atof(str.substr(0,3).c_str());
        v+=100.0*1.0;
        v+=10000.0*atof(str.substr(10,2).c_str());}
    if(std::strstr(str.c_str(),"févr.") != NULL){
        v+=atof(str.substr(0,3).c_str());
        v+=100.0*2.0;
        v+=10000.0*atof(str.substr(10,2).c_str());}
    if(std::strstr(str.c_str(),"mars") != NULL){
        v+=atof(str.substr(0,3).c_str());
        v+=100.0*3.0;
        v+=10000.0*atof(str.substr(9,2).c_str());}
    if(std::strstr(str.c_str(),"avr.") != NULL){
        v+=atof(str.substr(0,3).c_str());
        v+=100.0*4.0;
        v+=10000.0*atof(str.substr(9,2).c_str());}
    if(std::strstr(str.c_str(),"mai") != NULL){
        v+=atof(str.substr(0,3).c_str());
        v+=100.0*5.0;
        v+=10000.0*atof(str.substr(8,2).c_str());}
    if(std::strstr(str.c_str(),"juin") != NULL){
        v+=atof(str.substr(0,3).c_str());
        v+=100.0*6.0;
        v+=10000.0*atof(str.substr(9,2).c_str());}
    if(std::strstr(str.c_str(),"juil.") != NULL){
        v+=atof(str.substr(0,3).c_str());
        v+=100.0*7.0;
        v+=10000.0*atof(str.substr(10,2).c_str());}
    if(std::strstr(str.c_str(),"août") != NULL){
        v+=atof(str.substr(0,3).c_str());
        v+=100.0*8.0;
        v+=10000.0*atof(str.substr(9,2).c_str());}
    if(std::strstr(str.c_str(),"sept.") != NULL){
        v+=atof(str.substr(0,3).c_str());
        v+=100.0*9.0;
        v+=10000.0*atof(str.substr(10,2).c_str());}
    if(std::strstr(str.c_str(),"oct.") != NULL){
        v+=atof(str.substr(0,3).c_str());
        v+=100.0*10.0;
        v+=10000.0*atof(str.substr(9,2).c_str());}
    if(std::strstr(str.c_str(),"nov.") != NULL){
        v+=atof(str.substr(0,3).c_str());
        v+=100.0*11.0;
        v+=10000.0*atof(str.substr(9,2).c_str());}
    if(std::strstr(str.c_str(),"déc.") != NULL){
        v+=atof(str.substr(0,3).c_str());
        v+=100.0*12.0;
        v+=10000.0*atof(str.substr(9,2).c_str());}
    return v;
}

parse::parse(){}
struct compareDates{
bool operator()(const vector<string>& a, const vector<string>& b){
    parse p = parse();
 return p.dateConv(a.at(1).c_str()) < p.dateConv(b.at(1).c_str());
}}compareDates;

vector<vector<vector<string> > > parse::getDataCountry(int d, string strNote, string strCountry)  //c pour le nom du pays, d pour le numero de l'agence financière et str pour la note des agences financières
{
    vector<vector<vector<string>>> vec0;
    vector<vector<string>> vec1;
    vector<vector<string>> vec5;
    vector<vector<string>> vec10;
    for (auto& y : mapPays){
        if(strCountry.compare(1,strCountry.size()-2,y.first,1,y.first.size()-2)==0){
            vec1.reserve(y.second.capacity());
            vec5.reserve(y.second.capacity());
            vec10.reserve(y.second.capacity());
            for (auto& x : y.second){
            vector<string> a;
            a.reserve(3);
            a.push_back(x.at(3).substr(1,x.at(3).size()-2).c_str());
            a.push_back(x.at(1).c_str());
            a.push_back(x.at(9).c_str());
            vec5.push_back(a);

            vector<string> z;
            z.reserve(3);
            z.push_back(x.at(4).substr(1,x.at(4).size()-2).c_str());
            z.push_back(x.at(1).c_str());
            z.push_back(x.at(9).c_str());
            vec1.push_back(z);

            vector<string> e;
            e.reserve(3);
            e.push_back(x.at(5).substr(1,x.at(5).size()-2).c_str());
            e.push_back(x.at(1).c_str());
            e.push_back(x.at(9).c_str());
            vec10.push_back(e);

        }
        }
    }
    std::sort(vec1.begin(),vec1.end(),compareDates);
    std::sort(vec5.begin(),vec5.end(),compareDates);
    std::sort(vec10.begin(),vec10.end(),compareDates);
    string str1="";
    string str5="";
    string str10="";
    for (size_t i=0;i<vec1.size();i++){
        if(atof(vec1.at(i).at(2).c_str()) == nbr_Corr(d,strNote)){
            vec1.at(i).at(2)=str1;
            str1 = vec1.at(i).at(0);
            vec5.at(i).at(2)=str5;
            str5 = vec5.at(i).at(0);
            vec10.at(i).at(2)=str10;
            str10 = vec10.at(i).at(0);
        }
        else{
            str1=vec1.at(i).at(0);
            str5=vec5.at(i).at(0);
            str10=vec10.at(i).at(0);
            vec1.erase(vec1.begin()+i);
            vec5.erase(vec5.begin()+i);
            vec10.erase(vec10.begin()+i);
            i--;
        }
    }
    vec0.reserve(3);
    vec0.push_back(vec1);
    vec0.push_back(vec5);
    vec0.push_back(vec10);
    return vec0;
}
