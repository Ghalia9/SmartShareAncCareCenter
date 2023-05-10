
#include "themewidget1.h"

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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtCore/QTime>
#include <QtCharts/QBarCategoryAxis>
#include <QSqlQuery>

ThemeWidget1::ThemeWidget1(QWidget *parent) :
    QWidget(parent),
    m_listCount(3),
    m_valueMax(10),
    m_valueCount(7),
  //  m_dataTable(generateRandomData(m_listCount, m_valueMax, m_valueCount)),
    m_themeComboBox(createThemeBox()),
    m_antialiasCheckBox(new QCheckBox("Anti-aliasing")),
    m_animatedComboBox(createAnimationBox()),
    m_legendComboBox(createLegendBox())
{
    connectSignals();
    // create layout
    QGridLayout *baseLayout = new QGridLayout();
    QHBoxLayout *settingsLayout = new QHBoxLayout();
    settingsLayout->addWidget(new QLabel("Theme:"));
    settingsLayout->addWidget(m_themeComboBox);
    settingsLayout->addWidget(new QLabel("Animation:"));
    settingsLayout->addWidget(m_animatedComboBox);
    settingsLayout->addWidget(new QLabel("Legend:"));
    settingsLayout->addWidget(m_legendComboBox);
    settingsLayout->addWidget(m_antialiasCheckBox);
    settingsLayout->addStretch();
    baseLayout->addLayout(settingsLayout, 0, 0, 1, 3);
    QChartView *chartView;
    chartView = new QChartView(createPieChart());
    // Funny things happen if the pie slice labels do not fit the screen, so we ignore size policy
    chartView->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    baseLayout->addWidget(chartView, 2, 0);
    m_charts << chartView;
    setLayout(baseLayout);
    // Set defaults
    m_antialiasCheckBox->setChecked(true);
    updateUI();
}
ThemeWidget1::~ThemeWidget1()
{
}

void ThemeWidget1::connectSignals()
{
    connect(m_themeComboBox,
            static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, &ThemeWidget1::updateUI);
    connect(m_antialiasCheckBox, &QCheckBox::toggled, this, &ThemeWidget1::updateUI);
    connect(m_animatedComboBox,
            static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, &ThemeWidget1::updateUI);
    connect(m_legendComboBox,
            static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, &ThemeWidget1::updateUI);
}

DataTable ThemeWidget1::generateRandomData(int valueMax, int valueCount) const
{
    DataTable dataTable;

    // set seed for random stuff
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    // generate random data
    for (int i(0); i < 2; i++) { // modify listCount to 2
        DataList dataList;
        qreal yValue(0);
        for (int j(0); j < 2; j++) { // modify valueCount to 2
            yValue = yValue + (qreal)(qrand() % valueMax) / (qreal) 2; // use 2 instead of valueCount
            QPointF value((j + (qreal) rand() / (qreal) RAND_MAX) * ((qreal) m_valueMax / (qreal) 2), yValue); // use 2 instead of valueCount
            QString label = "Slice " + QString::number(i) + ":" + QString::number(j);
            dataList << Data(value, label);
        }
        dataTable << dataList;
    }

    return dataTable;
}

QComboBox *ThemeWidget1::createThemeBox() const
{
    // settings layout
    QComboBox *themeComboBox = new QComboBox();
    themeComboBox->addItem("Light", QChart::ChartThemeLight);
    themeComboBox->addItem("Blue Cerulean", QChart::ChartThemeBlueCerulean);
    themeComboBox->addItem("Dark", QChart::ChartThemeDark);
    themeComboBox->addItem("Brown Sand", QChart::ChartThemeBrownSand);
    themeComboBox->addItem("Blue NCS", QChart::ChartThemeBlueNcs);
    themeComboBox->addItem("High Contrast", QChart::ChartThemeHighContrast);
    themeComboBox->addItem("Blue Icy", QChart::ChartThemeBlueIcy);
    themeComboBox->addItem("Qt", QChart::ChartThemeQt);
    return themeComboBox;
}

QComboBox *ThemeWidget1::createAnimationBox() const
{
    // settings layout
    QComboBox *animationComboBox = new QComboBox();
    animationComboBox->addItem("No Animations", QChart::NoAnimation);
    animationComboBox->addItem("GridAxis Animations", QChart::GridAxisAnimations);
    animationComboBox->addItem("Series Animations", QChart::SeriesAnimations);
    animationComboBox->addItem("All Animations", QChart::AllAnimations);
    return animationComboBox;
}

