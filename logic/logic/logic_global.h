#ifndef LOGIC_GLOBAL_H
#define LOGIC_GLOBAL_H

#if defined(_MSC_VER) || defined(WIN64) || defined(_WIN64) || defined(__WIN64__) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#  define Q_DECL_EXPORT __declspec(dllexport)
#  define Q_DECL_IMPORT __declspec(dllimport)
#else
#  define Q_DECL_EXPORT     __attribute__((visibility("default")))
#  define Q_DECL_IMPORT     __attribute__((visibility("default")))
#endif

#if defined(LOGIC_LIBRARY)
#  define LOGIC_EXPORT Q_DECL_EXPORT
#else
#  define LOGIC_EXPORT Q_DECL_IMPORT
#endif

#endif // LOGIC_GLOBAL_H
