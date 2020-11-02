//
// Created by Hai Yaojing on 2020/10/28.
//

#ifndef MMKV_NATIVE_BRIDGE_H
#define MMKV_NATIVE_BRIDGE_H

#include "MMKVPredef.h"

#include "MMBuffer.h"
#include "MMKV.h"
#include "MMKVLog.h"
#include "MemoryFile.h"
#include <string>
#include <iostream>

using namespace std;
using namespace mmkv;

#ifdef MMKV_ANDROID
#define EXPORT_DLL_API __attribute__((visibility("default")))
#else
#define EXPORT_DLL_API __declspec(dllexport)
#endif


extern MMKV *defaultInstance();
extern MMKV *getInstance(const char *mapId);
extern "C" EXPORT_DLL_API void __init(const char * path, int logLevel);
extern "C" EXPORT_DLL_API void __encodeString(const char *mapId, const char *key, const char *value);
extern "C" EXPORT_DLL_API const char* __decodeString(const char *mapId, const char *key);
extern "C" EXPORT_DLL_API void __encodeBool(const char *mapId, const char *key, const bool value);
extern "C" EXPORT_DLL_API bool __decodeBool(const char *mapId, const char *key, const bool defaultValue);
extern "C" EXPORT_DLL_API void __encodeInt(const char *mapId, const char *key, const int32_t value);
extern "C" EXPORT_DLL_API int32_t __decodeInt(const char *mapId, const char *key, const int32_t defaultValue);
extern "C" EXPORT_DLL_API void __encodeLong(const char *mapId, const char *key, const int64_t value);
extern "C" EXPORT_DLL_API int64_t __decodeLong(const char *mapId, const char *key, const int64_t defaultValue);
extern "C" EXPORT_DLL_API void __encodeFloat(const char *mapId, const char *key, const float value);
extern "C" EXPORT_DLL_API float __decodeFloat(const char *mapId, const char *key, const float defaultValue);
extern "C" EXPORT_DLL_API void __encodeDouble(const char *mapId, const char *key, const double value);
extern "C" EXPORT_DLL_API double __decodeDouble(const char *mapId, const char *key, const double defaultValue);
extern "C" EXPORT_DLL_API size_t __totalSize(const char *mapId);
extern "C" EXPORT_DLL_API size_t __actualSize(const char *mapId);
extern "C" EXPORT_DLL_API void __removeValueForKey(const char *mapId, const char *key);
extern "C" EXPORT_DLL_API void __removeValuesForKeys(const char *mapId, const char **keys, const int size);
extern "C" EXPORT_DLL_API bool __containsKey(const char *mapId, const char *key);
extern "C" EXPORT_DLL_API const char* __getAllKey(const char *mapId);
extern "C" EXPORT_DLL_API void __sync(const char *mapId);
extern "C" EXPORT_DLL_API void __async(const char *mapId);
extern "C" EXPORT_DLL_API void __clearAll(const char *mapId);
extern "C" EXPORT_DLL_API void __close(const char *mapId);
extern "C" EXPORT_DLL_API void __freeNewMemory(char *pBuffer);

#endif //MMKV_NATIVE_BRIDGE_H
