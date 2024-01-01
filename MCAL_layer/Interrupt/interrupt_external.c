/* 
 * File:   interrupt_external.h
 * Author: Ahmed Yasser
 *
 * Created on September 5, 2023, 11:05 PM
 */

/* Section : includes */
#include "interrupt_external.h"

/* Section : Function Declaration */
void (*INT0_HUNDLER_INTERRUPT)(void);
void (*INT1_HUNDLER_INTERRUPT)(void);
void (*INT2_HUNDLER_INTERRUPT)(void);

void (* RB4_InterruptHandler_LOW)(void);
void (* RB4_InterruptHandler_HIGH)(void);
void (* RB5_InterruptHandler_LOW)(void);
void (* RB5_InterruptHandler_HIGH)(void);
void (* RB6_InterruptHandler_LOW)(void);
void (* RB6_InterruptHandler_HIGH)(void);
void (* RB7_InterruptHandler_LOW)(void);
void (* RB7_InterruptHandler_HIGH)(void);

static Std_ReturnType INT0_SET_HUNDLER_INTERRUPT(void (*interrupt_hunder)(void));
static Std_ReturnType INT1_SET_HUNDLER_INTERRUPT(void (*interrupt_hunder)(void));
static Std_ReturnType INT2_SET_HUNDLER_INTERRUPT(void (*interrupt_hunder)(void));
static Std_ReturnType INTX_SET_HUNDLER_INTERRUPT(const interrupt_INTx_t *int_obj);


static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj);



Std_ReturnType Interrupt_INTX_intialize(const interrupt_INTx_t *int_obj){
      Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
        ret = E_NOT_OK;
    else{
      Interrupt_INTx_Disable( int_obj); 
       Interrupt_INTx_Clear_Flag(int_obj); 
        Interrupt_INTx_Pin_Init( int_obj);
        Interrupt_INTx_Edge_Init(int_obj);
        INTX_SET_HUNDLER_INTERRUPT(int_obj);
        Interrupt_INTx_Enable(int_obj);
        #if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_PRIORITY_ENABLE
        Interrupt_INTx_Priority_Init( int_obj);
        #endif
    }
    return ret;
}
Std_ReturnType Interrupt_INTX_deintialize(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
        ret = E_NOT_OK;
    else{
      Interrupt_INTx_Disable(int_obj); 
    }
    return ret;
}


