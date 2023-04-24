#ifndef _raspi_roomcontrol_DHT_11_22_cpp_
#define _raspi_roomcontrol_DHT_11_22_cpp_


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#ifndef NO_SENSOR
#include <wiringPi.h>
#endif
#ifndef _raspi_roomcontrol_DHT_11_22_hpp_
#include "DHT_11_22.hpp"
#endif


#define MAX_TIMINGS 85
#define DHT_PIN     3   /* GPIO-22 */


using namespace sensor_data;

namespace raspi_roomcontrol {


DHT_11_22::DHT_11_22()
: m_initialized(false)
, m_valid(false)
{
}


DHT_11_22::DHT_11_22(bool valid)
: m_initialized(valid)
, m_valid(false)
{
}


DHT_11_22::DHT_11_22(DHT_11_22 && other)
: m_initialized(other.m_initialized)
, m_valid(other.m_valid)
{
    memcpy(this->m_data, other.m_data, sizeof(this->m_data));
    other.m_valid = false;
}


DHT_11_22 &
DHT_11_22::operator = (DHT_11_22 && other)
{
    this->m_initialized = other.m_initialized;
    this->m_valid = other.m_valid;
    memcpy(this->m_data, other.m_data, sizeof(this->m_data));
    other.m_valid = false;
    return *this;
}


DHT_11_22::SetupResult
DHT_11_22::setup() {
#ifndef NO_SENSOR
    if (wiringPiSetup() == -1) {
        m_initialized = false;
        return (SetupResult) { false };
    }
    else {
        m_initialized = true;
        return (SetupResult) { true };
    }
#else
    m_initialized = true;
    return (SetupResult) { true };
#endif
}


void
DHT_11_22::update() {
#ifndef NO_SENSOR
    if (!m_initialized) return;

    uint8_t laststate   = HIGH;
    uint8_t counter     = 0;
    uint8_t j           = 0, i;
    m_data[0] = m_data[1] = m_data[2] = m_data[3] = m_data[4] = 0;
    /* pull pin down for 18 milliseconds */
    pinMode(DHT_PIN, OUTPUT);
    digitalWrite(DHT_PIN, LOW);
    delay(18);
    /* prepare to read the pin */
    pinMode(DHT_PIN, INPUT);
    /* detect change and read data */
    for (i = 0; i < MAX_TIMINGS; ++i) {
        counter = 0;
        while (digitalRead(DHT_PIN) == laststate) {
            ++counter;
            delayMicroseconds(1);
            if (counter == 255) {
                break;
            }
        }
        laststate = digitalRead(DHT_PIN);
        if (counter == 255) break;
        /* ignore first 3 transitions */
        if ((i >= 4) && (i % 2 == 0)) {
            /* shove each bit into the storage bytes */
            m_data[j / 8] <<= 1;
            if (counter > 16) {
                m_data[j / 8] |= 1;
            }
            ++j;
        }
    }

    /*
     * check we read 40 bits (8bit x 5) + verify checksum in the last byte
     * print it out if data is good
     */
    if (
        (j >= 40) &&
        (m_data[4] == ((m_data[0] + m_data[1] + m_data[2] + m_data[3]) & 0xFF))
    ) {
        m_valid = true;
    }
    else {
        m_valid = false;
    }
#endif
}


DHT_11_22::Number
DHT_11_22::calcHumidity() const {
    if (!m_valid || !m_initialized) {
        return Number::INVALID;
    }
    else {
        float h = (float)((m_data[0] << 8) + m_data[1]) / 10;
        if (h > 100) {
            h = m_data[0];    // for DHT11
        }

        return Number(h);
    }
}


DHT_11_22::Number
DHT_11_22::calcTemperature() const {
    if (!m_valid || !m_initialized) {
        return Number::INVALID;
    }
    else {
        float c = (float)(((m_data[2] & 0x7F) << 8) + m_data[3]) / 10;
        if (c > 125) {
            c = m_data[2];    // for DHT11
        }
        if (m_data[2] & 0x80) {
            c = -c;
        }
        return Number(c);
    }
}


}


#endif // _raspi_roomcontrol_DHT_11_22_cpp_
