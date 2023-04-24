#ifndef _sensor_data_DataSetHistory_cpp_
#define _sensor_data_DataSetHistory_cpp_


#include <iostream>
#ifndef _sensor_data_UInt32_hpp_
#include "UInt32.hpp"
#endif
#ifndef _stockbase_DataSetHistory_hpp_
#include "DataSetHistory.hpp"
#endif


namespace sensor_data {


// ----------------------------------------------------------------------------
// static member vars
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// init and destroy
// ----------------------------------------------------------------------------


DataSetHistory::DataSetHistory()
{
}


DataSetHistory::DataSetHistory(DataSetHistory && other)
: SUPER(other)
{
}


void
DataSetHistory::operator = (DataSetHistory && other)
{
    if (this != &other) {
        SUPER::operator = (std::move(other));
    }
}


// ----------------------------------------------------------------------------
// read only members
// ----------------------------------------------------------------------------


void
DataSetHistory::write(std::ostream & os) const {
    for (const auto & e : *this) {
        os << e << "\n";
    }
}


// ----------------------------------------------------------------------------
// w+r only members
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// IO members
// ----------------------------------------------------------------------------


size_t
DataSetHistory::serialize(
    unsigned char * buffer_data,
    size_t          buffer_size
) const {
    unsigned char * pos = buffer_data;
    const unsigned char *const end = buffer_data + buffer_size;

    UInt32 ver = HISTORY_VERSION;
    UInt32 size = this->size();
    pos += ver.serialize(pos, end - pos);
    pos += size.serialize(pos, end - pos);

    for (const auto & e : *this) {
        pos += e.serialize(pos, end - pos);
    }

    return pos - buffer_data;
}


size_t
DataSetHistory::deserialize(
    const unsigned char * buffer_data,
    size_t                buffer_size
) {
    UInt32 ver;
    UInt32 size;
    const unsigned char * pos = buffer_data;
    const unsigned char *const end = buffer_data + buffer_size;

    pos += ver.deserialize(pos, end - pos);
    if (ver != HISTORY_VERSION) {
        fprintf(
            stderr,
            "wrong version number %x != %x:\n",
            ver.value,
            HISTORY_VERSION
        );
        return 0;
    }
    pos += size.deserialize(pos, end - pos);
    reserve(size);
    resize(size);
    for (auto & e : *this) {
        pos += e.deserialize(pos, end - pos);
    }

    return pos - buffer_data;
}


}


#endif // _sensor_data_DataSetHistory_cpp_
