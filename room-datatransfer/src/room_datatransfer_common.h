#ifndef _room_datatransfer_common_h_
#define _room_datatransfer_common_h_


#if defined(_COMP_MSVC_) || defined(_COMP_MINGW_)
#ifndef ROOM_DATATRANSFER_API_IMPORT
#define ROOM_DATATRANSFER_API_IMPORT __declspec(dllimport)
#endif
#ifndef ROOM_DATATRANSFER_CLASS_API_IMPORT
#define ROOM_DATATRANSFER_CLASS_API_IMPORT ROOM_DATATRANSFER_API_IMPORT
#endif
#ifndef ROOM_DATATRANSFER_VAR_VAR_IMPORT
#define ROOM_DATATRANSFER_VAR_VAR_IMPORT ROOM_DATATRANSFER_API_IMPORT extern
#endif
#ifndef ROOM_DATATRANSFER_API_EXPORT
#define ROOM_DATATRANSFER_API_EXPORT __declspec(dllexport)
#endif
#ifndef ROOM_DATATRANSFER_CLASS_API_EXPORT
#define ROOM_DATATRANSFER_CLASS_API_EXPORT ROOM_DATATRANSFER_API_EXPORT
#endif
#ifndef ROOM_DATATRANSFER_VAR_API_EXPORT
#define ROOM_DATATRANSFER_VAR_API_EXPORT ROOM_DATATRANSFER_API_EXPORT extern
#endif
#ifndef ROOM_DATATRANSFER_API_PRIVATE
#define ROOM_DATATRANSFER_API_PRIVATE extern
#endif
#ifndef ROOM_DATATRANSFER_CLASS_API_PRIVATE
#define ROOM_DATATRANSFER_CLASS_API_PRIVATE
#endif
#endif


#if defined(_COMP_GCC_) || defined(_COMP_CLANG_)
#ifndef ROOM_DATATRANSFER_API_IMPORT
#define ROOM_DATATRANSFER_API_IMPORT __attribute__((visibility("default")))
#endif
#ifndef ROOM_DATATRANSFER_CLASS_API_IMPORT
#define ROOM_DATATRANSFER_CLASS_API_IMPORT ROOM_DATATRANSFER_API_IMPORT
#endif
#ifndef ROOM_DATATRANSFER_VAR_API_IMPORT
#define ROOM_DATATRANSFER_VAR_API_IMPORT ROOM_DATATRANSFER_API_IMPORT extern
#endif
#ifndef ROOM_DATATRANSFER_API_EXPORT
#define ROOM_DATATRANSFER_API_EXPORT __attribute__((visibility("default")))
#endif
#ifndef ROOM_DATATRANSFER_CLASS_API_EXPORT
#define ROOM_DATATRANSFER_CLASS_API_EXPORT ROOM_DATATRANSFER_API_EXPORT
#endif
#ifndef ROOM_DATATRANSFER_VAR_API_EXPORT
#define ROOM_DATATRANSFER_VAR_API_EXPORT ROOM_DATATRANSFER_API_EXPORT extern
#endif
#ifndef ROOM_DATATRANSFER_API_PRIVATE
#define ROOM_DATATRANSFER_API_PRIVATE extern
#endif
#ifndef ROOM_DATATRANSFER_CLASS_API_PRIVATE
#define ROOM_DATATRANSFER_CLASS_API_PRIVATE __attribute__((visibility("hidden")))
#endif
#ifndef ROOM_DATATRANSFER_VAR_API_PRIVATE
#define ROOM_DATATRANSFER_VAR_API_PRIVATE __attribute__((visibility("hidden")))
#endif
#endif


#ifndef ROOM_DATATRANSFER_API
#define ROOM_DATATRANSFER_API ROOM_DATATRANSFER_API_IMPORT
#endif
#ifndef ROOM_DATATRANSFER_CLASS_API
#define ROOM_DATATRANSFER_CLASS_API ROOM_DATATRANSFER_CLASS_API_IMPORT
#endif
#ifndef ROOM_DATATRANSFER_VAR_API
#define ROOM_DATATRANSFER_VAR_API ROOM_DATATRANSFER_VAR_API_IMPORT
#endif


#if !defined(snprintf) && defined(_MSC_VER) && (_MSC_VER < 1900)
#define snprintf _snprintf
#endif


#endif // _room_datatransfer_common_h_
