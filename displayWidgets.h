#pragma once
#include <QPainter>
#include <QWidget>
#include "subject.h"

namespace displayWidget
{
  class displayWidgetBase : public QWidget
  {
    Q_OBJECT

  public:
    displayWidgetBase(observer::Subject* geoDataSource, QWidget* pParent = nullptr);

  protected:
    QVariant m_data;

  private:
    observer::Observer* observer{ nullptr };
  };

  //*************************************************************************//

  class pointTabWidget : public displayWidgetBase
  {
  public:
    pointTabWidget(observer::Subject* geoDataSource, QWidget* pParent = nullptr);

  protected:
    void paintEvent(QPaintEvent* event) override;
  };

  //*************************************************************************//

  class lineTabWidget : public displayWidgetBase
  {
  public:
    lineTabWidget(observer::Subject* geoDataSource, QWidget* pParent = nullptr);

  protected:
    void paintEvent(QPaintEvent* event) override;
  };


  //*************************************************************************//

  class polygonTabWidget : public displayWidgetBase
  {
  public:
    polygonTabWidget(observer::Subject* geoDataSource, QWidget* pParent = nullptr);

  protected:
    void paintEvent(QPaintEvent* event) override;
  };

  //*************************************************************************//

  class linePointWidget : public lineTabWidget
  {
  public:
    linePointWidget(observer::Subject* lineGeoDataSource, observer::Subject* pointGeoDataSource, QWidget* pParent = nullptr);

  protected:
    void paintEvent(QPaintEvent* event) override;

  private:
    QVariant pointData;
    observer::Observer* pointObserver;
  };
}
