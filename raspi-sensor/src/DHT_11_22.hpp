#ifndef _raspi_roomcontrol_DHT_11_22_hpp_
#define _raspi_roomcontrol_DHT_11_22_hpp_


#include <limits>
#include <iostream>
#ifndef _raspi_sensor_common_h_
#include "raspi_sensor_common.h"
#endif
#ifndef _raspi_roomcontrol_DataSet_hpp_
#include "DataSet.hpp"
#endif


namespace raspi_roomcontrol {


/**
 *  read temperature and humidity from DHT11 or DHT22 sensor
 */
class DHT_11_22 {


// ----------------------------------------------------------------------------
// inner classes
// ----------------------------------------------------------------------------

public:
    typedef sensor_data::Fixed<8> Number;
    struct SetupResult {
        bool      ok;

        operator bool() const {
            return ok;
        }

        void write(std::ostream & os) const {
            if (ok) {
                os << "succeed";;
            }
            else {
                os << "failed";
            }
        }
        friend std::ostream & operator << (
            std::ostream & os, const SetupResult & self
        ) {
            self.write(os);
            return os;
        }
    };


// ----------------------------------------------------------------------------
// init and destroy
// ----------------------------------------------------------------------------


    DHT_11_22();


protected:
    DHT_11_22(bool valid);
public:


    DHT_11_22(const DHT_11_22 & other) = delete;
    DHT_11_22 & operator = (const DHT_11_22 & other) = delete;


    DHT_11_22(DHT_11_22 && other);
    DHT_11_22 & operator = (DHT_11_22 && other);


    SetupResult setup();


// ----------------------------------------------------------------------------
// read only members
// ----------------------------------------------------------------------------


    operator bool() const { return m_initialized; }


    Number calcHumidity() const;


    Number calcTemperature() const;


// ----------------------------------------------------------------------------
// w+r only members
// ----------------------------------------------------------------------------


    void update();


// ----------------------------------------------------------------------------
// IO members
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// member vars
// ----------------------------------------------------------------------------
protected:
    bool m_initialized;
    bool m_valid;
    int  m_data[5];
};


}


#endif // _raspi_roomcontrol_DHT_11_22_hpp_
