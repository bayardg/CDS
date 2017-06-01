
#include "themewidget.h"
#include "parse.h"

#include <QtCharts/QChart>
#include <QValueAxis>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QAbstractBarSeries>
#include <QtCharts/QPercentBarSeries>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QLegend>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QSpinBox>
#include <QDateTimeAxis>
#include <QtWidgets/QCheckBox>
#include <cstring>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtCore/QTime>
#include <QtCharts/QBarCategoryAxis>

ThemeWidget::ThemeWidget(parse fichier, QWidget *parent) :
    QWidget(parent),
    mapPays(fichier.getMapPays()),
    m_yearComboBox(createYearBox()),
    m_paysBox(createCountryBox()),
    baseLayout(new QGridLayout())
{
    //mapPays= fichier.getMapPays();
    connectSignals();
    // create layout
    QHBoxLayout *settingsLayout = new QHBoxLayout();
    settingsLayout->addWidget(new QLabel("Pays"));
    settingsLayout->addWidget(m_paysBox);
    settingsLayout->addWidget(new QLabel("1Y/5Y/10Y:"));
    settingsLayout->addWidget(m_yearComboBox);
    settingsLayout->addStretch();
    baseLayout->addLayout(settingsLayout, 0, 0, 1, 3);

    //create charts

    QChartView *chartView;

    chartView = new QChartView(new QChart(),Q_NULLPTR);
    baseLayout->addWidget(chartView, 1, 0);
    m_charts << chartView;

    setLayout(baseLayout);

    // Set defaults
    updateUI();



}

ThemeWidget::~ThemeWidget()
{
}

void ThemeWidget::connectSignals()
{
    connect(m_yearComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateUI()));
    connect(m_paysBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateUI()));

}



QComboBox *ThemeWidget::createCountryBox() const
{
    QComboBox *countryComboBox = new QComboBox();
    countryComboBox->addItem("Choisissez un pays");
    for(auto& x : mapPays){
        countryComboBox->addItem(QVariant(x.first.c_str()).toString());
    }
    return countryComboBox;
}


QComboBox *ThemeWidget::createYearBox() const
{
    QComboBox *yearComboBox = new QComboBox();
    yearComboBox->addItem("1Y", 0);
    yearComboBox->addItem("5Y",1);
    yearComboBox->addItem("10Y",2);
    yearComboBox->addItem("all",3);
    return yearComboBox;
}

QChart *ThemeWidget::createAreaChart(QLineSeries *series) const
{
        QChart *chart = new QChart();
        chart->legend()->hide();
        chart->addSeries(series);
    return chart;
}



