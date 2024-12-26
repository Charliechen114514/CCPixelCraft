#include "ImageImporter.h"
#include "UiUtils.h"
#include <QDir>
#include <QFileDialog>

QStringList ImageImporter::import_from_dirent(const QString&     path,
                                              const QStringList& filters) {
    QDir fetching_dir(path);
    fetching_dir.setNameFilters(filters);
    return fetching_dir.entryList();
}

QStringList ImageImporter::import_from_dialog(const QString&     preset_path,
                                              const QStringList& filters) {
    return QFileDialog::getOpenFileNames(nullptr, "请选择图像文件（可复选）",
                                         preset_path, filters.join(";;"));
}

QStringList ImageImporter::import_from_dialog_default(
    const QString& preset_path) {
    QStringList default_filters;
    for (const auto& each : PNG_SUPPORT_SUFFIXS) {
        default_filters.append("*." + QString(each));
    }
    return QFileDialog::getOpenFileNames(nullptr, "请选择图像文件", preset_path,
                                         default_filters.join(";;"));
}

QStringList ImageImporter::import_from_dirent_default(const QString& path) {
    QDir        fetching_dir(path);
    QStringList default_filters;
    for (const auto& each : PNG_SUPPORT_SUFFIXS) {
        default_filters.append("*." + QString(each));
    }
    fetching_dir.setNameFilters(default_filters);
    return fetching_dir.entryList();
}
