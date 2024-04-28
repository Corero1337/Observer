#include <QApplication>
#include "QtTestProject.h"
#include "geoDataSource.h"

int main(int argc, char* argv[])
{
  std::vector< geoData::dataType> geoDatasourceTypes{ geoData::dataType::Point , 
    geoData::dataType::Line , geoData::dataType::Area };
  geoData::geoDataSource src(geoDatasourceTypes);

  QApplication a(argc, argv);
  QtTestProject w(src.getGeoDataSource(geoData::dataType::Point)
    , src.getGeoDataSource(geoData::dataType::Line)
    , src.getGeoDataSource(geoData::dataType::Area));

  QObject::connect(&w, &QtTestProject::newGeoData, &src, &geoData::geoDataSource::createGeoData);

  w.show();
  
  return a.exec();
}