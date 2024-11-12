#include "file_operations.h"

/* Meta information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Abdallah Ahmed Mohammed ");
MODULE_DESCRIPTION("test parameters");

#define MODULE_NAME "led_control_module"
#define MINOR_BASE 0
#define N_MINOR_DEVICES 5


#define CLASS_NAME "led_control_class"
#define DEVICE_NAME "led"


#define NUM_LEDS 5
int led_pins[NUM_LEDS] = {2, 3, 4, 17, 27};
const char *led_labels[NUM_LEDS] = {
    "gpio_pin2_label",
    "gpio_pin3_label",
    "gpio_pin4_label",
    "gpio_pin17_label",
    "gpio_pin27_label"
};

struct MyData{
    struct device *device_file[N_MINOR_DEVICES];
    dev_t device_number;
    struct class *device_class;
    struct cdev st_character_device;
    const struct file_operations fops;
}MyData_st = {
    .fops={
        .owner = THIS_MODULE,
        .open = Driver_Open,
        .release = Driver_release,
        .read = Driver_Read,
        .write = Driver_Write
    }
};


static int __init Module_init(void)
{
    int retval;
    int i;
    printk("hello Kernel this is the init module function \n");
    retval = alloc_chrdev_region(&MyData_st.device_number,MINOR_BASE,N_MINOR_DEVICES,MODULE_NAME);
    if (retval==0 )
    {
        printk("%s retval = %d , registered device major number = %d and minor number = %d \n",__FUNCTION__,retval,MAJOR(MyData_st.device_number),MINOR(MyData_st.device_number));
    }else
    {
        printk("cann't register device major number \n");
        return -1;
    }
    cdev_init(&MyData_st.st_character_device,&MyData_st.fops);
    retval = cdev_add(&MyData_st.st_character_device,MyData_st.device_number,N_MINOR_DEVICES);
    if (retval != 0)
    {
        printk("Registration of the devie failed \n");
       goto ERROR_ALLOCATE;
    }
    MyData_st.device_class = class_create(THIS_MODULE,CLASS_NAME);
    if(MyData_st.device_class == NULL)
    {
       printk("Creating device class failed\n");
       goto ERROR_CLASS_CREATE;
    }

     // Create device files for each minor device
    for (i = 0; i < N_MINOR_DEVICES; i++) {
        MyData_st.device_file[i] = device_create(MyData_st.device_class, NULL, MKDEV(MAJOR(MyData_st.device_number), MINOR_BASE + i), NULL, "%s%d", DEVICE_NAME, MINOR_BASE + i);
        if (IS_ERR(MyData_st.device_file[i])) {
            printk("Creating device file for minor %d failed\n", MINOR_BASE + i);
            retval = PTR_ERR(MyData_st.device_file[i]);
            goto ERROR_DEVICE_FILE_CREATE;
        }
    } 

    // Loop to request GPIO pins and set them as output
    for (i = 0; i < NUM_LEDS; i++) {
        // Request GPIO pin
        retval = gpio_request(led_pins[i], led_labels[i]);
        if (retval) {
            printk("Failed to request GPIO pin %d\n", led_pins[i]);
            goto ERROR_GPIO_REQUEST;
        }

        // Set GPIO pin as output
        retval = gpio_direction_output(led_pins[i], 0);
        if (retval) {
            printk("Failed to set GPIO direction for pin %d\n", led_pins[i]);
            goto ERROR_GPIO_SET_DIR;
        }
    }       
    return 0;


    ERROR_GPIO_SET_DIR:
    ERROR_GPIO_REQUEST:
    while (i > 0) {
        i--;
        gpio_free(led_pins[i]);
    }
    ERROR_DEVICE_FILE_CREATE:
        while (--i >= 0) {
        device_destroy(MyData_st.device_class, MKDEV(MAJOR(MyData_st.device_number), MINOR_BASE + i));
        }
    ERROR_CLASS_CREATE:
        cdev_del(&MyData_st.st_character_device);
    ERROR_ALLOCATE:
        unregister_chrdev_region(MyData_st.device_number,N_MINOR_DEVICES);
        return -1;

      
}

static void __exit Module_exit(void)
{
    int i;
    for (i = 0; i < NUM_LEDS; i++) {
        gpio_free(led_pins[i]);
    } 
    for (i = 0; i < N_MINOR_DEVICES; i++) {
        device_destroy(MyData_st.device_class, MKDEV(MAJOR(MyData_st.device_number), MINOR_BASE + i));
    }
    class_destroy(MyData_st.device_class);
    cdev_del(&MyData_st.st_character_device);
    unregister_chrdev_region(MyData_st.device_number,1);
    printk("Goodbye Kernel this is the exit module function \n");
}

module_init(Module_init);
module_exit(Module_exit);









