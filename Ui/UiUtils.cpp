#include "UiUtils.h"
#include <QStandardPaths>
#include <QString>

namespace UiUtils {

QString provide_default_selection_dirent() {
    return QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
}

}  // namespace UiUtils
