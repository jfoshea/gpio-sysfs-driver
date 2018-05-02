#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "gpio_sysfs_driver.h"

//=============================================================================
//
// @brief   GPIO Export 
// @param   gpio_num : GPIO port 
// @retval  0 for SUCCESS, < 0 for ERROR
//
//=============================================================================
int gpio_export( uint32_t gpio_num )
{
    int fd, len;
	char buf[ BUF_SIZE ];

	fd = open( SYS_GPIO_PATH "/export", O_WRONLY );
	if (fd < 0) 
    {
        perror( "File open error\n" );
		return fd;
	}

	len = snprintf( buf, sizeof( buf ), "%d", gpio_num );

	write( fd, buf, len );

	close( fd );

	return 0;
}

//=============================================================================
//
// @brief   GPIO Set Direction
// @param   gpio_num : GPIO port 
// @param   dir_value : 1 means 'out' , 0 means "in"
// @retval  0 for SUCCESS, < 0 for ERROR
//
//=============================================================================
int gpio_set_direction( uint32_t gpio_num, uint8_t dir_value )
{
    int fd;
    char buf[ BUF_SIZE ];

    snprintf( buf, sizeof( buf ), SYS_GPIO_PATH "/gpio%d/direction", gpio_num );

    fd = open( buf, O_WRONLY );
    if( fd < 0 ) 
    {
        perror( "File open error\n" );
        return fd;
    }

    if( dir_value )
        write( fd, "out", 4 );
    else
        write( fd, "in", 3 );

    close( fd );

    return 0;
}

//=============================================================================
//
// @brief   GPIO Set Value 
// @param   gpio_num : GPIO port 
// @param   out_value : 1 or 0
// @retval  0 for SUCCESS, < 0 for ERROR
//
//=============================================================================
int gpio_set_value( uint32_t gpio_num, uint8_t value )
{
    int fd;
    char buf[ BUF_SIZE ];

    snprintf( buf, sizeof( buf ), SYS_GPIO_PATH "/gpio%d/value", gpio_num );

    fd = open( buf, O_WRONLY );
    if( fd < 0 ) 
    {
        perror( "File open error\n" );
        return fd;
    }

    if( value )
        write( fd, "1", 2 );
    else
        write( fd, "0", 2 );

    close( fd );

    return 0;
}

//=============================================================================
//
// @brief   GPIO Get Value 
// @param   gpio_num : GPIO port 
// @retval  0 for SUCCESS, < 0 for ERROR
//
//=============================================================================
int gpio_get_value( uint32_t gpio_num )
{
    int fd;
    uint8_t value = 0;
    char buf[ BUF_SIZE ];

    snprintf( buf, sizeof( buf ), SYS_GPIO_PATH "/gpio%d/value", gpio_num );

    fd = open( buf, O_WRONLY );
    if( fd < 0 ) 
    {
        perror( "File open error\n" );
        return fd;
    }

    read( fd, &value, 1 );

    close( fd );

    return value;
}

//=============================================================================
//
// @brief   GPIO Set Trigger Edge
// @param   gpio_num : GPIO port 
// @param   edge : rising or falling edge 
// @retval  0 for SUCCESS, < 0 for ERROR
//
//=============================================================================
int gpio_set_trigger_edge( uint32_t gpio_num, char *edge )
{
    int fd;
    char buf[ BUF_SIZE ];

    snprintf( buf, sizeof( buf ), SYS_GPIO_PATH "/gpio%d/edge", gpio_num );

    fd = open( buf, O_WRONLY );
    if (fd < 0) 
    {
        perror( "File open error\n" );
        return fd;
    }

    write( fd, edge, strlen( edge ) + 1 );

    close( fd );

    return 0;
}

//=============================================================================
//
// @brief   GPIO Open sysfs for gpio port 
// @param   gpio_num : GPIO port 
// @retval  0 for SUCCESS, < 0 for ERROR
//
//=============================================================================
int gpio_file_open( uint32_t gpio_num )
{
    int fd;
    char buf[ BUF_SIZE ];

    snprintf( buf, sizeof( buf ), SYS_GPIO_PATH "/gpio%d/value", gpio_num );

    fd = open( buf, O_RDONLY | O_NONBLOCK );
    if( fd < 0 ) 
    {
        perror( "File open error\n" );
    }

    return fd;
}

//=============================================================================
//
// @brief   GPIO Open sysfs for gpio port 
// @param   fd : GPIO sysfs file descriptor 
// @retval  0 for SUCCESS, < 0 for ERROR
//
//=============================================================================
int gpio_file_close( int fd )
{
    return close( fd );
}
