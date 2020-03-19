/* Compile a sample ko module 
 *
 * Please compile this ko with the appropriate Linux share objects.
 * Ref. https://jerrynest.io/how-to-write-a-linux-kernel-module
 */

#include <linux/init.h>
#include <linux/module.h>

MODULE_DESCRIPTION("Hello_world");
MODULE_AUTHOR("logn-win");
MODULE_LICENSE("GPL");

static int hello_init(void)
{
 printk(KERN_INFO "Hello world !\n");
 return 0;
}

static void hello_exit(void)
{
 printk(KERN_INFO "Bye !\n");
}

module_init(hello_init);
module_exit(hello_exit);
