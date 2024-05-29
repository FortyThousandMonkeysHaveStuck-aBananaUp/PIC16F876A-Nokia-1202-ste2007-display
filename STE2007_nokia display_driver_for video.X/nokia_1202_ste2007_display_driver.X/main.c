//pragma
// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)


//include
#include <xc.h>
#include "../STE2007_nokia1202_display_driver/nokia_1202_ste2007_display_driver.h"

//extern

int main(void)
{
    //config
    TRISBbits.TRISB0=0; //0 - as output
    TRISBbits.TRISB1=0;
    TRISBbits.TRISB2=0;
    TRISBbits.TRISB3=0;
    TRISBbits.TRISB4=0;
    

//RB0 for LED
//RB1 for SCK   //ch1
//RB2 for MOSI  //ch3
//RB3 for CS    //ch5
//RB4 for RESET //ch7
    
    LED_down;
    SCK_down;
    MOSI_down;
    CS_up;
    RESET_down;
    
    //display initialization
    ste2007_display_driver(display_initialization);
    
    //clear all
    ste2007_display_driver(clear_all);
    
    //display permanent words
    ste2007_display_driver(permanent_words);
    
    page_and_column_address_set(6, 30);
    while(1)
    {
    //display numbers
        for(int i=0; i<10; i++)
        {
            page_and_column_address_set(0, 60);
            display_symbol(numbers_symbols[i]);

            
            page_and_column_address_set(1, 70);
            display_symbol(numbers_symbols[i]);

            
            page_and_column_address_set(2, 60);
            display_symbol(numbers_symbols[i]);
            user_delay(100000);
        }
    }
    
    return 0;
}