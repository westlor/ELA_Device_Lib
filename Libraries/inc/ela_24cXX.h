/*
 * ela_24cXX.h
 *
 *  Created on: 2016Äê3ÔÂ21ÈÕ
 *      Author: Westlor
 */

#ifndef LIBRARIES_INC_ELA_24CXX_H_
#define LIBRARIES_INC_ELA_24CXX_H_

#include <linux/i2c-dev.h>
#include <linux/i2c.h>

#define EEPROM_TYPE_UNKNOWN	0
#define EEPROM_TYPE_8BIT_ADDR	1
#define EEPROM_TYPE_16BIT_ADDR 	2

struct eeprom
{
	char *dev; 	// device file i.e. /dev/i2c-N
	int addr;	// i2c address
	int fd;		// file descriptor
	int type; 	// eeprom type
};

/*
 * opens the eeprom device at [dev_fqn] (i.e. /dev/i2c-N) whose address is
 * [addr] and set the eeprom_24c32 [e]
 */
int eeprom_open(char *dev_fqn, int addr, int type, struct eeprom*);
/*
 * closees the eeprom device [e]
 */
int eeprom_close(struct eeprom *e);
/*
 * read and returns the eeprom byte at memory address [mem_addr]
 * Note: eeprom must have been selected by ioctl(fd,I2C_SLAVE,address)
 */
int eeprom_read_byte(struct eeprom* e, __u16 mem_addr);
/*
 * read the current byte
 * Note: eeprom must have been selected by ioctl(fd,I2C_SLAVE,address)
 */
int eeprom_read_current_byte(struct eeprom *e);
/*
 * writes [data] at memory address [mem_addr]
 * Note: eeprom must have been selected by ioctl(fd,I2C_SLAVE,address)
 */
int eeprom_write_byte(struct eeprom *e, __u16 mem_addr, __u8 data);

#endif /* LIBRARIES_INC_ELA_24CXX_H_ */
