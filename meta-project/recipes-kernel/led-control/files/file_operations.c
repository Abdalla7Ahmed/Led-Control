#include "file_operations.h"



#define BUFFER_SIZE    100
static unsigned char buffer[BUFFER_SIZE];
unsigned int buffer_pointer = 0;
#define SIZE_read    3


#define f_NUM_LEDS 5
int f_led_pins[f_NUM_LEDS] = {2, 3, 4, 17, 27};



int Driver_Open(struct inode *device_file, struct file *instance)
{
    printk("%s device_file open was called \n",__FUNCTION__);
    return 0;
}
int Driver_release(struct inode *device_file, struct file *instance)
{
    printk("%s device_file release was called \n",__FUNCTION__);
    return 0;
}
ssize_t Driver_Read (struct file *file, char __user *user_buffer, size_t count, loff_t *offset)
{
    int not_copied=0;
    char tmp[3] = "";
    printk("%s device_file read was called , count to read = %ld , offset = %lld \n",__FUNCTION__,count,*offset);
    if(count + (*offset) > SIZE_read)
    {
        count = SIZE_read - (*offset);
    }
    // tmp[0] = gpio_get_value(PIN_IN) + '0';
    // tmp[1] = '\n';
    not_copied = copy_to_user(user_buffer,&tmp[*offset],count);
    if(not_copied)
    {
        printk("the count of not copied bytes is %d \n",not_copied);
        printk("error during the copieing\n");
        return -1;
    }
    // if the count less than size the function called more than one time 
    // start from the end reading index
    *offset = count;

   
    return count;
}


ssize_t Driver_Write (struct file *file,const char __user *user_buffer, size_t count, loff_t *offset)
{
    int not_copied=0;
    int minor = iminor(file->f_inode); // Get the minor number
    printk("%s device_file read was called , count to write = %ld , offset = %lld \n",__FUNCTION__,count,*offset);
    if(count + (*offset) > BUFFER_SIZE)
    {
        count = BUFFER_SIZE - (*offset);
    }
    if(!count)
    {
        printk("no memory space left \n");
        return -1;
    }
    
    not_copied = copy_from_user(&buffer[*offset],user_buffer,count);
    if(not_copied)
    {
        printk("the count of not copied bytes is %d \n",not_copied);
        printk("error during the copieing\n");
        return -1;
    }
    switch(buffer[0])
    {
        case '1':
            gpio_set_value(f_led_pins[minor],1);
            break;
        case '0':
            gpio_set_value(f_led_pins[minor],0);
            break;
        default:
            printk("error value !!! \n");
            break;

    }
    *offset = count;
    printk("the count of not copied bytes is %d \n",not_copied);
    printk("the copied message is : %s \n",buffer);
    return count;
}
