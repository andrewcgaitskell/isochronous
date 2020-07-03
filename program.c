#include <stdio.h>
#include <libusb-1.0/libusb.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "variables.h"

//void processMessage(const uint8_t*);


/*----------------------------------------------------------------------*/
int main(int argc, char*argv[])
{
  int res                      = 0;  /* return codes from libusb functions */
  int i                      = 0;  /* counter */
  libusb_device_handle* handle = 0;  /* handle for USB device */
  int kernelDriverDetached     = 0;  /* Set to 1 if kernel driver detached */
  int numBytes                 = 0;  /* Actual bytes transferred. */
  int length = 0;
  uint8_t buffer[64];                /* 64 byte transfer buffer */
  char msgstr[100]                   = "";
  //struct libusb_transfer *transfer = NULL;
	
  /* Initialise libusb. */
  res = libusb_init(0);
  if (res != 0)
  {
    fprintf(stderr, "Error initialising libusb.\n");
    return 1;
  }

  /* Get the first device with the matching Vendor ID and Product ID. If
   * intending to allow multiple demo boards to be connected at once, you
   * will need to use libusb_get_device_list() instead. Refer to the libusb
   * documentation for details.
   * idVendor               : 0x0c76
   * idProduct              : 0x1529
   */
  handle = libusb_open_device_with_vid_pid(0, 0x0c76, 0x1529);
  
  //fprintf(handle);
  
  if (!handle)
  {
    fprintf(stderr, "Unable to open device.\n");
    return 1;
  }
  
  //transfer = libusb_alloc_transfer(200);
	
  struct libusb_transfer *transfer = libusb_alloc_transfer(200);
  
  libusb_transfer_cb_fn capture_callback;

  if (!transfer)
      strcpy(msgstr,"transfer alloc failure");
      printf("%s\n", msgstr);
	
  strcpy(msgstr,"setting transfer parameters");
  printf("%s\n", msgstr);
   
  transfer->dev_handle = handle;
  transfer->endpoint = 0x82;
  transfer->type = LIBUSB_TRANSFER_TYPE_ISOCHRONOUS;
  transfer->timeout = 5000;
  transfer->buffer = malloc(1024);
  transfer->length = 1024;
  transfer->callback = capture_callback;
  transfer->num_iso_packets = 200;
	
  strcpy(msgstr,"start filling transfer descriptors");
  printf("%s\n", msgstr);
   
  for (i = 0; i < 8; i++) {
      struct libusb_iso_packet_descriptor *desc =
            &transfer->iso_packet_desc[i];
        desc->length = 64;
    }
  
  strcpy(msgstr,"finished filling transfer descriptors");
  printf("%s\n", msgstr);
  
	
  /* Submission */

  res = libusb_submit_transfer(transfer);

  /* Handle Events */
  while (!completed)
  {
    rc = libusb_handle_events_completed(NULL, &completed);
    if (rc != LIBUSB_SUCCESS)
    {
      fprintf(stderr, "Transfer Error: %s\n", libusb_error_name(rc));
      break;
    }
  }	
  /* Completion handling */
  
  libusb_fill_iso_transfer(
    transfer , //struct libusb_transfer* transfer,
    handle, //libusb_device_handle* dev_handle,
    0x82, // unsigned char endpoint,
    buffer, // unsigned char* buffer,
    1024, //int length,
    200, //int num_iso_packets,
    capture_callback, // libusb_transfer_cb_fn callback,
    &transfer, // void* user_data,
    5000 // unsigned int timeout
    );	

  /*
  res = libusb_fill_iso_transfer(
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

   // Print the output of the buffer as Hexadecimal values:
    for (int i = 0; i < 1024; i++) {
        printf("%02x ", buffer[i] & 0xff);
        }
    printf("\n");

   /* Shutdown libusb. */
  libusb_exit(0);

  return 0;
}

/*
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
*/


//+++++++++++++++++++++++++++++++++++++++

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

/*
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
*/

////transfer = alloc_capture_transfer();

/* Submission */

////res = libusb_submit_transfer(transfer);

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

/*
static int benchmark_in(uint8_t ep)
{
	static uint8_t buf[2048];
	static struct libusb_transfer *xfr;
	int num_iso_pack = 0;

	if (ep == EP_ISO_IN)
		num_iso_pack = 16;

	xfr = libusb_alloc_transfer(num_iso_pack);
	if (!xfr)
		return -ENOMEM;

	if (ep == EP_ISO_IN) {
		libusb_fill_iso_transfer(xfr, devh, ep, buf,
				sizeof(buf), num_iso_pack, cb_xfr, NULL, 0);
		libusb_set_iso_packet_lengths(xfr, sizeof(buf)/num_iso_pack);
	} else
		libusb_fill_bulk_transfer(xfr, devh, ep, buf,
				sizeof(buf), cb_xfr, NULL, 0);

	gettimeofday(&tv_start, NULL);

	 NOTE: To reach maximum possible performance the program must
	 * submit *multiple* transfers here, not just one.
	 *
	 * When only one transfer is submitted there is a gap in the bus
	 * schedule from when the transfer completes until a new transfer
	 * is submitted by the callback. This causes some jitter for
	 * isochronous transfers and loss of throughput for bulk transfers.
	 *
	 * This is avoided by queueing multiple transfers in advance, so
	 * that the host controller is always kept busy, and will schedule
	 * more transfers on the bus while the callback is running for
	 * transfers which have completed on the bus.
	 

	return libusb_submit_transfer(xfr);
}
*/
 
/***

static int alloc_transfers(void)
{
	img_transfer = libusb_alloc_transfer(0);
	if (!img_transfer)
		return -ENOMEM;
	libusb_fill_bulk_transfer(img_transfer, devh, EP_DATA, imgbuf,
		sizeof(imgbuf), cb_img, NULL, 0);
	return 0;
}

***/


/* Deallocation */


/* function declaration
int max(int num1, int num2);
 
int main () {

   //local variable definition
   int a = 100;
   int b = 200;
   int ret;
 
   //calling a function to get max value
   ret = max(a, b);
 
   printf( "Max value is : %d\n", ret );
 
   return 0;
}
*/

// function returning the max between two numbers
/*
int max(int num1, int num2) {

   // local variable declaration
   int result;
 
   if (num1 > num2)
      result = num1;
   else
      result = num2;
 
   return result; 
}
*/
