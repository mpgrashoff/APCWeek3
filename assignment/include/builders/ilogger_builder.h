//
// Created by dza02 on 9/6/2021.
//

#ifndef LESSON_ILOGGER_BUILDER_H
#define LESSON_ILOGGER_BUILDER_H

#include <string_view>
#include <memory>
#include "ilogger.h"
#include "itext_writer.h"

namespace builders {

    class ilogger_builder {
    public:

        enum class timestamp_type
        {
            none = -1,
            current_time= 0,
            running_time= 1
        };

        virtual ilogger_builder& reset() = 0;

        virtual ilogger_builder& with_console_output() = 0;
        virtual ilogger_builder& with_file_output(std::string_view file_name) = 0;
//        virtual ilogger_builder& with_runningtime_stamp() = 0;

        virtual std::unique_ptr<loggers::ilogger> get() = 0;

        //working here
        virtual ilogger_builder& with_writer(std::unique_ptr<io::itext_writer> writer) =0;
        virtual ilogger_builder& with_timestamp(timestamp_type type) = 0;


        virtual ~ilogger_builder() = default;



    };
}


#endif //LESSON_ILOGGER_BUILDER_H
