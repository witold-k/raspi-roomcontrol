#ifndef _room_datatransfer_Message_h_
#define _room_datatransfer_Message_h_


#include <stdint.h>


#ifndef _room_datatransfer_common_h_
#include "room_datatransfer_common.h"
#endif


#ifdef __cplusplus
extern "C" {
#endif


struct room_datatransfer_Message {
    uint8_t data[64]; // max size
    size_t  size;
    size_t  current;
};


int
room_datatransfer_Message_push(
    struct room_datatransfer_Message * self,
    const void * data,
    size_t       size
);


// ---------------------------------------------------------------------------


struct room_datatransfer_MessageBuffer {
    struct room_datatransfer_Message message[4];
    size_t current;
};


void
room_datatransfer_MessageBuffer_init(
    struct room_datatransfer_MessageBuffer * self
);


void
room_datatransfer_MessageBuffer_next(
    struct room_datatransfer_MessageBuffer * self
);


#ifdef __cplusplus
}
#endif


#endif /* _room_datatransfer_Message_h_ */
