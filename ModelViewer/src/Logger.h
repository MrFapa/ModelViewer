#pragma once
#include "spdlog/spdlog.h"

// todo add file logging functionality

// Fatal should always be printed
template<typename... Args>
static void LogFatal(const char* format, Args&&... args) {
    spdlog::critical(format, std::forward<Args>(args)...);
}


#ifdef MV_DEBUG
template<typename... Args>
static void LogInfo(const char* format, Args&&... args) {
    spdlog::info(format, std::forward<Args>(args)...);
}

template<typename... Args>
static void LogError(const char* format, Args&&... args) {
    spdlog::error(format, std::forward<Args>(args)...);
}

template<typename... Args>
static void LogWarning(const char* format, Args&&... args) {
    spdlog::warn(format, std::forward<Args>(args)...);
}

template<typename... Args>
static void LogDebug(const char* format, Args&&... args) {
    spdlog::debug(format, std::forward<Args>(args)...);
}

#else

static void LogInfo(const char* format, Args&&... args) {}
static void LogError(const char* format, Args&&... args) {}
static void LogWarning(const char* format, Args&&... args) {}
static void LogDebug(const char* format, Args&&... args) {}

#endif