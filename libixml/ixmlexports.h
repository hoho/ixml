/*
 * Summary: macros for marking symbols as exportable/importable.
 * Description: macros for marking symbols as exportable/importable.
 *
 * Copy: See Copyright for the status of this software.
 *
 * Author: Igor Zlatkovic <igor@zlatkovic.com>
 */

#ifndef __IXML_EXPORTS_H__
#define __IXML_EXPORTS_H__

/**
 * IXMLPUBFUN:
 * IXMLPUBFUN, IXMLPUBVAR, IXMLCALL
 *
 * Macros which declare an exportable function, an exportable variable and
 * the calling convention used for functions.
 *
 * Please use an extra block for every platform/compiler combination when
 * modifying this, rather than overlong #ifdef lines. This helps
 * readability as well as the fact that different compilers on the same
 * platform might need different definitions.
 */

/**
 * IXMLPUBFUN:
 *
 * Macros which declare an exportable function
 */
#define IXMLPUBFUN
/**
 * IXMLPUBVAR:
 *
 * Macros which declare an exportable variable
 */
#define IXMLPUBVAR extern
/**
 * IXMLCALL:
 *
 * Macros which declare the called convention for exported functions
 */
#define IXMLCALL

/** DOC_DISABLE */

/* Windows platform with MS compiler */
#if defined(_WIN32) && defined(_MSC_VER)
  #undef IXMLPUBFUN
  #undef IXMLPUBVAR
  #undef IXMLCALL
  #if defined(IN_LIBIXML) && !defined(LIBIXML_STATIC)
    #define IXMLPUBFUN __declspec(dllexport)
    #define IXMLPUBVAR __declspec(dllexport)
  #else
    #define IXMLPUBFUN
    #if !defined(LIBIXML_STATIC)
      #define IXMLPUBVAR __declspec(dllimport) extern
    #else
      #define IXMLPUBVAR extern
    #endif
  #endif
  #define IXMLCALL __cdecl
  #if !defined _REENTRANT
    #define _REENTRANT
  #endif
#endif

/* Windows platform with Borland compiler */
#if defined(_WIN32) && defined(__BORLANDC__)
  #undef IXMLPUBFUN
  #undef IXMLPUBVAR
  #undef IXMLCALL
  #if defined(IN_LIBIXML) && !defined(LIBIXML_STATIC)
    #define IXMLPUBFUN __declspec(dllexport)
    #define IXMLPUBVAR __declspec(dllexport) extern
  #else
    #define IXMLPUBFUN
    #if !defined(LIBIXML_STATIC)
      #define IXMLPUBVAR __declspec(dllimport) extern
    #else
      #define IXMLPUBVAR extern
    #endif
  #endif
  #define IXMLCALL __cdecl
  #if !defined _REENTRANT
    #define _REENTRANT
  #endif
#endif

/* Windows platform with GNU compiler (Mingw) */
#if defined(_WIN32) && defined(__MINGW32__)
  #undef IXMLPUBFUN
  #undef IXMLPUBVAR
  #undef IXMLCALL
/*
  #if defined(IN_LIBIXML) && !defined(LIBIXML_STATIC)
*/
  #if !defined(LIBIXML_STATIC)
    #define IXMLPUBFUN __declspec(dllexport)
    #define IXMLPUBVAR __declspec(dllexport) extern
  #else
    #define IXMLPUBFUN
    #if !defined(LIBIXML_STATIC)
      #define IXMLPUBVAR __declspec(dllimport) extern
    #else
      #define IXMLPUBVAR extern
    #endif
  #endif
  #define IXMLCALL __cdecl
  #if !defined _REENTRANT
    #define _REENTRANT
  #endif
#endif

/* Cygwin platform, GNU compiler */
#if defined(_WIN32) && defined(__CYGWIN__)
  #undef IXMLPUBFUN
  #undef IXMLPUBVAR
  #undef IXMLCALL
  #if defined(IN_LIBIXML) && !defined(LIBIXML_STATIC)
    #define IXMLPUBFUN __declspec(dllexport)
    #define IXMLPUBVAR __declspec(dllexport)
  #else
    #define IXMLPUBFUN
    #if !defined(LIBIXML_STATIC)
      #define IXMLPUBVAR __declspec(dllimport) extern
    #else
      #define IXMLPUBVAR
    #endif
  #endif
  #define IXMLCALL __cdecl
#endif

/* Compatibility */
#if !defined(LIBIXML_PUBLIC)
#define LIBIXML_PUBLIC IXMLPUBVAR
#endif

#endif /* __IXML_EXPORTS_H__ */
