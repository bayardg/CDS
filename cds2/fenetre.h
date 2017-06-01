#ifndef FENETRE_H
#define FENETRE_H
#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QLCDNumber>
#include <QCheckBox>
#include <QSlider>
#include <QFileDialog>
#include <QString>
#include <QInputDialog>
#include <QRadioButton>
#include <QGridLayout>
#include <QtWidgets>
#include <QVBoxLayout>

/*! \namespace fenetre
 *
 * Classe permettant la création de la fenetre d'accueil
 */
class fenetre : public QWidget
{
    Q_OBJECT
public:
    fenetre();
    void ouvrirItem(void);
    std::string getGlobalFile(void);
    void choixNote(void);
    int getTypeNote(void);
    int getTypeTab();
    bool box3Checked();

public slots:

    void openFile(void);




private:
    QPushButton *bouton;
    QPushButton *bouton1;

    QRadioButton *box1;
    QRadioButton *box2;
    QRadioButton *box3;

    QRadioButton *fitch;
    QRadioButton *snp;
    QRadioButton *moody;
    QRadioButton *mean;

    QGridLayout *layout;

};

#endif // FENETRE_H