static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *int_obj){
      Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
        ret = E_NOT_OK;
    else{
        switch(int_obj->source)
        {
            case INTERRUPT_EXTERNAL_INT0 :
                #if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_PRIORITY_ENABLE
                         INTERRUPT_HIGH_PRIORITY_ENABLE();         
                #else
                {
                    INTERRUPT_PeripheralInterrupt_Enable();
                    INTERRUPT_GlobalInterrupt_Enable();
                }    
                 #endif
                     INTERRUPT_INT0_ENABLE();
                     ret = E_OK;
            break;         
            case INTERRUPT_EXTERNAL_INT1 :
                #if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_PRIORITY_ENABLE
                    {
                        INTERRUPT_PRIORITY_GENERAL_ENABLE();
                        if(INTERRUPT_LOW_PRIORITY == int_obj->priority){ 
                         INTERRUPT_LOW_PRIORITY_ENABEL();
                            }
                        else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){ 
                         INTERRUPT_HIGH_PRIORITY_ENABLE();
                        }
                        else{ /* Nothing */ }
                    }
                #else
                {
                    INTERRUPT_PeripheralInterrupt_Enable();
                    INTERRUPT_GlobalInterrupt_Enable();
                }    
                 #endif
                     INTERRUPT_INT1_ENABLE();
                     ret = E_OK;
            break;        
            case INTERRUPT_EXTERNAL_INT2 :
                #if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_PRIORITY_ENABLE
                    {
                        INTERRUPT_PRIORITY_GENERAL_ENABLE();
                        if(INTERRUPT_LOW_PRIORITY == int_obj->priority){ 
                         INTERRUPT_LOW_PRIORITY_ENABEL();
                            }
                        else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){ 
                         INTERRUPT_HIGH_PRIORITY_ENABLE();
                        }
                        else{ /* Nothing */ }
                    }
               
                #else
                {
                    INTERRUPT_PeripheralInterrupt_Enable();
                    INTERRUPT_GlobalInterrupt_Enable();
                }    
                    
                #endif    
                     INTERRUPT_INT2_ENABLE();
                     ret = E_OK;
            break;
            default: ret = E_NOT_OK;
        }
    }
    return ret;
}
static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *int_obj){
     Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
        ret = E_NOT_OK;
    else
    {
          switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 : 
                INTERRUPT_INT0_DISABLE(); /* Disable the INT0 external interrupt */
                ret = E_OK; 
                break;
            case INTERRUPT_EXTERNAL_INT1 : 
                INTERRUPT_INT1_DISABLE(); /* Disable the INT1 external interrupt */
                ret = E_OK; 
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
                INTERRUPT_INT2_DISABLE(); /* Disable the INT2 external interrupt */
                ret = E_OK; 
                break;
            default : ret = E_NOT_OK;
        }
    }
     return ret;
}
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
        ret = E_NOT_OK;
      else{
         
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT1 : 
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){ INTERRUPT_INT1_PRIORITY_LOW(); }
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){  INTERRUPT_INT1_PRIORITY_HIGH(); }
                else{ /* Nothing */ }
                ret = E_OK; 
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){ INTERRUPT_INT2_PRIORITY_LOW(); }
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){ INTERRUPT_INT2_PRIORITY_HIGH(); }
                else{ /* Nothing */ }
                ret = E_OK; 
                break;
            default : ret = E_NOT_OK; 
    }
    }
    return ret;
}
static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
        ret = E_NOT_OK;
       else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 : 
                if(INTERRUPT_FALLING_EDGE == int_obj->edge_status){ INTERRUPT_INT0_FALLINGEDGESET(); }
                else if(INTERRUPT_RISING_EDGE == int_obj->edge_status){ INTERRUPT_INT0_RISINGEDGESET(); }
                else{ /* Nothing */ }
                ret = E_OK; 
                break;
            case INTERRUPT_EXTERNAL_INT1 : 
                if(INTERRUPT_FALLING_EDGE == int_obj->edge_status){ INTERRUPT_INT1_FALLINGEDGESET(); }
                else if(INTERRUPT_RISING_EDGE == int_obj->edge_status){ INTERRUPT_INT1_RISINGEDGESET(); }
                else{ /* Nothing */ }
                ret = E_OK; 
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
                if(INTERRUPT_FALLING_EDGE == int_obj->edge_status){ INTERRUPT_INT2_FALLINGEDGESET(); }
                else if(INTERRUPT_RISING_EDGE == int_obj->edge_status){ INTERRUPT_INT2_RISINGEDGESET(); }
                else{ /* Nothing */ }
                ret = E_OK; 
                break;
            default : ret = E_NOT_OK;
        }
    }
    return ret;
}
static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj){
       Std_ReturnType ret = E_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
         gpio_pin_direction_intialize(&(int_obj->interrupt_pin));
    }
       return ret;
}
static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj){
      Std_ReturnType ret = E_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 : 
                INTERRUPT_INT0_NOT_OCCURE(); /* Clears the interrupt flag for the external interrupt, INT0 */
                ret = E_OK; 
                break;
            case INTERRUPT_EXTERNAL_INT1 : 
                INTERRUPT_INT1_NOT_OCCURE(); /* Clears the interrupt flag for the external interrupt, INT1 */
                ret = E_OK; 
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
                INTERRUPT_INT2_NOT_OCCURE(); /* Clears the interrupt flag for the external interrupt, INT2 */
                ret = E_OK; 
                break;
            default : ret = E_NOT_OK;
        }
    }
    return ret;
}

