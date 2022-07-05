#ifndef LIBALIB_H
#define LIBALIB_H

#include "libalib_global.h"
#include <QString>
#include <QStringList>

class LIBALIB_EXPORT LibALib
{
public:
    LibALib();
    QStringList parseFileName(const QString & p_file_name);
    QStringList parseForScriptError(const QString & p_content_part);
    QStringList parseForScriptErrorParts(const QString & p_full_content);
};

#endif // LIBALIB_H