#ifndef _sensor_data_UInt32_hpp_
#define _sensor_data_UInt32_hpp_


#include <iostream>
#include <chrono>
#ifndef _sensor_data_common_h_
#include "sensor_data_common.h"
#endif
#ifndef _sensor_data_UInt32_hpp_
#include "UInt32.hpp"
#endif


namespace sensor_data {


struct UInt32 {


    constexpr UInt32() : value(0) {}


    constexpr UInt32(uint32_t val) : value(val) {}


    constexpr operator uint32_t() const { return value; }


    constexpr size_t serialize(void * buffer, size_t size) const {
        if (size < 4) return 0;
        uint8_t * b = static_cast<uint8_t *>(buffer);
        *b   = (value      ) & 0xFFU;
        *++b = (value >>  8) & 0xFFU;
        *++b = (value >> 16) & 0xFFU;
        *++b = (value >> 24) & 0xFFU;
        return 4;
    }


    constexpr size_t deserialize(const void * buffer, size_t size)  {
        if (size < 4) return 0;
        const uint8_t * b = static_cast<const uint8_t *>(buffer);

        value  = (uint32_t)*b;
        value |= (uint32_t)(*++b) <<  8;
        value |= (uint32_t)(*++b) <<  16;
        value |= (uint32_t)(*++b) <<  24;
        return 4;
    }


    uint32_t value;
};


}


#endif // _sensor_data_UInt32_hpp_