void INT0_ISR(void){
   INTERRUPT_INT0_NOT_OCCURE();
   if(INT0_SET_HUNDLER_INTERRUPT)
       INT0_HUNDLER_INTERRUPT();
}

void INT1_ISR(void){
   INTERRUPT_INT1_NOT_OCCURE();
   if(INT1_SET_HUNDLER_INTERRUPT)
       INT1_HUNDLER_INTERRUPT();
}

void INT2_ISR(void){
   INTERRUPT_INT2_NOT_OCCURE();
   if(INT2_SET_HUNDLER_INTERRUPT)
       INT2_HUNDLER_INTERRUPT();
}


static Std_ReturnType INT0_SET_HUNDLER_INTERRUPT(void (*interrupt_hunder)(void)){
     Std_ReturnType ret = E_OK;
    if(NULL == interrupt_hunder){
        ret = E_NOT_OK;
    }
   INT0_HUNDLER_INTERRUPT = interrupt_hunder;
    
}
static Std_ReturnType INT1_SET_HUNDLER_INTERRUPT(void (*interrupt_hunder)(void)){
     Std_ReturnType ret = E_OK;
    if(NULL == interrupt_hunder){
        ret = E_NOT_OK;
    }
    INT1_HUNDLER_INTERRUPT = interrupt_hunder;
}
static Std_ReturnType INT2_SET_HUNDLER_INTERRUPT(void (*interrupt_hunder)(void)){
     Std_ReturnType ret = E_OK;
    if(NULL == interrupt_hunder){
        ret = E_NOT_OK;
    }
    INT2_HUNDLER_INTERRUPT = interrupt_hunder;
}
static Std_ReturnType INTX_SET_HUNDLER_INTERRUPT(const interrupt_INTx_t *int_obj){
   Std_ReturnType ret = E_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 : 
                INT0_SET_HUNDLER_INTERRUPT(int_obj->externalfunction); /* Clears the interrupt flag for the external interrupt, INT0 */
                ret = E_OK; 
                break;
            case INTERRUPT_EXTERNAL_INT1 : 
                INT1_SET_HUNDLER_INTERRUPT(int_obj->externalfunction); /* Clears the interrupt flag for the external interrupt, INT1 */
                ret = E_OK; 
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
                INT2_SET_HUNDLER_INTERRUPT(int_obj->externalfunction); /* Clears the interrupt flag for the external interrupt, INT2 */
                ret = E_OK; 
                break;
            default : ret = E_NOT_OK;
        }
    }
    return ret;
}


Std_ReturnType Interrupt_RBX_intialize(const interrupt_RBX_t *int_obj){
          Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
        ret = E_NOT_OK;
    else{
         INTERRUPT_RB_DISABLE();
         INTERRUPT_RB_NOT_OCCURE();
         ret = gpio_pin_direction_intialize(&(int_obj->interrupt_pin));
      
   ret = gpio_pin_direction_intialize(&(int_obj->interrupt_pin));
        /* Initialize the call back functions */
        switch(int_obj->interrupt_pin.pin){
            case PIN4 : 
                RB4_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB4_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                break;
            case PIN5 : 
                RB5_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB5_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                break;
            case PIN6 : 
                RB6_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB6_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                break;
            case PIN7 : 
                RB7_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB7_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                break;
            default:
                ret = E_NOT_OK;
        }
         #if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_PRIORITY_ENABLE
              INTERRUPT_PRIORITY_GENERAL_ENABLE();
        if(INTERRUPT_LOW_PRIORITY == int_obj->priority){ 
            /* This macro will enable low priority global interrupts. */
            INTERRUPT_LOW_PRIORITY_ENABEL();
            /* This routine set the RBx External Interrupt Priority to be Low priority */
            INTERRUPT_RB_PRIORITY_LOW();
        }
        else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){ 
            /* This macro will enable high priority global interrupts. */
            INTERRUPT_HIGH_PRIORITY_ENABLE();
            /* This routine set the RBx External Interrupt Priority to be High priority */
            INTERRUPT_RB_PRIORITY_HIGH();
        }
        else{ /* Nothing */ }
        #else
                {
                    INTERRUPT_PeripheralInterrupt_Enable();
                    INTERRUPT_GlobalInterrupt_Enable();
                }    
               
        #endif
        INTERRUPT_RB_ENABLE();
    }
      
    return ret;
}

