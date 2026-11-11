#ifndef PANS_INCLUDE_PANS_EXPORT_H
#define PANS_INCLUDE_PANS_EXPORT_H
//跨平台动态符号导入导出
#if defined(_WIN32) && defined(PANS_SHARED_LIBRARY)
#if define(PANS_BUILDING_LIBRARY)
#define PANS_API __declspec(dllexport)
#else
#define PANS_API __declspec(dllimport)
#endif

#elif defined(__GNUC__) && defined(PANS_SHEARED_LIBERARY)
#define PANS_API __attribute__((visibility("default")))
#else
#define PANS_API
#endif








#endif