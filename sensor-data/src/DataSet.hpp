#ifndef _sensor_data_DataSet_hpp_
#define _sensor_data_DataSet_hpp_


#include <cmath>
#include <limits>
#include <iostream>
#ifndef _sensor_data_common_h_
#include "sensor_data_common.h"
#endif
#ifndef _sensor_data_Fixed_hpp_
#include "Fixed.hpp"
#endif
#ifndef _sensor_data_Time_hpp_
#include "Time.hpp"
#endif


namespace sensor_data {


template<int BITS>
struct DataSet {


    DataSet()
    : temperature((uint16_t)0)
    , humidity((uint16_t)0)
    { }


    DataSet(
        Fixed<BITS> a_temperature,
        Fixed<BITS> a_humidity
    )
    : temperature(a_temperature)
    , humidity(a_humidity)
    {
        time.set();
    }


    constexpr bool operator == (const DataSet & set) const {
        return time == set.time &&
            temperature == set.temperature &&
            humidity == set.humidity
        ;
    }


    constexpr size_t serialize(void * buffer, size_t size) const {
        size_t s;
        uint8_t * b = static_cast<uint8_t *>(buffer);
        s = time.serialize(b, size);
        if (0 == s) return 0;
        b += s;
        s = temperature.serialize(b, size);
        if (0 == s) return 0;
        b += s;
        s = humidity.serialize(b, size);
        if (0 == s) return 0;
        return b - static_cast<uint8_t *>(buffer);
    }
    constexpr size_t deserialize(const void * buffer, size_t size) {
        size_t s;
        const uint8_t * b = static_cast<const uint8_t *>(buffer);
        s = time.deserialize(b, size);
        if (0 == s) return 0;
        b += s;
        s = temperature.deserialize(b, size);
        if (0 == s) return 0;
        b += s;
        s = humidity.deserialize(b, size);
        if (0 == s) return 0;
        return b - static_cast<const uint8_t *>(buffer);
    }


    friend std::ostream & operator << (std::ostream & os, DataSet<BITS> self) {
        os << self.time << ": temperature = "
           << self.temperature.round(1) << ", humidity = "
           << self.humidity.round(1);
        return os;
    }


    Time        time;
    Fixed<BITS> temperature;
    Fixed<BITS> humidity;
};


}


#endif // _sensor_data_DataSet_hpp_