Std_ReturnType Interrupt_RBX_deintialize(const interrupt_RBX_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        /* This routine clears the interrupt disable for the external interrupt, RBx */
        INTERRUPT_RB_DISABLE();
        /* This routine clears the interrupt flag for the external interrupt, RBx */
        INTERRUPT_RB_NOT_OCCURE();
    }
    return ret;
}

void RB4_ISR(uint8 RB4_Source){
    /* The RB4 external OnChange interrupt occurred (must be cleared in software) */
    INTERRUPT_RB_NOT_OCCURE();
    /* Code : To be executed from MCAL Interrupt Context */
    /* Application Callback function gets called every time this ISR executes */
    if(0 == RB4_Source){
        if(RB4_InterruptHandler_HIGH){ RB4_InterruptHandler_HIGH(); }
        else{ /* Nothing */ }
    }
    else if (1 == RB4_Source){
        if(RB4_InterruptHandler_LOW){ RB4_InterruptHandler_LOW(); }
        else{ /* Nothing */ }
    }
    else { /* Nothing */ }   
}

/**
 * External Interrupt RB4 MCAL Helper function 
 */
void RB5_ISR(uint8 RB5_Source){
    /* The RB4 external OnChange interrupt occurred (must be cleared in software) */
    INTERRUPT_RB_NOT_OCCURE();
    /* Code : To be executed from MCAL Interrupt Context */
    /* Application Callback function gets called every time this ISR executes */
    if(0 == RB5_Source){
        if(RB5_InterruptHandler_HIGH){ RB5_InterruptHandler_HIGH(); }
        else{ /* Nothing */ }
    }
    else if (1 == RB5_Source){
        if(RB5_InterruptHandler_LOW){ RB5_InterruptHandler_LOW(); }
        else{ /* Nothing */ }
    }
    else { /* Nothing */ }
}

/**
 * External Interrupt RB4 MCAL Helper function 
 */
void RB6_ISR(uint8 RB6_Source){
    /* The RB4 external OnChange interrupt occurred (must be cleared in software) */
    INTERRUPT_RB_NOT_OCCURE();
    /* Code : To be executed from MCAL Interrupt Context */
    /* Application Callback function gets called every time this ISR executes */
    if(0 == RB6_Source){
        if(RB6_InterruptHandler_HIGH){ RB6_InterruptHandler_HIGH(); }
        else{ /* Nothing */ }
    }
    else if (1 == RB6_Source){
        if(RB6_InterruptHandler_LOW){ RB6_InterruptHandler_LOW(); }
        else{ /* Nothing */ }
    }
    else { /* Nothing */ }   
}

/**
 * External Interrupt RB4 MCAL Helper function 
 */
void RB7_ISR(uint8 RB7_Source){
    /* The RB4 external OnChange interrupt occurred (must be cleared in software) */
    INTERRUPT_RB_NOT_OCCURE();
    /* Code : To be executed from MCAL Interrupt Context */
    /* Application Callback function gets called every time this ISR executes */
    if(0 == RB7_Source){
        if(RB7_InterruptHandler_HIGH){ RB7_InterruptHandler_HIGH(); }
        else{ /* Nothing */ }
    }
    else if (1 == RB7_Source){
        if(RB7_InterruptHandler_LOW){ RB7_InterruptHandler_LOW(); }
        else{ /* Nothing */ }
    }
    else { /* Nothing */ }   
}
