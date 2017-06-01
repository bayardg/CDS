#ifndef THEMEWIDGET_H
#define THEMEWIDGET_H

#include <QtWidgets/QWidget>
#include <QtCharts/QChartGlobal>
#include "parse.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <QtCharts/QLineSeries>
#include <QtWidgets/QGridLayout>


#include <QtCharts/QChart>
#include <QtCore/QTimer>


class QComboBox;
class QCheckBox;

QT_CHARTS_BEGIN_NAMESPACE
class QSplineSeries;
class QValueAxis;

class QChartView;
class QChart;
QT_CHARTS_END_NAMESPACE

typedef QPair<QPointF, QString> Data;
typedef QList<Data> DataList;
typedef QList<DataList> DataTable;

QT_CHARTS_USE_NAMESPACE

/*! \namespace ThemeWidget
 *
 * Classe permettant la création de la fenetre contenant les courbes CDS
 */
class ThemeWidget: public QWidget
{
    Q_OBJECT
public:
    /*!
     *  \brief Constructeur
     *
     */
    explicit ThemeWidget(parse fichier,QWidget *parent = 0);
    ~ThemeWidget();

private Q_SLOTS:
    /*!
     *  \brief mettre à jour la fenetre
     *
     */
    void updateUI();
    /*!
     *  \brief mettre à jour les courbes
     *
     */
    void updateChart(int k);

private:
    /*!
     *  \brief create Country Box
     *
     */
    QComboBox *createCountryBox() const;
    /*!
     *  \brief create Year Box
     *
     */
    QComboBox *createYearBox() const;
    /*!
     *  \brief Connecter les signaux
     *
     */
    void connectSignals();
    /*!
     *  \brief créer un objet Qchart
     *
     */
    QChart *createAreaChart(QLineSeries *series) const;
    /*!
     *  \brief Convertir le string en une date de type QDate
     *
     */
    QDate conversionDate(string str);

private:

    QList<QChartView *> m_charts;

    unordered_map <string, vector<vector<string>>> mapPays;

    QComboBox *m_yearComboBox;
    QComboBox *m_paysBox;
    QGridLayout *baseLayout;

};

#endif /* THEMEWIDGET_H */
