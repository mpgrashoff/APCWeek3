//
// Created by dza02 on 9/6/2021.
//

#include "builders/logger_builder.h"
#include "logger.h"
#include "console_writer.h"
#include "decorators/decorator.h"
#include "decorators/runningtime_decorator.h"
#include "decorators/timestamp_decorator.h"
#include <memory>

builders::logger_builder::logger_builder():
    m_writer{nullptr}, m_logger{nullptr}
{
    reset();
}

builders::ilogger_builder& builders::logger_builder::reset() {

    auto multi_writer = std::make_unique<writers::multi_writer>();
    m_writer = multi_writer.get();

    m_logger = std::make_unique<lib::logger>( std::move(multi_writer) );
    return *this;
}

builders::ilogger_builder& builders::logger_builder::with_console_output() {
    if (m_writer){
        m_writer->add_writer("console", std::make_unique<writers::console_writer>() );
    }
    return *this;
}

builders::ilogger_builder& builders::logger_builder::with_file_output(std::string_view file_name) {
    if (m_writer){
        m_writer->add_writer(std::string{file_name}, std::make_unique<writers::stream_writer>(file_name.data()) );
    }
    return *this;
}

//builders::ilogger_builder& builders::logger_builder::with_runningtime_stamp() {
//    if (m_logger) {
//        m_logger = std::make_unique<lib::decorators::runningtime_decorator>(std::move(m_logger));
//    }
//    return *this;
//}

std::unique_ptr<loggers::ilogger> builders::logger_builder::get() {
    m_writer = nullptr;
    return std::move(m_logger);
}

builders::ilogger_builder& builders::logger_builder::with_writer(std::unique_ptr<io::itext_writer> writer)
{
    m_writer->add_writer(std::to_string(rand()),std::move(writer));
    return *this;
}

builders::ilogger_builder& builders::logger_builder::with_timestamp(timestamp_type type)
{
    if (timestamped == true){std::cout << "this logger has likely been decorated already not able to decorate again. second call has been ignored\n"; }
     switch (type) {
        case timestamp_type::none:
            std::cout << "no timestamping was defined in with_timestamp()\n";
            break;
        case timestamp_type::running_time:
            if (m_logger) {
                m_logger = std::make_unique<lib::decorators::runningtime_decorator>(std::move(m_logger));
            }
            timestamped = true;
            break;
        case timestamp_type::current_time:
            if (m_logger){
                m_logger = std::make_unique<lib::decorators::timestamp_decorator>(std::move(m_logger));
            }
            timestamped = true;
            break;
    }
    return *this;
}

builders::logger_builder builders::default_builder() {
    return  {};
}
