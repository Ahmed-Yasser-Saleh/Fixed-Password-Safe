/* 
 * File:   ecu_keypad.h
 * Author: Ahmed Yasser
 *
 * Created on August 15, 2023, 7:48 AM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

/* Section : Includes */
#include "ecu_keypad_confg.h"
#include "../../MCAL_layer/GPIO/gpio.h"
#include "../../MCAL_layer/Interrupt/interrupt_external.h"

/* Section : Macro Declarations */
#define KEYPAD_ROWS      4
#define KEYPAD_COLUMNS   4
#define ROW_PIN_0        0
#define ROW_PIN_1        1
#define ROW_PIN_2        2
#define ROW_PIN_3        3
#define COLUMN_PIN_0     0
#define COLUMN_PIN_1     1
#define COLUMN_PIN_2     2
#define COLUMN_PIN_3     3

/* Section : Macro Function Declaration */
/* Section : Data Type Declarations */
typedef struct {
    Pin_Config_t keyad_row_pin[KEYPAD_ROWS];
    Pin_Config_t keyad_column_pin[KEYPAD_COLUMNS];
}kepad_confg_t;
/* Section : Function Declarations */
Std_ReturnType keypad_pin_initialize(const kepad_confg_t *keypad);
Std_ReturnType get_value(const kepad_confg_t *keypad, uint8 *value);

#if INTERRUPT_INT_EXTERNAL_FEATURE == INTERRUPT_EXTERNAL_ENABLE
Std_ReturnType get_value_INTX_interrupt(const kepad_confg_t *keypad, const interrupt_INTx_t *INTX, uint8 *value);
Std_ReturnType get_value_RBX_interrupt(const kepad_confg_t *keypad, const interrupt_RBX_t *RBX, uint8 *value);
#endif

#endif	/* ECU_KEYPAD_H */

