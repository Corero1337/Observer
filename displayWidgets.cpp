#include "displayWidgets.h"

displayWidget::displayWidgetBase::displayWidgetBase(observer::Subject* geoDataSource, QWidget* pParent /*= nullptr*/)
  : QWidget(pParent)
  , observer(new observer::Observer([&](const QVariant& value)
    {m_data = value; update(); }, this))
{
  if (geoDataSource != nullptr)
    geoDataSource->registerObserver(observer);
};

displayWidget::pointTabWidget::pointTabWidget(observer::Subject* geoDataSource, QWidget* pParent /*= nullptr*/)
  : displayWidgetBase(geoDataSource, pParent)
{
}

void displayWidget::pointTabWidget::paintEvent(QPaintEvent* event)
{
  if (m_data.canConvert<QPoint>())
  {
    QPainter painter(this);
      painter.setPen(QPen(Qt::blue, 12));
    painter.drawPoint(m_data.toPoint());
  }
}

displayWidget::lineTabWidget::lineTabWidget(observer::Subject* geoDataSource, QWidget* pParent)
  : displayWidgetBase(geoDataSource, pParent)
{

}

void displayWidget::lineTabWidget::paintEvent(QPaintEvent* event)
{
  if (m_data.canConvert<QLine>())
  {
    QPainter painter(this);
    painter.setPen(QPen(Qt::green, 12));
    painter.drawLine(m_data.toLine());
  }
}

displayWidget::polygonTabWidget::polygonTabWidget(observer::Subject* geoDataSource, QWidget* pParent)
  : displayWidgetBase(geoDataSource, pParent)
{

}

void displayWidget::polygonTabWidget::paintEvent(QPaintEvent* event)
{
  if (m_data.canConvert<QPolygon>())
  {
    QPainter painter(this);
    painter.setPen(QPen(Qt::blue, 12));
    painter.drawPolygon(m_data.value<QPolygon>());
  }
}

displayWidget::linePointWidget::linePointWidget(observer::Subject* lineGeoDataSource, observer::Subject* pointGeoDataSource, QWidget* pParent)
  : lineTabWidget(lineGeoDataSource, pParent)
  , pointObserver(new observer::Observer([&](const QVariant& value)
    {pointData = value; update(); }, this))
{
  if(pointGeoDataSource != nullptr)
    pointGeoDataSource->registerObserver(pointObserver);
}

void displayWidget::linePointWidget::paintEvent(QPaintEvent* event)
{
  QPainter painter(this);
  painter.setPen(QPen(Qt::darkMagenta, 12));

  if (pointData.canConvert<QPoint>())
    painter.drawPoint(pointData.toPoint());

  if (m_data.canConvert<QLine>())
    painter.drawLine(m_data.toLine());
}
