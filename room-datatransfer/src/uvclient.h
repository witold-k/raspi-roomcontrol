#ifndef _room_datatransfer_uvclient_h_
#define _room_datatransfer_uvclient_h_


#include <uv.h>
#ifndef _room_datatransfer_common_h_
#include "room_datatransfer_common.h"
#endif


#ifdef __cplusplus
extern "C" {
#endif


ROOM_DATATRANSFER_API int
room_datatransfer_uvclient_init(
    const char * addr,
    int          port
);


ROOM_DATATRANSFER_API int
room_datatransfer_uvclient_run();


#ifdef __cplusplus
}
#endif


#endif /* _room_datatransfer_uvclient_h_ */
