#ifndef _sensor_data_Time_hpp_
#define _sensor_data_Time_hpp_


#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <time.h>
#include <iostream>
#include <chrono>
#ifndef _librealtime_Tools_h_
#include <librealtime/Tools.h>
#endif
#ifndef _sensor_data_common_h_
#include "sensor_data_common.h"
#endif
#ifndef _sensor_data_UInt64_hpp_
#include "UInt64.hpp"
#endif


namespace sensor_data {


struct Time {


    Time() {}


    void set() {
        time = std::chrono::system_clock::now();
    }


    bool operator == (Time other) const { return sec() == other.sec(); }


    uint64_t sec() const {
        return std::chrono::duration_cast<std::chrono::seconds>(
            time.time_since_epoch()
        ).count();
    }


    constexpr size_t serialize(void * buffer, size_t size) const {
        uint64_t t64 = std::chrono::duration_cast<std::chrono::seconds>(
            time.time_since_epoch()
        ).count();
        UInt64 ui(t64);
        return ui.serialize(buffer, size);
    }
    constexpr size_t deserialize(const void * buffer, size_t size) {
        UInt64 ui;
        size_t s = ui.deserialize(buffer, size);
        if (0 == s) return 0;
        std::chrono::seconds sec(ui.value);
        time = std::chrono::time_point<std::chrono::system_clock>(sec);
        return s;
    }


    friend std::ostream & operator << (std::ostream & os, Time self) {
        std::time_t epoch_time = std::chrono::system_clock::to_time_t(self.time);
        char buf[30];
        struct tm tm0;
        memset(&tm0, 0, sizeof(tm0));
        const struct tm t = realtimeLocaltime(epoch_time);
        realtimeAsctime(&t, &buf[0], sizeof(buf));
        size_t len = strlen(&buf[0]);
        buf[len - 1] = 0;
        os << buf;
        return os;
    }


    std::chrono::time_point<std::chrono::system_clock> time;
};


}


#endif // _sensor_data_Time_hpp_
