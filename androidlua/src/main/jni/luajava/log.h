//
// Created by leon on 16/3/10.
//

#ifndef LUA_LOG_H
#define LUA_LOG_H

#include <android/log.h>

#define LOG_LEVEL 10
#define  LOG_TAG "LUA-JNI"

#define LOGI(level, ...) if (level <= LOG_LEVEL) {__android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__);}
#define LOGE(level, ...) if (level <= LOG_LEVEL + 10) {__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__);}
#define LOGW(level, ...) if (level <= LOG_LEVEL + 5) {__android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__);}

#endif //LUA_LOG_H