QComboBox *ThemeWidget1::createLegendBox() const
{
    QComboBox *legendComboBox = new QComboBox();
    legendComboBox->addItem("No Legend ", 0);
    legendComboBox->addItem("Legend Top", Qt::AlignTop);
    legendComboBox->addItem("Legend Bottom", Qt::AlignBottom);
    legendComboBox->addItem("Legend Left", Qt::AlignLeft);
    legendComboBox->addItem("Legend Right", Qt::AlignRight);
    return legendComboBox;
}
/*
QChart *ThemeWidget1::createPieChart() const
{
    QChart *chart = new QChart();
    chart->setTitle("BUDGET VS COLLECTS");

    qreal pieSize = 10.0;
    QPieSeries *series = new QPieSeries(chart);

    // Get the sum of budgets and collections from the Collects table
    QSqlQuery query("SELECT SUM(collect_budget), SUM(collections) FROM Collects");
    query.next();
    double budgetSum = query.value(0).toDouble();
    double collectionSum = query.value(1).toDouble();

    // Add the sum of budgets and collections to the pie chart
    series->append("Budget", budgetSum);
    series->append("Collections", collectionSum);

    // Set the properties of the pie chart
    series->setPieSize(pieSize);
    series->setHorizontalPosition(0.5);
    series->setVerticalPosition(0.5);
    series->setLabelsVisible();
    QPieSlice *budgetSlice = series->slices().at(0);
        budgetSlice->setLabel(QString("Budget: %1 DT").arg(budgetSum));
        budgetSlice->setLabelPosition(QPieSlice::LabelInsideNormal);

        QPieSlice *collectionSlice = series->slices().at(1);
        collectionSlice->setLabel(QString("Collection: %1 DT").arg(collectionSum));
        collectionSlice->setLabelPosition(QPieSlice::LabelInsideNormal);

    chart->addSeries(series);

    return chart;
}*/
QChart *ThemeWidget1::createPieChart() const
{
    QChart *chart = new QChart();
    chart->setTitle("BUDGET VS COLLECTS");

    qreal pieSize = 10.0;
    QPieSeries *series = new QPieSeries(chart);

    // Get the sum of amounts from the donations table
    QSqlQuery query("SELECT SUM(amount) FROM donations");
    query.next();
    double donationSum = query.value(0).toDouble();

    // Get the sum of collections from the Collects table
    QSqlQuery query2("SELECT SUM(collections) FROM Collects");
    query2.next();
    double collectionSum = query2.value(0).toDouble();

    // Add the sum of amounts and collections to the pie chart
    series->append("Donations", donationSum);
    series->append("Collections", collectionSum);

    // Set the properties of the pie chart
    series->setPieSize(pieSize);
    series->setHorizontalPosition(0.5);
    series->setVerticalPosition(0.5);
    series->setLabelsVisible();
    QPieSlice *donationSlice = series->slices().at(0);
    donationSlice->setLabel(QString("Donations: %1 DT").arg(donationSum));
    donationSlice->setLabelPosition(QPieSlice::LabelInsideNormal);

    QPieSlice *collectionSlice = series->slices().at(1);
    collectionSlice->setLabel(QString("Collections: %1 DT").arg(collectionSum));
    collectionSlice->setLabelPosition(QPieSlice::LabelInsideNormal);

    chart->addSeries(series);

    return chart;
}

void ThemeWidget1::updateUI()
{
    QChart::ChartTheme theme = static_cast<QChart::ChartTheme>(
                m_themeComboBox->itemData(m_themeComboBox->currentIndex()).toInt());

    const auto charts = m_charts;
    if (m_charts.at(0)->chart()->theme() != theme) {
        for (QChartView *chartView : charts)
            chartView->chart()->setTheme(theme);

        QPalette pal = window()->palette();
        if (theme == QChart::ChartThemeLight) {
            pal.setColor(QPalette::Window, QRgb(0xf0f0f0));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        } else if (theme == QChart::ChartThemeDark) {
            pal.setColor(QPalette::Window, QRgb(0x121218));
            pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
        } else if (theme == QChart::ChartThemeBlueCerulean) {
            pal.setColor(QPalette::Window, QRgb(0x40434a));
            pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
        } else if (theme == QChart::ChartThemeBrownSand) {
            pal.setColor(QPalette::Window, QRgb(0x9e8965));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        } else if (theme == QChart::ChartThemeBlueNcs) {
            pal.setColor(QPalette::Window, QRgb(0x018bba));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        } else if (theme == QChart::ChartThemeHighContrast) {
            pal.setColor(QPalette::Window, QRgb(0xffab03));
            pal.setColor(QPalette::WindowText, QRgb(0x181818));
        } else if (theme == QChart::ChartThemeBlueIcy) {
            pal.setColor(QPalette::Window, QRgb(0xcee7f0));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        } else {
            pal.setColor(QPalette::Window, QRgb(0xf0f0f0));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        }
        window()->setPalette(pal);
    }

    bool checked = m_antialiasCheckBox->isChecked();
    for (QChartView *chart : charts)
        chart->setRenderHint(QPainter::Antialiasing, checked);

    QChart::AnimationOptions options(
                m_animatedComboBox->itemData(m_animatedComboBox->currentIndex()).toInt());
    if (m_charts.at(0)->chart()->animationOptions() != options) {
        for (QChartView *chartView : charts)
            chartView->chart()->setAnimationOptions(options);
    }

    Qt::Alignment alignment(m_legendComboBox->itemData(m_legendComboBox->currentIndex()).toInt());

    if (!alignment) {
        for (QChartView *chartView : charts)
            chartView->chart()->legend()->hide();
    } else {
        for (QChartView *chartView : charts) {
            chartView->chart()->legend()->setAlignment(alignment);
            chartView->chart()->legend()->show();
        }
    }
}

