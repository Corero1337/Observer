#pragma once
#include <qobject.h>
#include <QVariant>

namespace observer
{
    using dataProcessStrategy = std::function<void(const QVariant&)>;

    class Observer : public QObject
    {
        Q_OBJECT

        public:

        Observer(dataProcessStrategy strategy, QObject* pParent = nullptr)
            : QObject(pParent)
            , notify(std::move(strategy))
        {};

        dataProcessStrategy notify;
    };
}
