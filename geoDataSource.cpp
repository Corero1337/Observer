#include "geoDataSource.h"
#include <random>
#include <qpoint.h>
#include <qline.h>
#include <qpolygon.h>

const int x_max = 250;
const int y_max = 250;
const int x_min = 0;
const int y_min = 0;

// random number generator
std::random_device rd; // obtain a random number from hardware
std::mt19937 gen(rd()); // seed the generator

int getRandomPointInCoordinateSystem()
{
	std::uniform_int_distribution<> distrEvent(x_min, x_max);
	return distrEvent(gen);
}

geoData::geoDataSource::geoDataSource(const std::vector<dataType>& geoDataSourcesToProvide, QObject* pParent /* = nullptr */)
	: QObject(pParent)
{
	for (auto geoDataType : geoDataSourcesToProvide)
		addGeoDataSource(geoDataType);
}

geoData::geoDataSource::geoDataSource(QObject* pParent /*= nullptr*/)
  : QObject(pParent)
{}

void geoData::geoDataSource::addGeoDataSource(dataType geoDataType)
{
	if(!m_geoDataSubjects.contains(geoDataType))
        m_geoDataSubjects.insert(geoDataType, new observer::Subject(this));
}

void geoData::geoDataSource::deleteGeoDataSource(dataType geoDataType)
{
	if (m_geoDataSubjects.contains(geoDataType))
	{
		m_geoDataSubjects[geoDataType]->deleteLater();
		m_geoDataSubjects.remove(geoDataType);
	}
}

observer::Subject* geoData::geoDataSource::getGeoDataSource(dataType geoDataType) const
{
	return m_geoDataSubjects.contains(geoDataType) ? m_geoDataSubjects[geoDataType] : nullptr;
}

void geoData::geoDataSource::createGeoData(dataType geoDataType) const
{
	if (m_geoDataSubjects.contains(geoDataType))
	{
		QVariant value;
		switch (geoDataType)
		{
		case geoData::dataType::Point:
			value = QVariant(QPoint(getRandomPointInCoordinateSystem(), getRandomPointInCoordinateSystem()));
			break;
		case geoData::dataType::Line:
			value = QVariant(QLine(getRandomPointInCoordinateSystem(), getRandomPointInCoordinateSystem(),
				getRandomPointInCoordinateSystem(), getRandomPointInCoordinateSystem()));
			break;
		case geoData::dataType::Area:
		{
			QVector<QPoint> points;
			for (int i = 0; i < 10; i++)
				points.push_back(QPoint(getRandomPointInCoordinateSystem(), getRandomPointInCoordinateSystem()));
			value = QVariant(QPolygon(points));
			break;
		}
		default:
			break;
		}

		m_geoDataSubjects[geoDataType]->notifyObservers(value);
	}
}
