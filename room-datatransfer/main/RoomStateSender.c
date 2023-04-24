#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "../src/uvclient.h"


int main(
    int argc,
    const char * argv[]
) {
    const char * addr = 0;
    if (argc >= 2) {
        addr = argv[1];
    }

    int ret = room_datatransfer_uvclient_init(addr, 12344);
    if (ret) {
        fprintf(stderr,
            "[uvclient] can not initalize: %d:%s\n",
            errno, strerror(errno)
        );
        return -1;
    }
    return room_datatransfer_uvclient_run();
}
