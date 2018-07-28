/*----------------------------------------------------------------------------|
|                                                                             |
|                               stick_driver.c                                |
|                                                                             |
|-----------------------------------------------------------------------------|
|
| Description  : Linux Kernel Driver Tutorial
|
|----------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------|
|                           System Includes                                   |
|-----------------------------------------------------------------------------|
| Most of Linux drivers' header files are located at:                         | 
| /usr/src/linux-headers-<your-linux-version>/include/                        |
|----------------------------------------------------------------------------*/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>

/*----------------------------------------------------------------------------|
|                           Module Defines                                    |
|----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------|
|                           Module Type Definitions                           |
|----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------|
|                           Module Function Prototypes                        |
|----------------------------------------------------------------------------*/

static int __init pen_init(void);

static void __exit pen_exit(void);

static int pen_probe(struct usb_interface *interface, const struct usb_device_id *id);

static void pen_disconnect(struct usb_interface *interface);

/*----------------------------------------------------------------------------|
|                           Module Global data                                |
|----------------------------------------------------------------------------*/

// usb_device_id
static struct usb_device_id pen_table[] =
{ /* Mutliple Device IDs can share the same USB driver */
  {USB_DEVICE(0x0bda, 0x0119)},  /* Real USB SD-card reader */
  {USB_DEVICE(0x1915, 0xaf11)},  /* Nordic Semiconductor USB dongle */
  {}  /* Terminating entry */
};
MODULE_DEVICE_TABLE(usb, pen_table);

/* IMPORTANT usb_driver struct for registering 
 * 1. Name of this USB driver
 * 2. USB VID/PID this driver is intended for.
 * 3. connect/disconnect callback handlers
 */
static struct usb_driver pen_driver =
{
   .name = "LeoChu-USB Stick-Driver",
   .id_table = pen_table,           /* link to USB device-id */
   .probe = pen_probe,              /* callback when connect USB */
   .disconnect = pen_disconnect     /* callback when disconnect USB */
};

/*----------------------------------------------------------------------------|
|                           Module Function Definitions                       |
|----------------------------------------------------------------------------*/
//Leo(TODO): I am still not quite sure what these will go as they look like MACRO expansion to me.

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Leo Chu");
MODULE_DESCRIPTION("USB Pen Registration Driver");

module_init(pen_init);
module_exit(pen_exit);


/*#-------------------------------------------------------------------------#*/
static int __init pen_init(void)
/** @brief Initialization routine executed when this kernel module is loaded
 *
 *  This function must register to Linux kernel via "module_init(pen_init)" call
 *
 *  @param[in,out] input argument
 *  @param[in,out] output argument
 *  @return void.
 */
{
   int ret = -1;

   printk(KERN_INFO "[*] LeoChu Constructor of Pen Driver");
   printk(KERN_INFO "\tRegistering Driverwith Kernel");
   ret = usb_register(&pen_driver);
   printk(KERN_INFO "\tRegistration completed");

   return ret;
}

/*#-------------------------------------------------------------------------#*/
static void __exit pen_exit(void)
/** @brief Termination routine executed when this kernel module is removed
 *
 *  This function must register to Linux kernel via "module_exit(pen_exit)" call
 *
 *  @param[in,out] input argument
 *  @param[in,out] output argument
 *  @return void.
 */
{
   printk(KERN_INFO "[*] LeoChu Destructor of driver");
   usb_deregister(&pen_driver);
   printk(KERN_INFO "\tDeregistration completed");
}

/*#-------------------------------------------------------------------------#*/
static int pen_probe(struct usb_interface *interface, const struct usb_device_id *id)
/** @brief One line description of the function
 *
 *  Detail description of the function
 *
 *  @param[in,out] input argument
 *  @param[in,out] output argument
 *  @return void.
 */
{
   printk(KERN_INFO "[*]  LeoChu Pen Drive (%04X:%04X) plugged\n", id->idVendor, id->idProduct);

   /* TODO: we shall check VID:PID before telling kernel that we can handle this USB device */
   return 0;   /* return 0 indicates we will manage this device */
}

/*#-------------------------------------------------------------------------#*/
static void pen_disconnect(struct usb_interface *interface)
/** @brief One line description of the function
 *
 *  Detail description of the function
 *
 *  @param[in,out] input argument
 *  @param[in,out] output argument
 *  @return void.
 */
{
   printk(KERN_INFO "[*] LeoChu Pen Drive unplugged\n");
}

/*#------------------------ End of stick_driver.c ---------------------------#*/
