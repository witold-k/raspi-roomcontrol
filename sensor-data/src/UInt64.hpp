#ifndef _sensor_data_UInt64_hpp_
#define _sensor_data_UInt64_hpp_


#include <iostream>
#include <chrono>
#ifndef _sensor_data_common_h_
#include "sensor_data_common.h"
#endif
#ifndef _sensor_data_UInt64_hpp_
#include "UInt64.hpp"
#endif


namespace sensor_data {


struct UInt64 {


    constexpr UInt64() : value(0) {}


    constexpr UInt64(uint64_t val) : value(val) {}


    constexpr operator uint64_t() const { return value; }


    constexpr size_t serialize(void * buffer, size_t size) const {
        if (size < 8) return 0;
        uint8_t * b = static_cast<uint8_t *>(buffer);
        *b   = (value      ) & 0xFFU;
        *++b = (value >>  8) & 0xFFU;
        *++b = (value >> 16) & 0xFFU;
        *++b = (value >> 24) & 0xFFU;
        *++b = (value >> 32) & 0xFFU;
        *++b = (value >> 40) & 0xFFU;
        *++b = (value >> 48) & 0xFFU;
        *++b = (value >> 56) & 0xFFU;
        return 8;
    }


    constexpr size_t deserialize(const void * buffer, size_t size)  {
        if (size < 8) return 0;
        const uint8_t * b = static_cast<const uint8_t *>(buffer);

        value  = (uint64_t)*b;
        value |= (uint64_t)(*++b) <<  8;
        value |= (uint64_t)(*++b) <<  16;
        value |= (uint64_t)(*++b) <<  24;
        value |= (uint64_t)(*++b) <<  32;
        value |= (uint64_t)(*++b) <<  40;
        value |= (uint64_t)(*++b) <<  48;
        value |= (uint64_t)(*++b) <<  56;
        return 8;
    }


    uint64_t value;
};


}


#endif // _sensor_data_UInt64_hpp_
