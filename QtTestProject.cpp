#include "QtTestProject.h"
#include "displayWidgets.h"

QtTestProject::QtTestProject(observer::Subject* pointDataSource, observer::Subject* lineDataSource,
  observer::Subject* polygonDataSource, QWidget *parent /* = nullptr */)
  : QMainWindow(parent)
{
  ui.setupUi(this);

  auto tabLayout = new QVBoxLayout(this);
  auto tabWidget = new displayWidget::pointTabWidget(pointDataSource, this);
  tabLayout->addWidget(tabWidget);
  ui.tabWidget->widget(0)->setLayout(tabLayout);
  
  tabLayout = new QVBoxLayout(this);
  auto tabWidgetLine = new displayWidget::lineTabWidget(lineDataSource ,this);
  tabLayout->addWidget(tabWidgetLine);
  ui.tabWidget->widget(1)->setLayout(tabLayout);

  tabLayout = new QVBoxLayout(this);
  auto tabWidgetPolygon = new displayWidget::polygonTabWidget(polygonDataSource ,this);
  tabLayout->addWidget(tabWidgetPolygon);
  ui.tabWidget->widget(2)->setLayout(tabLayout);
  
  auto tabLinePoint = new displayWidget::linePointWidget(lineDataSource, pointDataSource, this);
  ui.tabWidget->addTab(tabLinePoint, "LinePoint");


  connect(ui.btnCreatePoint, &QPushButton::clicked, this, 
    [&]() {emit newGeoData(geoData::dataType::Point); });;

  connect(ui.btnCreateLine, &QPushButton::clicked, this,
    [&]() {emit newGeoData(geoData::dataType::Line); });;

  connect(ui.btnCreatePolygon, &QPushButton::clicked, this,
    [&]() {emit newGeoData(geoData::dataType::Area); });;
}
