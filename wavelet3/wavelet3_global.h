#ifndef WAVELET3_GLOBAL_H
#define WAVELET3_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(WAVELET3_LIBRARY)
#  define WAVELET3SHARED_EXPORT Q_DECL_EXPORT
#else
#  define WAVELET3SHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // WAVELET3_GLOBAL_H
