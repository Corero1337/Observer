#pragma once
#include <vector>
#include <qmap.h>
#include "subject.h"
#include "GeoDataEnums.h"

namespace geoData
{
	class geoDataSource : public QObject
	{
	public:
		geoDataSource(QObject* pParent = nullptr);
		geoDataSource(const std::vector<dataType>& geoDataSourcesToProvide, QObject* pParent = nullptr);
		void addGeoDataSource(dataType geoDataType);
		void deleteGeoDataSource(dataType geoDataType);
        observer::Subject* getGeoDataSource(dataType geoDataType) const;
		void createGeoData(dataType geoDataType) const;
	
	private:
        QMap<dataType ,observer::Subject*> m_geoDataSubjects;
	};
}

