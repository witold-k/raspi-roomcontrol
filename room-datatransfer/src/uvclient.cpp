#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <chrono>
#include <thread>
#include <iostream>


#ifndef _raspi_roomcontrol_DHT_11_22_hpp_
#include "../../raspi-sensor/src/DHT_11_22.hpp"
#endif
#ifndef _room_datatransfer_Message_h_
#include "Message.h"
#endif
#ifndef _room_datatransfer_uvclient_h_
#include "uvclient.h"
#endif


#define CHECK(r, msg)                                       \
    if (r < 0) {                                            \
        fprintf(stderr, "%s: %s\n", msg, uv_strerror(r));   \
    }


using namespace std::literals::chrono_literals;
using namespace sensor_data;
using namespace raspi_roomcontrol;


#ifdef __cplusplus
extern "C" {
#endif


static uv_loop_t * loop = 0;
static uv_udp_t send_socket;
static uv_udp_t recv_socket;
static DHT_11_22 sensor;
static int port = 12344;
static struct sockaddr_in send_addr;
static struct sockaddr_in recv_addr;
static const char * addrstr = 0;
static char portstr[6];
static uv_getaddrinfo_t addrreq;
static void send_msg();

#if 0
static void on_allocate(
    uv_handle_t* handle,
    size_t size,
    uv_buf_t * buf
) {
    (void)handle;
    buf->base = (char*)malloc(size);
    buf->len = size;
}
#endif

void on_resolved(uv_getaddrinfo_t *resolver, int status, struct addrinfo *res) {
    (void)resolver;
    int ret;
    if (EAI_AGAIN == status) {
        fprintf(stderr,
            "[uvclient] retry resolve name\n"
        );
        std::this_thread::sleep_for(100ms);
        uv_getaddrinfo(loop, &addrreq, on_resolved, addrstr, portstr, 0);
        return;
    }
    else if (status < 0) {
        fprintf(stderr,
                "[uvclient] getaddrinfo callback error %s\n",
                uv_err_name(status)
        );
        return;
    }

    //send_addr = *(struct sockaddr_in*)res->ai_addr;
    char addr[17] = {'\0'};
    uv_ip4_name((struct sockaddr_in*)res->ai_addr, addr, 16);
    uv_freeaddrinfo(res);
    printf("[uvclient] ip: %s:%d\n", addr, port);
    uv_ip4_addr(addr, port, &send_addr);
    uv_ip4_addr("0.0.0.0", port, &recv_addr);

    ret = uv_udp_init(loop, &send_socket);
    if (ret) {
        fprintf(stderr,
            "[uvclient] can not init: %d:%s\n",
            ret, uv_err_name(ret)
        );
        return;
    }

    ret = uv_udp_init(loop, &recv_socket);
    if (ret) {
        fprintf(stderr,
            "[uvclient] can not init: %d:%s\n",
            ret, uv_err_name(ret)
        );
        return;
    }
    ret = uv_udp_bind(&recv_socket, (const struct sockaddr*)&recv_addr, 0);
    if (ret) {
        fprintf(stderr,
            "[uvclient] can not init: %d:%s\n",
            ret, uv_err_name(ret)
        );
        return;
    }

    send_msg();
}

#if 0
static void on_read(
    uv_udp_t *req,
    ssize_t nread,
    const uv_buf_t * buf,
    const struct sockaddr *addr,
    unsigned int flags
) {
    if (nread < 0) {
        // there seems to be no way to get an error code here (none of the udp tests do)
        fprintf(stderr, "[uvclient] recv error unexpected\n");
        uv_close((uv_handle_t*) req, NULL);
        free(buf->base);
        return;
    }
    struct sockaddr_in recv_addr = *(struct sockaddr_in*)addr;
    char sender[17] = { 0 };
    uv_ip4_name(&recv_addr, sender, 16);
    sender[sizeof(sender) - 1] = 0;
    fprintf(stdout, "[uvclient] recv from %s:%d\n", sender, recv_addr.sin_port);
    free(buf->base);
    uv_udp_recv_stop(req);
}
#endif

static void on_send(
    uv_udp_send_t* req,
    int status
);

uv_udp_send_t req2;
static void send_msg() {
    struct room_datatransfer_Message * msg = (struct room_datatransfer_Message *)malloc(
        sizeof(struct room_datatransfer_Message)
    );
    memset(msg, 0, sizeof(*msg));
    DHT_11_22::Number temp;
    DHT_11_22::Number hum;

    sensor.update();
    temp = sensor.calcTemperature();
    hum  = sensor.calcHumidity();
    DataSet<8> ds(temp, hum);
    size_t ss = ds.serialize(msg->data, sizeof(msg->data));
    msg->size = msg->current = ss;
    std::cout << ds << std::endl;
    //DataSet<8> ds2;
    //ds2.deserialize(msg->data, sizeof(msg->data));
    //std::cout << ds2 << std::endl;

    uv_buf_t buf = uv_buf_init((char*)msg, sizeof(*msg));
    int ret = uv_udp_send(
        &req2,
        &send_socket,
        &buf,
        1,
        (struct sockaddr*)&send_addr,
        on_send
    );
    if (ret) {
        fprintf(stderr,
            "[uvclient] can not send: %d:%s\n",
            ret, uv_err_name(ret)
        );
    }
}


static void on_send(
    uv_udp_send_t* req,
    int status
) {
    (void)req;
    if (status < 0) {
        fprintf(stderr, "[uvclient] on_send error %s\n", uv_err_name(status));
        //    return;
    }

    std::this_thread::sleep_for(10s);
    send_msg();
}


//static void terminate() {
//}


int room_datatransfer_uvclient_init(
    const char * addr,
    int          port
) {
    int ret;
    if (0 == addr) addr = "127.0.0.1";
    DHT_11_22::SetupResult sres = sensor.setup();
    if (!sres) {
        std::cerr << sres << std::endl;
        return -1;
    }

    loop = uv_default_loop();

    addrstr = addr;
    snprintf(portstr, sizeof(portstr), "%d", port);
    ret = uv_getaddrinfo(loop, &addrreq, on_resolved, addr, portstr, 0);
    if (ret) {
        fprintf(stderr,
            "[uvclient] can not getaddrinfo: %d:%s\n",
            ret, uv_err_name(ret)
        );
        uv_loop_close(loop);
        loop = 0;
    }

    return ret;
}


int room_datatransfer_uvclient_run() {
    if (0 == loop) {
        std::cerr << "[CLIENT] not initialized" << std::endl;
        return -1;
    }

    //uv_udp_recv_start(&recv_socket, on_allocate, on_read);
    //int len = sizeof(struct sockaddr_in);
    //memset(&recv_addr, 0, sizeof(struct sockaddr_in));
    //int ok = uv_udp_getsockname(&recv_socket, (struct sockaddr *)&recv_addr, &len);
    //fprintf(stdout, "recv from port[%d:%d] %d\n", ok, len, (int)recv_addr.sin_port);

    int ret = uv_run(loop, UV_RUN_DEFAULT);
    if (ret) {
        fprintf(stderr,
            "[uvclient] can not run: %d:%s\n",
            ret, uv_err_name(ret)
        );
    }

    uv_loop_close(loop);
    loop = 0;
    return 0;
}


#ifdef __cplusplus
}
#endif
