#include <stdio.h>
#include <libusb-1.0/libusb.h>
#include <stdint.h>
#include <string.h>

#include "variables.h"

/* https://vovkos.github.io/doxyrest/samples/libusb/group_libusb_asyncio.html?highlight=isochronous */

/*
Asynchronous transfers
We can view asynchronous I/O as a 5 step process:

Allocation : allocate a libusb_transfer
Filling : populate the libusb_transfer instance with information about the transfer you wish to perform
Submission : ask libusb to submit the transfer
Completion handling : examine transfer results in the libusb_transfer structure
Deallocation : clean up resources
*/

/* Allocation */

/*struct libusb_transfer*
libusb_alloc_transfer(int iso_packets)*/

/* transfer = libusb_alloc_transfer(200); */

/* Filling */

static struct libusb_transfer *alloc_capture_transfer(void)
{
    struct libusb_transfer *transfer = libusb_alloc_transfer(200);
    int i;

    if (!transfer)
        die("transfer alloc failure");
   
    msg("setting transfer parameters");
   
    transfer->dev_handle = handle;
    transfer->endpoint = 0x82;
    transfer->type = LIBUSB_TRANSFER_TYPE_ISOCHRONOUS;
    transfer->timeout = 5000;
    transfer->buffer = malloc(1024);
    transfer->length = 1024;
    transfer->callback = capture_callback;
    transfer->num_iso_packets = 200;
   
    msg("filling transfer descriptors");
   
    for (i = 0; i < 8; i++) {
        struct libusb_iso_packet_descriptor *desc =
            &transfer->iso_packet_desc[i];
        desc->length = 64;
    }
   
    msg("returning transfer structure");
   
    return transfer;
}

transfer = alloc_capture_transfer;

/* Submission */

libusb_submit_transfer(transfer);

/* Completion handling */

/*
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
*/

/*
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
*/

//unsigned char data[4];
//int actual_length;
//int r = libusb_bulk_transfer(handle, LIBUSB_ENDPOINT_IN, data, sizeof(data), &actual_length, 0);
//if (r == 0 && actual_length == sizeof(data)) {
    // results of the transaction can now be found in the data buffer
    // parse them here and report button press
//} else {
//    error();
//}

/* Deallocation */


/* function declaration */
int max(int num1, int num2);
 
int main () {

   /* local variable definition */
   int a = 100;
   int b = 200;
   int ret;
 
   /* calling a function to get max value */
   ret = max(a, b);
 
   printf( "Max value is : %d\n", ret );
 
   return 0;
}
 
/* function returning the max between two numbers */
int max(int num1, int num2) {

   /* local variable declaration */
   int result;
 
   if (num1 > num2)
      result = num1;
   else
      result = num2;
 
   return result; 
}
