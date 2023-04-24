#ifndef _sensor_data_common_h_
#define _sensor_data_common_h_


#if defined(_COMP_MSVC_) || defined(_COMP_MINGW_)
#ifndef SENSOR_DATA_API_IMPORT
#define SENSOR_DATA_API_IMPORT __declspec(dllimport)
#endif
#ifndef SENSOR_DATA_CLASS_API_IMPORT
#define SENSOR_DATA_CLASS_API_IMPORT SENSOR_DATA_API_IMPORT
#endif
#ifndef SENSOR_DATA_VAR_VAR_IMPORT
#define SENSOR_DATA_VAR_VAR_IMPORT SENSOR_DATA_API_IMPORT extern
#endif
#ifndef SENSOR_DATA_API_EXPORT
#define SENSOR_DATA_API_EXPORT __declspec(dllexport)
#endif
#ifndef SENSOR_DATA_CLASS_API_EXPORT
#define SENSOR_DATA_CLASS_API_EXPORT SENSOR_DATA_API_EXPORT
#endif
#ifndef SENSOR_DATA_VAR_API_EXPORT
#define SENSOR_DATA_VAR_API_EXPORT SENSOR_DATA_API_EXPORT extern
#endif
#ifndef SENSOR_DATA_API_PRIVATE
#define SENSOR_DATA_API_PRIVATE extern
#endif
#ifndef SENSOR_DATA_CLASS_API_PRIVATE
#define SENSOR_DATA_CLASS_API_PRIVATE
#endif
#endif


#if defined(_COMP_GCC_) || defined(_COMP_CLANG_)
#ifndef SENSOR_DATA_API_IMPORT
#define SENSOR_DATA_API_IMPORT __attribute__((visibility("default")))
#endif
#ifndef SENSOR_DATA_CLASS_API_IMPORT
#define SENSOR_DATA_CLASS_API_IMPORT SENSOR_DATA_API_IMPORT
#endif
#ifndef SENSOR_DATA_VAR_API_IMPORT
#define SENSOR_DATA_VAR_API_IMPORT SENSOR_DATA_API_IMPORT extern
#endif
#ifndef SENSOR_DATA_API_EXPORT
#define SENSOR_DATA_API_EXPORT __attribute__((visibility("default")))
#endif
#ifndef SENSOR_DATA_CLASS_API_EXPORT
#define SENSOR_DATA_CLASS_API_EXPORT SENSOR_DATA_API_EXPORT
#endif
#ifndef SENSOR_DATA_VAR_API_EXPORT
#define SENSOR_DATA_VAR_API_EXPORT SENSOR_DATA_API_EXPORT extern
#endif
#ifndef SENSOR_DATA_API_PRIVATE
#define SENSOR_DATA_API_PRIVATE extern
#endif
#ifndef SENSOR_DATA_CLASS_API_PRIVATE
#define SENSOR_DATA_CLASS_API_PRIVATE __attribute__((visibility("hidden")))
#endif
#ifndef SENSOR_DATA_VAR_API_PRIVATE
#define SENSOR_DATA_VAR_API_PRIVATE __attribute__((visibility("hidden")))
#endif
#endif


#ifndef SENSOR_DATA_API
#define SENSOR_DATA_API SENSOR_DATA_API_IMPORT
#endif
#ifndef SENSOR_DATA_CLASS_API
#define SENSOR_DATA_CLASS_API SENSOR_DATA_CLASS_API_IMPORT
#endif
#ifndef SENSOR_DATA_VAR_API
#define SENSOR_DATA_VAR_API SENSOR_DATA_VAR_API_IMPORT
#endif


#endif // _sensor_data_common_h_
