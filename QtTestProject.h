#pragma once

#include <QtWidgets/QMainWindow>
#include "./ui_QtTestProject.h"
#include "GeoDataEnums.h"

namespace observer
{
    class Subject;
}

class QtTestProject : public QMainWindow
{
    Q_OBJECT

public:
    QtTestProject(observer::Subject* pointDataSource, observer::Subject* lineDataSource,
      observer::Subject* polygonDataSource, QWidget *parent = nullptr);
    ~QtTestProject() = default;

    Q_SIGNAL void newGeoData(geoData::dataType geoDateType);

private:
    Ui::QtTestProjectClass ui;
};
