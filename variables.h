#include <stdio.h>
#include <libusb-1.0/libusb.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>

char *test (void);

// typedefs

typedef void (*libusb_transfer_cb_fn)(struct libusb_transfer *transfer);

// enums

enum libusb_transfer_flags;
enum libusb_transfer_status;

// structs

struct libusb_control_setup;
struct libusb_iso_packet_descriptor;
struct libusb_transfer;

// global functions

int
libusb_alloc_streams(
    libusb_device_handle* dev_handle,
    uint32_t num_streams,
    unsigned char* endpoints,
    int num_endpoints
    );

int
libusb_free_streams(
    libusb_device_handle* dev_handle,
    unsigned char* endpoints,
    int num_endpoints
    );

unsigned char*
libusb_dev_mem_alloc(
    libusb_device_handle* dev_handle,
    size_t length
    );

int
libusb_dev_mem_free(
    libusb_device_handle* dev_handle,
    unsigned char* buffer,
    size_t length
    );

struct libusb_transfer*
libusb_alloc_transfer(int iso_packets);

void
libusb_free_transfer(struct libusb_transfer* transfer);

int
libusb_submit_transfer(struct libusb_transfer* transfer);

int
libusb_cancel_transfer(struct libusb_transfer* transfer);

void
libusb_transfer_set_stream_id(
    struct libusb_transfer* transfer,
    uint32_t stream_id
    );

uint32_t
libusb_transfer_get_stream_id(struct libusb_transfer* transfer);

static
unsigned char*
libusb_control_transfer_get_data(struct libusb_transfer* transfer);

static
struct libusb_control_setup*
libusb_control_transfer_get_setup(struct libusb_transfer* transfer);

static
void
libusb_fill_control_setup(
    unsigned char* buffer,
    uint8_t bmRequestType,
    uint8_t bRequest,
    uint16_t wValue,
    uint16_t wIndex,
    uint16_t wLength
    );

static
void
libusb_fill_control_transfer(
    struct libusb_transfer* transfer,
    libusb_device_handle* dev_handle,
    unsigned char* buffer,
    libusb_transfer_cb_fn callback,
    void* user_data,
    unsigned int timeout
    );

static
void
libusb_fill_bulk_transfer(
    struct libusb_transfer* transfer,
    libusb_device_handle* dev_handle,
    unsigned char endpoint,
    unsigned char* buffer,
    int length,
    libusb_transfer_cb_fn callback,
    void* user_data,
    unsigned int timeout
    );

static
void
libusb_fill_bulk_stream_transfer(
    struct libusb_transfer* transfer,
    libusb_device_handle* dev_handle,
    unsigned char endpoint,
    uint32_t stream_id,
    unsigned char* buffer,
    int length,
    libusb_transfer_cb_fn callback,
    void* user_data,
    unsigned int timeout
    );

static
void
libusb_fill_interrupt_transfer(
    struct libusb_transfer* transfer,
    libusb_device_handle* dev_handle,
    unsigned char endpoint,
    unsigned char* buffer,
    int length,
    libusb_transfer_cb_fn callback,
    void* user_data,
    unsigned int timeout
    );

static
void
libusb_fill_iso_transfer(
    struct libusb_transfer* transfer,
    libusb_device_handle* dev_handle,
    unsigned char endpoint,
    unsigned char* buffer,
    int length,
    int num_iso_packets,
    libusb_transfer_cb_fn callback,
    void* user_data,
    unsigned int timeout
    );

static
void
libusb_set_iso_packet_lengths(
    struct libusb_transfer* transfer,
    unsigned int length
    );

static
unsigned char*
libusb_get_iso_packet_buffer(
    struct libusb_transfer* transfer,
    unsigned int packet
    );

static
unsigned char*
libusb_get_iso_packet_buffer_simple(
    struct libusb_transfer* transfer,
    unsigned int packet
    );
