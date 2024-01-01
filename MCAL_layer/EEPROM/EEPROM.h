/* 
 * File:   EEPROM.h
 * Author: Ahmed Yasser
 *
 * Created on September 12, 2023, 9:39 AM
 */

#ifndef EEPROM_H
#define	EEPROM_H

/* Section : Includes */
#include "../mcal_std_types.h"
#include <../proc/pic18f4620.h>
#include "../device_config.h"
#include "../Interrupt/interrupt_cfg.h"

/* Section : Macro Declarations */     

/* Section : Macro Function Declaration */
#define  ACCESS_DATA_EEPROM_MEMORY()            (EECON1bits.EEPGD = 0)
#define  ACCESS_DATA_EEPROM_MEMORY_2()          (EECON1bits.CFGS = 0)

#define  WRITE_OPERATION_ENABLE()               (EECON1bits.WREN = 1)
#define  WRITE_OPERATION_DISABLE()              (EECON1bits.WREN = 0)
#define  WRITE_CONTROL()                        (EECON1bits.WR = 1) 

#define READ_CONTROL()                          (EECON1bits.RD = 1)

/* Section : Data Type Declarations */

/* Section : Function Declarations */
Std_ReturnType EEPROM_Write_Data(uint16 address, uint8 data);
Std_ReturnType EEPROM_Read_Data(uint16 address, uint8 *data);
#endif	/* EEPROM_H */

