#pragma once
#include "observer.h"

namespace observer
{
    class Subject : public QObject
    {
        Q_OBJECT

        public:
            Subject(QObject* pParent = nullptr)
                : QObject(pParent) {};

            void registerObserver(Observer* observer)
            {
                connect(this, &Subject::newNotification, [observer](const QVariant& value)
                        {
                            if(observer != nullptr)
                                observer->notify(value);
                        });
            };

            void notifyObservers(const QVariant& value)
            {
                emit newNotification(value);
            };

        private:
            signals:
            void newNotification(const QVariant& value);
    };
}
