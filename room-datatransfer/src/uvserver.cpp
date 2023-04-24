#include <stdio.h>
#include <stdlib.h>
#include <uv.h>
#include <iostream>
#ifndef _raspi_roomcontrol_DHT_11_22_hpp_
#include "../../raspi-sensor/src/DHT_11_22.hpp"
#endif
#ifndef _room_datatransfer_Message_h_
#include "Message.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif


using namespace sensor_data;
using namespace raspi_roomcontrol;


uv_loop_t *loop;
uv_udp_t recv_socket;
uv_udp_t send_socket; // race condition here, only one connection allowed
uv_udp_send_t req2;   // race condition here, only one connection allowed


#define CHECK(r, msg)                                       \
    if (r < 0) {                                            \
        fprintf(stderr, "%s: %s\n", msg, uv_strerror(r));   \
        exit(1);                                            \
    }


static void on_allocate(
    uv_handle_t* handle,
    size_t size,
    uv_buf_t * buf
) {
    (void)handle;
    buf->base = (char *)malloc(size);
    buf->len = size;
}

#if 0
static void on_send(
    uv_udp_send_t* req,
    int status
) {
    (void)req;
    (void)status;
    std::cout << "[on_send]" << std::endl;
}
#endif

static void on_read(
    uv_udp_t *req,
    ssize_t nread,
    const uv_buf_t * buf,
    const struct sockaddr *addr,
    unsigned int flags
) {
    (void)flags;
    if (nread < 0) {
        // there seems to be no way to get an error code here (none of the udp tests do)
        fprintf(stderr, "recv error unexpected\n");
        uv_close((uv_handle_t*) req, NULL);
        free(buf->base);
        return;
    }
    struct sockaddr_in recv_addr = *(const struct sockaddr_in*)addr;
    char sender[17] = { 0 };
    uv_ip4_name(&recv_addr, sender, 16);
    sender[sizeof(sender) - 1] = 0;

    struct room_datatransfer_Message * msg = (struct room_datatransfer_Message *)buf->base;

    DHT_11_22::Number temp;
    DHT_11_22::Number hum;
    DataSet<8> ds(temp, hum);
    static_assert(sizeof(*msg) >= sizeof(ds) * 2);

//    size_t ss = ds.deserialize(msg->data, nread);
    std::cout << sender << ": " << ds
//              << " (" << ss << "/" << nread << ": " << sizeof(ds) << ")"
              << std::endl;
    free(buf->base);

    uv_udp_recv_stop(req);
}

#if 0
static void terminate() {
}
#endif

int room_datatransfer_uvserver_run(
    const char * addr,
    int          port
) {
    struct sockaddr_in recv_addr;
    int status;
    if (0 == addr) addr = "0.0.0.0";
    loop = uv_default_loop();
    status = uv_udp_init(loop, &recv_socket);
    CHECK(status, "init");
    uv_ip4_addr(addr, port, &recv_addr);
    uv_udp_bind(&recv_socket, (const struct sockaddr*)&recv_addr, 0);
    CHECK(status, "bind");

    for (;;) {
        status = uv_udp_recv_start(&recv_socket, on_allocate, on_read);
        CHECK(status, "recv");

        status = uv_run(loop, UV_RUN_DEFAULT);
        CHECK(status, "run");
    }

    uv_loop_close(loop);
    return 0;
}


#ifdef __cplusplus
}
#endif
