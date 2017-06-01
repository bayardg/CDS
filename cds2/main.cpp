#include <string>
#include <iomanip>
#include "parse.h"
#include "assert.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <cstring>
#include <math.h>
#include <iomanip>
#include <unordered_map>
#include <algorithm>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include "table.h"
#include "tableau.h"
#include <unistd.h>
// fus //
#include <QApplication>
#include <QPushButton>
#include <QCheckBox>
#include "fenetre.h"
#include "themewidget.h"
// //////////////


int main(int argc, char *argv[])
{

    // FUSION //
    QApplication app(argc, argv);
    //Creation fenetre
    fenetre MaFenetre;
    MaFenetre.show();

    app.exec();


    // //////////////////
    int d = MaFenetre.getTypeNote();
    cout << d << endl ;
    parse fichierParse(d,MaFenetre.getGlobalFile());


    // ////////////////
    if(MaFenetre.box3Checked()){
    QApplication a(argc, argv);
    QMainWindow window;
    ThemeWidget *widget = new ThemeWidget(fichierParse);
    window.setCentralWidget(widget);
    window.resize(900, 600);
    window.show();
    a.exec();}

    // //////////
    else{
        tableau tab(d,MaFenetre.getTypeTab(),fichierParse,argc, argv);
    }


return 0;
}