void ThemeWidget::updateChart(int k){
    QLineSeries *series5Y = new QLineSeries();
    series5Y->setName(QString("evolution 5Y"));
    QLineSeries *series1Y = new QLineSeries();
    QLineSeries *series10Y = new QLineSeries();
    series1Y->setName(QString("evolution 1Y"));
    series10Y->setName(QString("evolution 10Y"));
    int i =0;
    for (auto& x: mapPays){
        if(QString::compare(QVariant(x.first.c_str()).toString(),m_paysBox->itemText(m_paysBox->currentIndex()), Qt::CaseInsensitive)==0){
            for (auto& y : x.second){
                if(atof(y.at(3).substr(1,y.at(3).size()-2).c_str())!=0){
                QDateTime moment;
                moment.setDate(conversionDate(y.at(1).substr(1,y.at(1).size()-2).c_str()));
                series5Y->append(moment.toMSecsSinceEpoch(),atof(y.at(3).substr(1,y.at(3).size()-2).c_str()));}
                if(atof(y.at(4).substr(1,y.at(4).size()-2).c_str())!=0){
                QDateTime moment;
                moment.setDate(conversionDate(y.at(1).substr(1,y.at(1).size()-2).c_str()));
                series1Y->append(moment.toMSecsSinceEpoch(),atof(y.at(4).substr(1,y.at(4).size()-2).c_str()));
                }
                if(atof(y.at(5).substr(1,y.at(5).size()-2).c_str())!=0){
                QDateTime moment;
                moment.setDate(conversionDate(y.at(1).substr(1,y.at(1).size()-2).c_str()));
                series10Y->append(moment.toMSecsSinceEpoch(),atof(y.at(5).substr(1,y.at(5).size()-2).c_str()));}
                i++;
            }
        }
    }
if(k==1){
    QChart *chart5 = createAreaChart(series5Y);
    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setFormat("dd-MMM-yy");
    axisX->setTitleText("Date");
    chart5->addAxis(axisX, Qt::AlignBottom);
    series5Y->attachAxis(axisX);
    QValueAxis *axisY = new QValueAxis;
    axisY->setLabelFormat("%i");
    axisY->setTitleText("CDS spread");
    chart5->addAxis(axisY, Qt::AlignLeft);
    series5Y->attachAxis(axisY);

  //  chart5->createDefaultAxes();
    chart5->setTitle("CDS spread 5Y");
    QChartView *chartView5;
    chartView5 = new QChartView(chart5,Q_NULLPTR);
    chartView5->chart()->setTheme(QChart::ChartThemeBlueCerulean);
    chartView5->setRenderHint(QPainter::Antialiasing, true);
    chartView5->setRubberBand(QChartView::HorizontalRubberBand);
    baseLayout->addWidget(chartView5, 1, 0);
    m_charts << chartView5;
}
else if(k==0){
    QChart *chart1 = createAreaChart(series1Y);
    //chart1->createDefaultAxes();
    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setFormat("dd-MMM-yy");
    axisX->setTitleText("Date");
    chart1->addAxis(axisX, Qt::AlignBottom);
    series1Y->attachAxis(axisX);
    QValueAxis *axisY = new QValueAxis;
    axisY->setLabelFormat("%i");
    axisY->setTitleText("CDS spread");
    chart1->addAxis(axisY, Qt::AlignLeft);
    series1Y->attachAxis(axisY);
    chart1->setTitle("CDS spread 1Y");
    QChartView *chartView1;
    chartView1 = new QChartView(chart1,Q_NULLPTR);
    chartView1->chart()->setTheme(QChart::ChartThemeBlueCerulean);
    chartView1->setRenderHint(QPainter::Antialiasing, true);
    chartView1->setRubberBand(QChartView::HorizontalRubberBand);
    baseLayout->addWidget(chartView1, 1, 0);
    m_charts << chartView1;
}
else if(k==2){
    QChart *chart10 = createAreaChart(series10Y);
    //chart10->createDefaultAxes();
    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setFormat("dd-MMM-yy");
    axisX->setTitleText("Date");
    chart10->addAxis(axisX, Qt::AlignBottom);
    series10Y->attachAxis(axisX);
    QValueAxis *axisY = new QValueAxis;
    axisY->setLabelFormat("%i");
    axisY->setTitleText("CDS spread");
    chart10->addAxis(axisY, Qt::AlignLeft);
    series10Y->attachAxis(axisY);
    chart10->setTitle("CDS spread 10Y");
    QChartView *chartView10;
    chartView10 = new QChartView(chart10,Q_NULLPTR);
    chartView10->chart()->setTheme(QChart::ChartThemeBlueCerulean);
    chartView10->setRenderHint(QPainter::Antialiasing, true);
    chartView10->setRubberBand(QChartView::HorizontalRubberBand);
    baseLayout->addWidget(chartView10, 1, 0);
    m_charts << chartView10;
}
else{
    QChart *chartAll = createAreaChart(series10Y);
    chartAll->addSeries(series5Y);
    chartAll->addSeries(series1Y);
    //chartAll->createDefaultAxes();
    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setFormat("dd-MMM-yy");
    axisX->setTitleText("Date");
    chartAll->addAxis(axisX, Qt::AlignBottom);
    series5Y->attachAxis(axisX);
    series10Y->attachAxis(axisX);
    series1Y->attachAxis(axisX);
    QValueAxis *axisY = new QValueAxis;
    axisY->setLabelFormat("%i");
    axisY->setMax(10500);
    axisY->setMin(0);
    axisY->setTitleText("CDS spread");
    chartAll->addAxis(axisY, Qt::AlignLeft);
    //series5Y->attachAxis(axisY);
    series5Y->attachAxis(axisY);
    series10Y->attachAxis(axisY);
    series1Y->attachAxis(axisY);
    chartAll->setTitle("CDS spread 1Y,5Y and 10Y");
    QChartView *chartViewAll;
    chartViewAll = new QChartView(chartAll,Q_NULLPTR);
    chartViewAll->chart()->setTheme(QChart::ChartThemeDark);
    chartViewAll->chart()->legend()->setAlignment(Qt::AlignTop);
    chartViewAll->chart()->legend()->show();
    chartViewAll->setRenderHint(QPainter::Antialiasing, true);
    chartViewAll->setRubberBand(QChartView::RectangleRubberBand);
    baseLayout->addWidget(chartViewAll, 1, 0);
    m_charts << chartViewAll;
}

}

QDate ThemeWidget::conversionDate(string str){
    int m=0;
    if(std::strstr(str.c_str(),"janv.") != NULL){
        m=1;}
    if(std::strstr(str.c_str(),"févr.") != NULL){
        m=2;}
    if(std::strstr(str.c_str(),"mars") != NULL){
        m=3;}
    if(std::strstr(str.c_str(),"avr.") != NULL){
        m=4;}
    if(std::strstr(str.c_str(),"mai") != NULL){
        m=5;}
    if(std::strstr(str.c_str(),"juin") != NULL){
        m=6;}
    if(std::strstr(str.c_str(),"juil.") != NULL){
        m=7;}
    if(std::strstr(str.c_str(),"août") != NULL){
        m=8;}
    if(std::strstr(str.c_str(),"sept.") != NULL){
        m=9;}
    if(std::strstr(str.c_str(),"oct.") != NULL){
        m=10;}
    if(std::strstr(str.c_str(),"nov.") != NULL){
        m=11;}
    if(std::strstr(str.c_str(),"déc.") != NULL){
        m=12;}
    return QDate(atoi(str.substr(str.size()-2,2).c_str()),m,atoi(str.substr(0,2).c_str()));
}

void ThemeWidget::updateUI()
{
        QPalette pal = window()->palette();

            pal.setColor(QPalette::Window, QRgb(0x40434a));
            pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));

        window()->setPalette(pal);
    updateChart(m_yearComboBox->itemData(m_yearComboBox->currentIndex()).toInt());
}
