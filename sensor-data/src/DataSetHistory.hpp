#ifndef _sensor_data_DataSetHistory_hpp_
#define _sensor_data_DataSetHistory_hpp_


#include <iostream>
#include <vector>
#ifndef _sensor_data_common_h_
#include "sensor_data_common.h"
#endif
#ifndef _sensor_data_DataSet_hpp_
#include "DataSet.hpp"
#endif


namespace sensor_data {


class SENSOR_DATA_CLASS_API DataSetHistory
: public std::vector<DataSet<8>>
{
    enum {
        HISTORY_VERSION = 010000,
    };
public:
    typedef std::vector<DataSet<8>> SUPER;
// ----------------------------------------------------------------------------
// init and destroy
// ----------------------------------------------------------------------------


    DataSetHistory();
    DataSetHistory(const DataSetHistory & other) = delete;
    DataSetHistory(DataSetHistory && other);
    void operator = (const DataSetHistory & hist) = delete;
    void operator = (DataSetHistory && hist);


// ----------------------------------------------------------------------------
// read only members
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// w+r only members
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// IO only members
// ----------------------------------------------------------------------------


    size_t serialize(
        unsigned char * buffer_data,
        size_t          buffer_size
    ) const;
    size_t deserialize(
        const unsigned char * buffer_data,
        size_t                buffer_size
    );

    void write(std::ostream & os) const;


// ----------------------------------------------------------------------------
// member vars
// ----------------------------------------------------------------------------

};


}


#endif // _sensor_data_DataSetHistory_hpp_
