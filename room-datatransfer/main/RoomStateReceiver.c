#include "../src/uvserver.h"


int main(
    int argc,
    const char * argv[]
) {
    const char * addr = 0;
    if (argc >= 2) {
        addr = argv[1];
    }

    return room_datatransfer_uvserver_run(addr, 12344);
}
