#ifndef UIMAINWINDOWINITIALIZER_H
#define UIMAINWINDOWINITIALIZER_H
class CCImageMainWindow;
#include <QObject>

class UiMainWindowInitializer : public QObject {
    Q_OBJECT
public:
    explicit UiMainWindowInitializer(QObject* parent = nullptr);

    static void initUiMainWindowConnections(CCImageMainWindow* window);

private:
    static void _connect_toolBar(CCImageMainWindow* window);
    static void _connect_functional(CCImageMainWindow* window);
    static void _init_style(CCImageMainWindow* window);
    static void _init_keyAndMouseEvent(CCImageMainWindow* window);
    static void _init_keyEvent(CCImageMainWindow* window);
    static void _init_mouseEvent(CCImageMainWindow* window);
};

#endif  // UIMAINWINDOWINITIALIZER_H
