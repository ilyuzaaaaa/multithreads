//
// Created by Илюза Янгирова on 03.01.2021.
//
#include "Hash.hpp"

void SetUpLogging() {
    //Настройка логирования
    // Файловый логгер, в который записываются результаты с уровнями логгирования
    // trace и info
    auto TraceFileLogger = boost::log::add_file_log(
            boost::log::keywords::file_name =
                    "/Users/iluzaangirova/multithreads/logs/"
                    "TraceLog_%N.log",
            boost::log::keywords::rotation_size = 10 * 1024 * 1024,
            boost::log::keywords::format =
                    "[%TimeStamp%][%Severity%][%ThreadID%]: %Message%");
    // Файловый логгер, в который записываются результаты с уровнем логгирования
    // info
    auto InfoFileLogger = boost::log::add_file_log(
            boost::log::keywords::file_name =
                    "/Users/iluzaangirova/multithreads/logs/"
                    "InfoLog.log",
            boost::log::keywords::format =
                    "[%TimeStamp%][%Severity%][%ThreadID%]: %Message%");
    // Консольный логгер, в который записываются результаты с уровнем логгирования
    // info
    auto consoleLogger = boost::log::add_console_log(
            std::cout, boost::log::keywords::format =
                    "[%TimeStamp%][%Severity%][%ThreadID%]: %Message%");

    //Установка фильтрации
    TraceFileLogger->set_filter(boost::log::trivial::severity >=
                                boost::log::trivial::trace);
    InfoFileLogger->set_filter(boost::log::trivial::severity ==
                               boost::log::trivial::info);
    consoleLogger->set_filter(boost::log::trivial::severity ==
                              boost::log::trivial::info);
}
void JsonFiler::NewElement(const std::string& randString, const std::string& hash,
                   std::time_t timestamp) {
    std::scoped_lock<std::mutex> lock(mut);
    std::stringstream HexString;
    HexString << std::hex << std::uppercase << std::stoi(randString);
    json JsonObj;
    JsonObj["randString"] = HexString.str();
    JsonObj["hash"] = hash;
    JsonObj["timestamp"] = timestamp;
    JsonArray.push_back(JsonObj);
}
std::ostream& operator<<(std::ostream& out, const JsonFiler& j) {
    std::scoped_lock<std::mutex> lock(j.mut);
    out << j.JsonArray.dump(4);
    return out;
}
