#ifndef GPIO_SYSFS_DRIVER_H_
#define GPIO_SYSFS_DRIVER_H_


#define BUF_SIZE    100

#define SYS_GPIO_PATH       "/sys/class/gpio"

#define HIGH_VALUE          1
#define LOW_VALUE           0

#define GPIO_DIR_OUT        HIGH_VALUE
#define GPIO_DIR_IN         LOW_VALUE

#define GPIO_LOW_VALUE      LOW_VALUE
#define GPIO_HIGH_VALUE     HIGH_VALUE

// Function prototypes
int gpio_export( uint32_t gpio_num );
int gpio_set_direction( uint32_t gpio_num, uint8_t dir_value );
int gpio_set_value( uint32_t gpio_num, uint8_t value );
int gpio_get_value( uint32_t gpio_num );
int gpio_set_trigger_edge( uint32_t gpio_num, char *edge );
int gpio_file_open( uint32_t gpio_num );
int gpio_file_close( int fd );

#endif

