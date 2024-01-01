/* 
 * File:   Password_safe.c
 * Author: Ahmed Yasser
 *
 * Created on October 24, 2023, 7:00 AM
 */
#include "password_safe.h"
#include "MCAL_layer/EEPROM/EEPROM.h"
#include "MCAL_layer/Interrupt/interrupt_external.h"

void (burrun0_interrupt)(void);
void (burrun1_interrupt)(void);
void (burrun2_interrupt)(void);
void (burrun3_interrupt)(void);

volatile uint8 rd_value;
volatile uint8 val;
volatile uint8 psw_st = 1;
uint8 cnt;
uint8 arr[5]={'0','1', '2', '3'};
uint8 cnt_pw;

kepad_confg_t keypad = {
  
  .keyad_row_pin[0].port = PORTB_INDEX,
  .keyad_row_pin[0].pin  = PIN3,
  .keyad_row_pin[0].direction = OUTPUT,
  .keyad_row_pin[0].logic = LOW,
  .keyad_row_pin[1].port = PORTB_INDEX,
  .keyad_row_pin[1].pin = PIN5,
  .keyad_row_pin[1].direction = OUTPUT,
  .keyad_row_pin[1].logic = LOW,
  .keyad_row_pin[2].port = PORTB_INDEX,
  .keyad_row_pin[2].pin  = PIN6,
  .keyad_row_pin[2].direction = OUTPUT,
  .keyad_row_pin[2].logic = LOW,
  .keyad_row_pin[3].port = PORTB_INDEX,
  .keyad_row_pin[3].pin = PIN7,
  .keyad_row_pin[3].direction = OUTPUT,
  .keyad_row_pin[3].logic = LOW,
  .keyad_column_pin[0].port = PORTB_INDEX,
  .keyad_column_pin[0].pin = PIN0,
  .keyad_column_pin[0].direction = INPUT,
  .keyad_column_pin[0].logic = LOW,
  .keyad_column_pin[1].port = PORTB_INDEX,
  .keyad_column_pin[1].pin  = PIN1,
  .keyad_column_pin[1].direction = INPUT,
  .keyad_column_pin[1].logic = LOW,
  .keyad_column_pin[2].port = PORTB_INDEX,
  .keyad_column_pin[2].pin = PIN2,
  .keyad_column_pin[2].direction = INPUT,
  .keyad_column_pin[2].logic = LOW,
  .keyad_column_pin[3].port = PORTB_INDEX,
  .keyad_column_pin[3].pin  = PIN4,
  .keyad_column_pin[3].direction = INPUT,
  .keyad_column_pin[3].logic = LOW
};

lcd_confg_4_t lcd_4bit = {
 .rs_lcd.port = PORTD_INDEX,
 .rs_lcd.pin  = PIN2,
 .rs_lcd.direction = OUTPUT,
 .rs_lcd.logic     = LOW,
 .en_lcd.port = PORTD_INDEX,
 .en_lcd.pin = PIN3,
 .en_lcd.direction = OUTPUT,
 .en_lcd.logic = LOW,
 .lcd_pin[0].port = PORTD_INDEX,
 .lcd_pin[0].pin = PIN4,
 .lcd_pin[0].direction = OUTPUT,
 .lcd_pin[0].logic = LOW,
 .lcd_pin[1].port = PORTD_INDEX,    
 .lcd_pin[1].pin  = PIN5,
 .lcd_pin[1].direction = OUTPUT,
 .lcd_pin[1].logic = LOW,
 .lcd_pin[2].port = PORTD_INDEX,
 .lcd_pin[2].pin = PIN6,
 .lcd_pin[2].direction = OUTPUT,
 .lcd_pin[2].logic = LOW,
 .lcd_pin[3].port = PORTD_INDEX,
 .lcd_pin[3].pin  = PIN7,
 .lcd_pin[3].direction = OUTPUT,
 .lcd_pin[3].logic = LOW,
 };

interrupt_INTx_t INT0_obj = {
  .externalfunction = burrun0_interrupt,
  .source = INTERRUPT_EXTERNAL_INT0,
  .interrupt_pin.direction = INPUT,
  .interrupt_pin.pin = PIN0,
  .interrupt_pin.port = PORTB_INDEX,
  .edge_status = INTERRUPT_RISING_EDGE
}; 

interrupt_INTx_t INT1_obj = {
  .externalfunction = burrun1_interrupt,
  .source = INTERRUPT_EXTERNAL_INT1,
  .interrupt_pin.direction = INPUT,
  .interrupt_pin.pin = PIN1,
  .interrupt_pin.port = PORTB_INDEX,
  .edge_status = INTERRUPT_RISING_EDGE
}; 

