#ifndef LIBALIB_GLOBAL_H
#define LIBALIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LIBALIB_LIBRARY)
#  define LIBALIB_EXPORT Q_DECL_EXPORT
#else
#  define LIBALIB_EXPORT Q_DECL_IMPORT
#endif

#endif // LIBALIB_GLOBAL_H
