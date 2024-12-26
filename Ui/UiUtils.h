#ifndef UIUTILS_H
#define UIUTILS_H
class QString;
static constexpr const char* PNG_SUPPORT_SUFFIXS[] = {"png", "PNG",  "jpg",
                                                      "JPG", "jpeg", "JPEG"};

namespace UiUtils {

QString provide_default_selection_dirent();

}

#endif  // UIUTILS_H
