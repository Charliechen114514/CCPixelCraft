#ifndef MOUSEMONITOR_H
#define MOUSEMONITOR_H
#include <QMap>
#include "ActionMonitor/eventhandlefunctor.h"
#include "predef.h"

class WindowMouseMonitor
{
public:
    WindowMouseMonitor() = default;
    DISABLE_COPY(WindowMouseMonitor);
    using ModifierType = int;
    static constexpr int CLEAR_MODIFIERS = 0;

    struct MonitoringError{
        enum class Error{
            NO_ERROR,
            RE_REGISTER
        } e{Error::NO_ERROR};
        QString errorString()
        {
            switch (e) {
            case Error::RE_REGISTER:
                return "重复注册";
                break;
            case Error::NO_ERROR:
                return "";
                break;
            }
            return "Unknown Error";
        }
    };

    enum class MouseWheelOperator{
        WHEEL_UP,
        WHEEL_DOWN
    };

    bool                registerEventsHandle(MouseWheelOperator op, MouseFunctor* f);
    bool                doProcess(MouseWheelOperator op);
    void                setModifiers(int modifiers){this->modifiers = modifiers;}
    ModifierType        getCurrentModifiersType() const {return modifiers;}
    void                clearModifiers(){modifiers = CLEAR_MODIFIERS;}

private:
    ModifierType        modifiers { CLEAR_MODIFIERS };
    MonitoringError     e;
    QMap<MouseWheelOperator,
        std::shared_ptr<MouseFunctor>>     mouseHandler;
};

#endif // MOUSEMONITOR_H
