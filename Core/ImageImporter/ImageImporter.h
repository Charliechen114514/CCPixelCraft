#ifndef IMAGEIMPORTER_H
#define IMAGEIMPORTER_H
#include <QString>

namespace ImageImporter {

QStringList import_from_dirent(const QString& path, const QStringList& filters);

QStringList import_from_dirent_default(const QString& path);

QStringList import_from_dialog(const QString&     preset_path,
                               const QStringList& filters);

QStringList import_from_dialog_default(const QString& preset_path);

};  // namespace ImageImporter

#endif  // IMAGEIMPORTER_H
