#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>

/*---------------------------------------------------------------------------*/
/* MODULE PROTOTYPE */

static int pen_probe(struct usb_interface *interface, const struct usb_device_id *id);

static void pen_disconnect(struct usb_interface *interface);

/*---------------------------------------------------------------------------*/
/* MODULE VARIABLE */

// usb_device_id
static struct usb_device_id pen_table[] =
{ /* Mutliple Device IDs can share the same USB driver */
  {USB_DEVICE(0x0bda, 0x0119)},  /* Real USB SD-card reader */
  {USB_DEVICE(0x1915, 0xaf11)},  /* Nordic Semiconductor USB dongle */
  {}  /* Terminating entry */
};
MODULE_DEVICE_TABLE(usb, pen_table);


//Leo: This is the most important LINKER of all related info for registering/deregistering USB device
// usb_driver struct for holding USB driver information
static struct usb_driver pen_driver =
{
   .name = "LeoChu-USB Stick-Driver",
   .id_table = pen_table,           /* link to USB device-id */
   .probe = pen_probe,              /* callback when connect USB */
   .disconnect = pen_disconnect     /* callback when disconnect USB */
};




/*---------------------------------------------------------------------------*/
/* MODULE DEFINITION                                                         */

static int __init pen_init(void)
{
   int ret = -1;

   printk(KERN_INFO "[*] LeoChu Constructor of Pen Driver");
   printk(KERN_INFO "\tRegistering Driverwith Kernel");
   ret = usb_register(&pen_driver);
   printk(KERN_INFO "\tRegistration completed");

   return ret;
}


static void __exit pen_exit(void)
{
   printk(KERN_INFO "[*] LeoChu Destructor of driver");
   usb_deregister(&pen_driver);
   printk(KERN_INFO "\tDeregistration completed");
}

/* This function is only called when no other preceeding driver handle this device's insertion */
static int pen_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
   printk(KERN_INFO "[*]  LeoChu Pen Drive (%04X:%04X) plugged\n", id->idVendor, id->idProduct);

   /* TODO: we shall check VID:PID before telling kernel that we can handle this USB device */
   return 0;   /* return 0 indicates we will manage this device */
}

static void pen_disconnect(struct usb_interface *interface)
{
   printk(KERN_INFO "[*] LeoChu Pen Drive unplugged\n");
}

module_init(pen_init);
module_exit(pen_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Leo Chu");
MODULE_DESCRIPTION("USB Pen Registration Driver");

