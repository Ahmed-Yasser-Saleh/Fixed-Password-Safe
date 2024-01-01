/* 
 * File:   ecu_keypad_confg.c
 * Author: Ahmed Yasser
 *
 * Created on August 15, 2023, 7:49 AM
 */
/* Section : Includes */
#include "ecu_keypad.h"

/* Section : Macro Declarations */
/* Section : Macro Function Declaration */
/* Section : Data Type Declarations */
uint8 keypad_val[KEYPAD_ROWS][KEYPAD_COLUMNS] = {  
                                                  {'7', '8', '9', '/'},
                                                  {'4', '5', '6', '*'},
                                                  {'1', '2', '3', '-'},
                                                  {'#', '0', '=', '+'}
                                               };

/* Section : Function Declarations */
Std_ReturnType keypad_pin_initialize(const kepad_confg_t *keypad){
     Std_ReturnType ret = E_OK;
    if(NULL == keypad)
        ret = E_NOT_OK;
    else{
        gpio_pin_intialize(&(keypad->keyad_row_pin[ROW_PIN_0]));
        gpio_pin_intialize(&(keypad->keyad_row_pin[ROW_PIN_1]));
        gpio_pin_intialize(&(keypad->keyad_row_pin[ROW_PIN_2]));
        gpio_pin_intialize(&(keypad->keyad_row_pin[ROW_PIN_3]));
        gpio_pin_direction_intialize(&(keypad->keyad_column_pin[COLUMN_PIN_0]));
        gpio_pin_direction_intialize(&(keypad->keyad_column_pin[COLUMN_PIN_1]));
        gpio_pin_direction_intialize(&(keypad->keyad_column_pin[COLUMN_PIN_2]));
        gpio_pin_direction_intialize(&(keypad->keyad_column_pin[COLUMN_PIN_3]));
    }
    return ret;
}
Std_ReturnType get_value(const kepad_confg_t *keypad, uint8 *value){
    Std_ReturnType ret = E_OK;
    uint8 cnt_row = 0; uint8 cnt_col = 0; uint8 cnt = 0;
    Logic_t pin_colm_st = LOW;
 
    if(NULL == keypad || NULL == value)
        ret = E_NOT_OK;
    else{
        for(cnt_row = 0; cnt_row < KEYPAD_ROWS; cnt_row++){
            for(cnt = 0; cnt < KEYPAD_ROWS; cnt++)
            { 
                ret = gpio_pin_write_logic(&(keypad->keyad_row_pin[cnt]),LOW);
            }    
            ret = gpio_pin_write_logic(&(keypad->keyad_row_pin[cnt_row]),HIGH);
            for(cnt_col = 0; cnt_col < KEYPAD_COLUMNS; cnt_col++)
            {
                ret = gpio_pin_read_logic(&(keypad->keyad_column_pin[cnt_col]),&pin_colm_st);
                if(HIGH == pin_colm_st)
                       *value = keypad_val[cnt_row][cnt_col];
            } 
       }
    }
    return ret; 
}

#if INTERRUPT_INT_EXTERNAL_FEATURE == INTERRUPT_EXTERNAL_ENABLE

Std_ReturnType get_value_INTX_interrupt(const kepad_confg_t *keypad, const interrupt_INTx_t *INTX, uint8 *value){
     Std_ReturnType ret = E_OK;
      Logic_t pin_row_st = LOW;
    if(NULL == keypad || NULL == value || NULL == INTX)
        ret = E_NOT_OK;
    else {   
            for(uint8 cnt = 0; cnt < KEYPAD_ROWS; cnt++)
            { 
                ret = gpio_pin_read_logic(&(keypad->keyad_row_pin[cnt]),&pin_row_st);
                if(HIGH == pin_row_st)
                    *value =  keypad_val[cnt][INTX->interrupt_pin.pin];
                pin_row_st = LOW;
            }    
    }
    return ret;
}
Std_ReturnType get_value_RBX_interrupt(const kepad_confg_t *keypad, const interrupt_RBX_t *RBX, uint8 *value){
      Std_ReturnType ret = E_OK;
      Logic_t pin_row_st = LOW;
    if(NULL == keypad || NULL == value || NULL == RBX)
        ret = E_NOT_OK;
    else {   
            for(uint8 cnt = 0; cnt < KEYPAD_ROWS; cnt++)
            { 
                ret = gpio_pin_read_logic(&(keypad->keyad_row_pin[cnt]),&pin_row_st);
                if(HIGH == pin_row_st)
                       *value =  keypad_val[cnt][RBX->interrupt_pin.pin - 1];       
            }    
    }
    return ret;
}
#endif