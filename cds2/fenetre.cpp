#include "fenetre.h"
#include <iostream>
using namespace std;


QString globalDossier;
int globalNumTab = 8;
int typeNote=2;

fenetre::fenetre() : QWidget()
{

    QFont police("Times New Roman", 10, QFont::Bold, true);
    this->setWindowTitle("Credit Default Swap");
    // Layout principal
    layout = new QGridLayout;

    // Gestion bouton quitter et choix du fichier //

    bouton1 = new QPushButton("Choix du fichier", this);
    bouton = new QPushButton("Lancer l'affichage", this);
    bouton->setFont(police);
    bouton1->setFont(police);


    bouton->setCursor(Qt::PointingHandCursor);
    bouton1->setCursor(Qt::PointingHandCursor);
    bouton->setShortcut(tr("ENTER"));

    // Layout pour les boutons
    QHBoxLayout *boutonLayout = new QHBoxLayout;
    boutonLayout->addWidget(bouton1);
    boutonLayout->addWidget(bouton);


    // Création GroupBox pour le choix du tableau
    QGroupBox *groupbox = new QGroupBox("Choix de la fonctionnalité",this);

    box1 = new QRadioButton("Tableau 8");
    box2 = new QRadioButton("Tableau 9");
    box3 = new QRadioButton("Evolution des CDS");

    box1->setChecked(true);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(box1);
    vbox->addWidget(box2);
    vbox->addWidget(box3);

    groupbox->setLayout(vbox);
    groupbox->move(5,5);

    // Création GroupBox pour le choix de la note
    QGroupBox *groupboxNote = new QGroupBox("Choix de la notation", this);

    fitch = new QRadioButton("Fitch");
    moody = new QRadioButton("Moody's");
    snp = new QRadioButton("Standard and Poor's");
    mean = new QRadioButton("Moyenne des 3");
    fitch->setChecked(true);

    // //////////////////////////////
    QVBoxLayout *noteLayout = new QVBoxLayout;
    noteLayout->addWidget(fitch);
    noteLayout->addWidget(moody);
    noteLayout->addWidget(snp);
    noteLayout->addWidget(mean);
    groupboxNote->setLayout(noteLayout);



    // ///////////////////////////

    // Paramètrisation du layout principal

    layout->addLayout(boutonLayout,1,1);
    layout->addWidget(groupboxNote,0,1);
    layout->addWidget(groupbox,0,0);
    this->setLayout(layout);




    QObject::connect(bouton, SIGNAL(clicked()), qApp, SLOT(quit()));

    QObject::connect(bouton1, SIGNAL(clicked()), this,SLOT(openFile()));



}
void fenetre::openFile(void)
{
     if ( fitch->isChecked() == true) {
         typeNote =1;
     }
     if (moody->isChecked() == true) {
         typeNote = 2;
     }
     if ( snp->isChecked() == true) {
         typeNote =3;
     }
     if ( mean->isChecked() == true) {
         typeNote = 4;
     }

     if (box1->isChecked() == true) {
         globalNumTab = 8;
     }

     if (box2->isChecked() == true) {
         globalNumTab = 9;
     }

     globalDossier = QFileDialog::getOpenFileName(this,"open");
     cout <<  "nom du fichier :" << globalDossier.toStdString() << endl;

}

bool fenetre::box3Checked(){
    return box3->isChecked();
}

void fenetre::ouvrirItem(void)
{
    globalNumTab = QInputDialog::getInt(this, "Choix du tableau", "Entrer 8 ou 9 en fonction du tableau souhaité");
}

int fenetre::getTypeTab()
{
    return globalNumTab;
}


void fenetre::choixNote(void)
{
    typeNote = QInputDialog::getInt(this,"Choix de la note", "1:Moody's, 2:Fitch, 3:Standards, 4: Moyenne des 3");

}

int fenetre::getTypeNote(void) {
    return typeNote;
}


std::string fenetre::getGlobalFile(void)
{


    return globalDossier.toStdString();
}