interrupt_INTx_t INT2_obj = {
  .externalfunction = burrun2_interrupt,
  .source = INTERRUPT_EXTERNAL_INT2,
  .interrupt_pin.direction = INPUT,
  .interrupt_pin.pin = PIN2,
  .interrupt_pin.port = PORTB_INDEX,
  .edge_status = INTERRUPT_RISING_EDGE
}; 
interrupt_RBX_t RB_obj_1 = {
  .EXT_InterruptHandler_LOW =   NULL,
  .EXT_InterruptHandler_HIGH =   burrun3_interrupt,
  .interrupt_pin.direction = INPUT,
  .interrupt_pin.pin = PIN4,
  .interrupt_pin.port = PORTB_INDEX,
};

int main() {
     Std_ReturnType ret = E_NOT_OK;
     application_initialize();
     for(int i = 0; i < 4; i++)
            ret = EEPROM_Write_Data((0x0000 + i),arr[i] - '0');
      while(1){
          
          for(uint8 cnt_row = 0; cnt_row < KEYPAD_ROWS; cnt_row++){
            for(cnt = 0; cnt < KEYPAD_ROWS; cnt++)
            { 
                ret = gpio_pin_write_logic(&(keypad.keyad_row_pin[cnt]),LOW);
            }    
            ret = gpio_pin_write_logic(&(keypad.keyad_row_pin[cnt_row]),HIGH);
          }
          send_4_bit_command(&lcd_4bit,DISPLAY_ON_UNDER_LINE_CURSOR_OFF_BLOCK_CURSOR_ON);
          if(4 == cnt_pw && 0 == psw_st)
          {
            send_4_bit_command(&lcd_4bit,DISPLAY_ON_UNDER_LINE_CURSOR_OFF_BLOCK_CURSOR_OFF);
            send_4_bit_string_data_pos(&lcd_4bit,2,2,"Incorrect Password");
            send_4_bit_string_data_pos(&lcd_4bit,3,2,"     Try Again    ");
            __delay_ms(1000);
            send_4_bit_command(&lcd_4bit,CLEAR_DISPLAY);
            cnt_pw = 0;
            psw_st = 1;
          }
          else if(4 == cnt_pw && 1 == psw_st){
            send_4_bit_command(&lcd_4bit,DISPLAY_ON_UNDER_LINE_CURSOR_OFF_BLOCK_CURSOR_OFF);
            send_4_bit_string_data_pos(&lcd_4bit,2,2,"  correct Password");
            __delay_ms(1000);
            send_4_bit_command(&lcd_4bit,CLEAR_DISPLAY);
            cnt_pw = 0;
          }
 
     }
      return (EXIT_SUCCESS);
}

void application_initialize(void){
    keypad_pin_initialize(&keypad);
    lcd_pins_4_initialize(&lcd_4bit);
    Interrupt_INTX_intialize(&INT0_obj);
    Interrupt_INTX_intialize(&INT1_obj);
    Interrupt_INTX_intialize(&INT2_obj);
    Interrupt_RBX_intialize(&RB_obj_1);
}

void (burrun0_interrupt)(void){
    get_value_INTX_interrupt(&keypad, &INT0_obj, &rd_value);
    send_4_bit_char_data(&lcd_4bit,'*');
    EEPROM_Read_Data(0x0000 + cnt_pw, &val);
    __delay_ms(500);
    if((rd_value - '0') != val)
         psw_st = 0;
    cnt_pw++;
}

void (burrun1_interrupt)(void){
    get_value_INTX_interrupt(&keypad, &INT1_obj, &rd_value);
    send_4_bit_char_data(&lcd_4bit,'*');
    EEPROM_Read_Data(0x0000 + cnt_pw, &val);
    __delay_ms(500);
    if((rd_value - '0') != val)
            psw_st = 0;
    cnt_pw++;
}
void (burrun2_interrupt)(void){
    get_value_INTX_interrupt(&keypad, &INT2_obj, &rd_value);
    send_4_bit_char_data(&lcd_4bit,'*');
    EEPROM_Read_Data(0x0000 + cnt_pw, &val);
     __delay_ms(500);
    if((rd_value - '0') != val)
            psw_st = 0;
    cnt_pw++;
}

void (burrun3_interrupt)(void){
    get_value_RBX_interrupt(&keypad, &RB_obj_1, &rd_value);
    send_4_bit_char_data(&lcd_4bit,'*');
    EEPROM_Read_Data(0x0000 + cnt_pw, &val);
    __delay_ms(500);
    if((rd_value - '0') != val)
            psw_st = 0;
    cnt_pw++;
}
