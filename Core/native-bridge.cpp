
#include "native-bridge.h"

std::wstring String2WString(const std::string &s) {
    std::string strLocale = setlocale(LC_ALL, "");
    const char *chSrc = s.c_str();
    size_t nDestSize = mbstowcs(NULL, chSrc, 0) + 1;
    wchar_t *wchDest = new wchar_t[nDestSize];
    wmemset(wchDest, 0, nDestSize);
    mbstowcs(wchDest, chSrc, nDestSize);
    std::wstring wstrResult = wchDest;
    delete[] wchDest;
    setlocale(LC_ALL, strLocale.c_str());
    return wstrResult;
}

MMKV *defaultInstance() {
#ifdef MMKV_ANDROID
    return MMKV::defaultMMKV(MMKV_SINGLE_PROCESS);
#else
    return MMKV::defaultMMKV(MMKV_SINGLE_PROCESS);
#endif
}

MMKV *getInstance(const char *mapId) {
    if (mapId == nullptr || *mapId == '\0')
        return defaultInstance();
#ifdef MMKV_ANDROID
    return MMKV::mmkvWithID(mapId, mmkv::DEFAULT_MMAP_SIZE, MMKV_SINGLE_PROCESS);
#else
    return MMKV::mmkvWithID(mapId, MMKV_SINGLE_PROCESS);
#endif

}

void __init(const char * path, int logLevel) {
#ifdef MMKV_ANDROID
    MMKV::initializeMMKV(path, (MMKVLogLevel)logLevel);
#else
    std::wstring finalPath = String2WString(path);
    MMKV::initializeMMKV(finalPath, (MMKVLogLevel) logLevel);
#endif

}

void __encodeString(const char *mapId, const char *key, const char *value) {
    auto mmkv = getInstance(mapId);
    if (mmkv != nullptr) {
        mmkv->set(value, key);
    }
}

const char* __decodeString(const char *mapId, const char *key) {
    auto mmkv = getInstance(mapId);
    if (mmkv != nullptr) {
        string value;
        if (mmkv->getString(key, value)) {
            char* result = new char[value.size() + 1];
            strcpy(result, value.c_str());
            result[value.size()] = '\0';
            return result;
        }
    }
    return nullptr;
}

void __encodeBool(const char *mapId, const char *key, const bool value) {
    auto mmkv = getInstance(mapId);
    if (mmkv != nullptr) {
        mmkv->set(value, key);
    }
}

bool __decodeBool(const char *mapId, const char *key, const bool defaultValue) {
    auto mmkv = getInstance(mapId);
    bool value;
    if (mmkv != nullptr) {
        return mmkv->getBool(key, defaultValue);
    }
    return defaultValue;
}

void __encodeInt(const char *mapId, const char *key, const int32_t value) {
    auto mmkv = getInstance(mapId);
    if (mmkv != nullptr) {
        mmkv->set(value, key);
    }
}

int32_t __decodeInt(const char *mapId, const char *key, const int32_t defaultValue) {
    auto mmkv = getInstance(mapId);
    if (mmkv != nullptr) {
        return mmkv->getInt32(key, defaultValue);
    }
    return defaultValue;
}
void __encodeLong(const char *mapId, const char *key, const int64_t value) {
    auto mmkv = getInstance(mapId);
    if (mmkv != nullptr) {
        mmkv->set(value, key);
    }
}

int64_t __decodeLong(const char *mapId, const char *key, const int64_t defaultValue) {
    auto mmkv = getInstance(mapId);
    if (mmkv != nullptr) {
        return mmkv->getInt64(key, defaultValue);
    }
    return defaultValue;
}

void __encodeFloat(const char *mapId, const char *key, const float value) {
    auto mmkv = getInstance(mapId);
    if (mmkv != nullptr) {
        mmkv->set(value, key);
    }
}

float __decodeFloat(const char *mapId, const char *key, const float defaultValue) {
    auto mmkv = getInstance(mapId);
    if (mmkv != nullptr) {
        return mmkv->getFloat(key, defaultValue);
    }
    return defaultValue;
}

void __encodeDouble(const char *mapId, const char *key, const double value) {
    auto mmkv = getInstance(mapId);
    if (mmkv != nullptr) {
        mmkv->set(value, key);
    }
}

double __decodeDouble(const char *mapId, const char *key, const double defaultValue) {
    auto mmkv = getInstance(mapId);
    if (mmkv != nullptr) {
        return mmkv->getDouble(key, defaultValue);
    }
    return defaultValue;
}

size_t __totalSize(const char *mapId) {
    auto mmkv = getInstance(mapId);
    if (mmkv != nullptr) {
        return mmkv->totalSize();
    }
    return 0;
}

size_t __actualSize(const char *mapId) {
    auto mmkv = getInstance(mapId);
    if (mmkv != nullptr) {
        return mmkv->actualSize();
    }
    return 0;
}

void __removeValueForKey(const char *mapId, const char *key) {
    auto mmkv = getInstance(mapId);
    if (mmkv != nullptr) {
        mmkv->removeValueForKey(key);
    }
}

void __removeValuesForKeys(const char *mapId, const char **keys, const int size) {
    if (keys == nullptr)
        return;
    auto mmkv = getInstance(mapId);
    if (mmkv != nullptr) {
        vector<string> vec;
        for (int i = 0; i < size; i++) {
            vec.push_back(keys[i]);
        }

        mmkv->removeValuesForKeys(vec);
    }
}

bool __containsKey(const char *mapId, const char *key) {
    auto mmkv = getInstance(mapId);
    if (mmkv != nullptr) {
        return mmkv->containsKey(key);
    }
    return false;
}

const char* __getAllKey(const char *mapId) {
    auto mmkv = getInstance(mapId);
    if (mmkv != nullptr) {
        string value("");
        auto keys = mmkv->allKeys();
        for (auto it = keys.begin(); it != keys.end(); it++) {
            if (it != keys.begin()) {
                value.append(",");
            }
            value.append(*it);
        }
        char* result = new char[value.size() + 1];
        strcpy(result, value.c_str());
        result[value.size()] = '\0';
        return result;
    }
    return nullptr;
}

void __sync(const char *mapId) {
    auto mmkv = getInstance(mapId);
    if (mmkv != nullptr) {
        mmkv->sync(MMKV_SYNC);
    }
}

void __async(const char *mapId) {
    auto mmkv = getInstance(mapId);
    if (mmkv != nullptr) {
        mmkv->sync(MMKV_ASYNC);
    }
}

void __clearAll(const char *mapId) {
    auto mmkv = getInstance(mapId);
    if (mmkv != nullptr) {
        mmkv->clearAll();
    }
}

void __close(const char *mapId) {
    auto mmkv = getInstance(mapId);
    if (mmkv != nullptr) {
        mmkv->close();
    }
}

void __freeNewMemory(char *pBuffer) {
    if (nullptr != pBuffer) {
        delete pBuffer;
        pBuffer = nullptr;
    }
}

