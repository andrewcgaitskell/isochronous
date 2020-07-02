#include <stdio.h>
#include <libusb-1.0/libusb.h>
#include <stdint.h>
#include <string.h>

void processMessage(const uint8_t*);


/*----------------------------------------------------------------------*/
int main(int argc, char*argv[])
{
  int res                      = 0;  /* return codes from libusb functions */
  libusb_device_handle* handle = 0;  /* handle for USB device */
  int kernelDriverDetached     = 0;  /* Set to 1 if kernel driver detached */
  int numBytes                 = 0;  /* Actual bytes transferred. */
  uint8_t buffer[64];                /* 64 byte transfer buffer */

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
  if (!handle)
  {
    fprintf(stderr, "Unable to open device.\n");
    return 1;
  }

  /* Check whether a kernel driver is attached to interface #0. If so, we'll 
   * need to detach it.
   */
  if (libusb_kernel_driver_active(handle, 1))
  {
    res = libusb_detach_kernel_driver(handle, 1);
    if (res == 0)
    {
      kernelDriverDetached = 1;
    }
    else
    {
      fprintf(stderr, "Error detaching kernel driver.\n");
      return 1;
    }
  }

  /* Claim interface #0. */
  /*res = libusb_claim_interface(handle, 0);*/
  res = libusb_claim_interface(handle,1);
  if (res != 0)
  {
    fprintf(stderr, "Error claiming interface.\n");
    return 1;
  }
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 
 
 Endpoint Descriptor:
        bLength                 9
        bDescriptorType         5
        bEndpointAddress     0x82  EP 2 IN
        bmAttributes            5
          Transfer Type            Isochronous
          Synch Type               Asynchronous
          Usage Type               Data
        wMaxPacketSize     0x00c8  1x 200 bytes
        bInterval               1
        bRefresh                0
        bSynchAddress           0  
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
  
 // int ps = libusb_get_max_iso_packet_size(libusb_device* handle,unsigned char 0x82);
  
  /*
  libusb_get_max_iso_packet_size(
    libusb_device* dev,
    unsigned char endpoint
    )  
  */
  
  printf(ps);

  /* Release interface #0. */
  res = libusb_release_interface(handle,1);
  if (0 != res)
  {
    fprintf(stderr, "Error releasing interface.\n");
  }

  /* If we detached a kernel driver from interface #0 earlier, we'll now 
   * need to attach it again.  */
  if (kernelDriverDetached)
  {
    libusb_attach_kernel_driver(handle, 1);
  }

  /* Shutdown libusb. */
  libusb_exit(0);

  return 0;
}
