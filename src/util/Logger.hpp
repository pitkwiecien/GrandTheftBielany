#pragma once
#include <iostream>
#include <string>
#include <string_view>

// Minimalny logger. Header-only dla wygody.
// Użycie: Logger::info("Gracz awansował na poziom {}", level);
namespace Logger {

enum class Level { Info, Warn, Error };

inline void log(Level lvl, std::string_view msg) {
    const char* tag = "[INFO] ";
    std::ostream* out = &std::cout;
    switch (lvl) {
        case Level::Warn:  tag = "[WARN] ";  out = &std::cerr; break;
        case Level::Error: tag = "[ERROR] "; out = &std::cerr; break;
        case Level::Info:  default: break;
    }
    (*out) << tag << msg << '\n';
}

inline void info(std::string_view msg)  { log(Level::Info,  msg); }
inline void warn(std::string_view msg)  { log(Level::Warn,  msg); }
inline void error(std::string_view msg) { log(Level::Error, msg); }

} // namespace Logger
