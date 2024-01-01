/* 
 * File:   interrupt_external.h
 * Author: Ahmed Yasser
 *
 * Created on September 5, 2023, 11:05 PM
 */

#ifndef INTERRUPT_EXTERNAL_H
#define	INTERRUPT_EXTERNAL_H

/* Section : Includes */
#include "interrupt_cfg.h"
#include "../GPIO/gpio.h"

/* Section : Macro Declarations */ 

#define INTERRUPT_EXTERNAL_INT0_DISABLE              0x00
#define INTERRUPT_EXTERNAL_INT0_ENABLE               0x01

#define INTERRUPT_EXTERNAL_INT0_NOT_OCCURE           0x00
#define INTERRUPT_EXTERNAL_INT0_OCCURE               0x00

#define INTERRUPT_LOW_PRIORITY         0x00
#define INTERRUPT_HIGH_PRIORITY        0x01

/* Section : Macro Function Declaration */

#if INTERRUPT_INT_EXTERNAL_FEATURE == INTERRUPT_EXTERNAL_ENABLE

#define INTERRUPT_INT0_DISABLE()            (INTCONbits.INT0E = 0)
#define INTERRUPT_INT0_ENABLE()             (INTCONbits.INT0E = 1)
 #define INTERRUPT_INT0_NOT_OCCURE()         (INTCONbits.INT0F = 0)
#define INTERRUPT_INT0_OCCURE()             (INTCONbits.INT0F = 1)  //note when interrupt occure flag direct = 1
#define INTERRUPT_INT0_FALLINGEDGESET()     (INTCON2bits.INTEDG0 = 0)
#define INTERRUPT_INT0_RISINGEDGESET()      (INTCON2bits.INTEDG0 = 1)

#define INTERRUPT_INT1_DISABLE()            (INTCON3bits.INT1E = 0)
#define INTERRUPT_INT1_ENABLE()             (INTCON3bits.INT1E = 1)
 #define INTERRUPT_INT1_NOT_OCCURE()         (INTCON3bits.INT1F = 0) 
#define INTERRUPT_INT1_OCCURE()             (INTCON3bits.INT1F = 1)  //note when interrupt occure flag direct = 1
#define INTERRUPT_INT1_FALLINGEDGESET()     (INTCON2bits.INTEDG1 = 0)
#define INTERRUPT_INT1_RISINGEDGESET()      (INTCON2bits.INTEDG1 = 1)

#define INTERRUPT_INT2_DISABLE()            (INTCON3bits.INT2E = 0)
#define INTERRUPT_INT2_ENABLE()             (INTCON3bits.INT2E = 1)
#define INTERRUPT_INT2_NOT_OCCURE()         (INTCON3bits.INT2F = 0) //note when interrupt occure flag direct = 1
#define INTERRUPT_INT2_OCCURE()             (INTCON3bits.INT2F = 1) 
#define INTERRUPT_INT2_FALLINGEDGESET()     (INTCON2bits.INTEDG2 = 0)
#define INTERRUPT_INT2_RISINGEDGESET()      (INTCON2bits.INTEDG2 = 1)

#if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_PRIORITY_ENABLE

#define INTERRUPT_INT1_PRIORITY_LOW()       (INTCON3bits.INT1P = 0)
#define INTERRUPT_INT1_PRIORITY_HIGH()      (INTCON3bits.INT1P = 1)

#define INTERRUPT_INT2_PRIORITY_LOW()       (INTCON3bits.INT2P = 0)
#define INTERRUPT_INT2_PRIORITY_HIGH()      (INTCON3bits.INT2P = 1)

#endif

#endif

#if INTERRUPT_ONCHANGE_EXTERNAL_FEATURE == INTERRUPT_EXTERNAL_ENABLE

#define INTERRUPT_RB_DISABLE()            (INTCONbits.RBIE = 0)
#define INTERRUPT_RB_ENABLE()             (INTCONbits.RBIE = 1)
 #define INTERRUPT_RB_NOT_OCCURE()         (INTCONbits.RBIF = 0) //note when interrupt occure flag direct = 1
#define INTERRUPT_RB_OCCURE()             (INTCONbits.RBIF = 1) 

#if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_PRIORITY_ENABLE

#define INTERRUPT_RB_PRIORITY_LOW()       (INTCON2bits.RBIP = 0)
#define INTERRUPT_RB_PRIORITY_HIGH()      (INTCON2bits.RBIP = 1)

#endif
#endif

/* Section : Data Type Declaration */
typedef enum{
    INTERRUPT_EXTERNAL_INT0,
    INTERRUPT_EXTERNAL_INT1,
    INTERRUPT_EXTERNAL_INT2        
}interrpt_INTX_index;

typedef enum{
    FALLING_EDGE,
    RISING_EDGE        
}interrupt_external_edge_st;

typedef struct{
   void (*externalfunction)(void);
   interrpt_INTX_index source;
   interrupt_external_edge_st edge_status;
   interrupt_priority_status priority;
   Pin_Config_t interrupt_pin;
}interrupt_INTx_t;

typedef struct{
    void (*EXT_InterruptHandler_HIGH)(void);
    void (*EXT_InterruptHandler_LOW)(void);
   interrupt_priority_status priority;
   Pin_Config_t interrupt_pin;
}interrupt_RBX_t;
/* Section : Function Declaration */
Std_ReturnType Interrupt_INTX_intialize(const interrupt_INTx_t *int_obj);
Std_ReturnType Interrupt_INTX_deintialize(const interrupt_INTx_t *int_obj);
Std_ReturnType Interrupt_RBX_intialize(const interrupt_RBX_t *int_obj);
Std_ReturnType Interrupt_RBX_deintialize(const interrupt_RBX_t *int_obj);
#endif	/* INTERRUPT_EXTERNAL_H */

