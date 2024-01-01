/* 
 * File:   interrupt_manager.h
 * Author: Ahmed Yasser
 *
 * Created on September 7, 2023, 2:30 PM
 */

/* Section : Includes */
#include "interrupt_manager.h"

/* Section : Macro Declarations */ 


/* Section : Macro Function Declaration */

/* Section : Data Type Declarations */
static volatile RB4_Flag = 1;
/* Section : Function Declarations */

#if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_PRIORITY_ENABLE
void __interrupt() InterruptManagerHigh(void){
 
}

void __interrupt(low_priority) InterruptManagerLow(void){ 

 
}
#else

void __interrupt() InterruptManager(void){
 
 if((INTERRUPT_ENABLE == INTCONbits.INT0E) && (INTERRUPT_OCCURE == INTCONbits.INT0F)){
        INT0_ISR(); /* External Interrupt 0 */
    }
    else{ /* Nothing */ }
    if((INTERRUPT_ENABLE == INTCON3bits.INT1E) && (INTERRUPT_OCCURE == INTCON3bits.INT1F)){
        INT1_ISR(); /* External Interrupt 1 */
    }
    else{ /* Nothing */ }
    if((INTERRUPT_ENABLE == INTCON3bits.INT2E) && (INTERRUPT_OCCURE == INTCON3bits.INT2F)){
        INT2_ISR(); /* External Interrupt 2 */
    }
    else{ /* Nothing */ }
 if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCURE == INTCONbits.RBIF) && 
       (PORTBbits.RB4 == 1) && (RB4_Flag == 1)){
        RB4_Flag = 0;
        RB4_ISR(0);
    }
    else{ /* Nothing */ }
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCURE == INTCONbits.RBIF) && 
       (PORTBbits.RB4 == 0) && (RB4_Flag == 0)){
        RB4_Flag = 1;
        RB4_ISR(1);
    }
    else{ /* Nothing */ }
}
#endif
