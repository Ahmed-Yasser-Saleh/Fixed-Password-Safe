/* 
 * File:   EEPROM.h
 * Author: Ahmed Yasser
 *
 * Created on September 12, 2023, 9:39 AM
 */

/* Section : Includes */
#include "EEPROM.h"
/* Section : Macro Declarations */
/* Section : Macro Function Declaration */
/* Section : Data Type Declarations */
/* Section : Function Declarations */
Std_ReturnType EEPROM_Write_Data(uint16 addrees, uint8 data){
    Std_ReturnType ret = E_OK;
     uint8 global_iterrupr_status = INTCONbits.GIE;
     
        EEADRH = (uint8)((addrees >> 8) & 0x03);
        EEADR  = (uint8)(addrees & 0xFF);
        EEDATA = data;
        
        ACCESS_DATA_EEPROM_MEMORY();
        ACCESS_DATA_EEPROM_MEMORY_2();
        
        WRITE_OPERATION_ENABLE();
        
       
        
        INTERRUPT_GlobalInterrupt_Disable();
        
        EECON2 = 0x55;
        EECON2 = 0xAA;
        
        WRITE_CONTROL();
        while(EECON1bits.WR);
        
        WRITE_OPERATION_DISABLE();
        INTCONbits.GIE = global_iterrupr_status;
    return ret;
}
Std_ReturnType EEPROM_Read_Data(uint16 addrees, uint8 *data){
     Std_ReturnType ret = E_OK;
    if(NULL == data)
    {
     ret = E_NOT_OK;
    }
    else {
        EEADRH = (uint8)((addrees >> 8) & 0x03);
        EEADR  = (uint8)(addrees & 0xFF);
        
        ACCESS_DATA_EEPROM_MEMORY();
        ACCESS_DATA_EEPROM_MEMORY_2();
        
        READ_CONTROL();
        
        NOP();
        NOP();  
        
        *data = EEDATA;
    }  
  return ret;
} 