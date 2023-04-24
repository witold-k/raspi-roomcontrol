#ifndef _sensor_data_Fixed_hpp_
#define _sensor_data_Fixed_hpp_


#include <cmath>
#include <limits>
#include <iostream>
#ifndef _sensor_data_common_h_
#include "sensor_data_common.h"
#endif


namespace sensor_data {


struct SerializedFixed {
    uint8_t data[2];
};


static constexpr float       ROUND10_MUL[6] = {
    1.0f, 10.0f, 100.0f, 1000.0f, 10000.0f, 100000.0f
};
static constexpr float       ROUND10_DIF[6] = {
    1.0f, 1.0f / 10.0f, 1.0f / 100.0f, 1.0f / 1000.0f,
    1.0f / 10000.0f, 1.0f / 100000.0f
};


template <int BITS>
class Fixed {
public:
    static constexpr float       MUL  = (float)(1 << BITS);
    static constexpr float       INV  = 1.0f / (float)(1 << BITS);
    static constexpr uint16_t    MASK = (uint16_t)(((uint16_t)-1) << BITS);
    static constexpr uint16_t    INVALID_VALUE = static_cast<uint16_t>(0x8000U);
    static constexpr Fixed<BITS> INVALID = Fixed<BITS>(INVALID_VALUE);


    constexpr Fixed() : data(0) {}
    constexpr Fixed(uint16_t d) : data(d) {}
    constexpr Fixed(float f) { set(f); }


    constexpr Fixed(SerializedFixed f)
    : data(
        ((uint16_t)f.data[0] << 8) |
        ((uint16_t)f.data[1])
      )
    { }


    constexpr void operator = (uint16_t d) { data = d; }
    constexpr void operator = (float f) { set(f); }


    void operator = (SerializedFixed f) {
        data =
            ((uint16_t)f.data[0] << 8) |
            ((uint16_t)f.data[1])
        ;
    }


    operator float() const {
        return INVALID.data == data
            ? std::numeric_limits<float>::quiet_NaN()
            : static_cast<float>(data) * INV
        ;
    }
    constexpr float round(int index) const {
        if (INVALID.data == data) {
            return std::numeric_limits<float>::quiet_NaN();
        }
        else {
            return ::round(static_cast<float>(data) * INV * ROUND10_MUL[index]) * ROUND10_DIF[index];
        }
    }


    constexpr bool operator == (Fixed other) const { return data == other.data; }
    constexpr bool operator == (float f) const { return data == Fixed<BITS>(f); }
    constexpr void set(float f) { data = (uint16_t)(f * MUL); }


    bool forward(Fixed other) {
        if (INVALID_VALUE == data) {
            data = other.data;
            return true;
        }
        else {
            return false;
        }
    }


    constexpr SerializedFixed serialize() const {
        return (SerializedFixed) {
            static_cast<uint8_t>(data >> 8),
            static_cast<uint8_t>(data)
        };
    }
    constexpr size_t serialize(void * buffer, size_t size) const {
        if (size < 2) return 0;
        uint8_t * b = static_cast<uint8_t *>(buffer);
        b[0] = static_cast<uint8_t>(data >> 8);
        b[1] = static_cast<uint8_t>(data);
        return 2;
    }
    constexpr size_t deserialize(const void * buffer, size_t size) {
        if (size < 2) return 0;
        const uint8_t * b = static_cast<const uint8_t *>(buffer);
        data =
            ((uint16_t)b[0] << 8) |
            ((uint16_t)b[1]);
        return 2;
    }


    friend std::ostream & operator << (std::ostream & os, Fixed<BITS> self) {
        if (INVALID.data == self.data) {
            os << "INVALID";
        }
        else {
            os << (float)self;
        }
        return os;
    }


private:
    uint16_t data;
};


}


#endif // _sensor_data_Fixed_hpp_
