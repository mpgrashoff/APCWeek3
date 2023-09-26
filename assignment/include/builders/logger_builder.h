//
// Created by dza02 on 9/6/2021.
//

#ifndef LESSON_LOGGER_BUILDER_H
#define LESSON_LOGGER_BUILDER_H

#include <string_view>
#include <memory>
#include "ilogger_builder.h"
#include "multi_writer.h"

namespace builders {

    class logger_builder: public ilogger_builder {
    public:
        logger_builder();

        virtual ilogger_builder& reset() override;
        virtual ilogger_builder& with_console_output() override;
        virtual ilogger_builder& with_file_output(std::string_view file_name) override;
//        virtual ilogger_builder& with_runningtime_stamp() override;
        virtual std::unique_ptr <loggers::ilogger> get() override;
        //working here
        virtual ilogger_builder& with_writer(std::unique_ptr<io::itext_writer> writer) override;
        virtual ilogger_builder & with_timestamp(timestamp_type type) override;


        virtual ~logger_builder() override = default;

    private:
        writers::multi_writer* m_writer;
        std::unique_ptr<loggers::ilogger> m_logger;
        bool timestamped = false;
    };

    logger_builder default_builder();

}

#endif //LESSON_LOGGER_BUILDER_H
