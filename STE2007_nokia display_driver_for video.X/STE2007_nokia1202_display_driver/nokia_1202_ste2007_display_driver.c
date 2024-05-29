#include "../STE2007_nokia1202_display_driver/nokia_1202_ste2007_display_driver.h"

void transmit_command(char command)
{
    SCK_down;
    MOSI_down;//0 for commands
    SCK_up;
    
    
    SCK_down;
    for(int i=0; i<8; i++)
    {
        if(command&0x80)    {MOSI_up;}
        else                {MOSI_down;}
        
        SCK_up;
        command<<=1;//command = command<<1;
        //0xE1
        //11100001
        //11000010
        //10000100
        SCK_down;
    }
}

void transmit_data(char data)
{
    SCK_down;
    MOSI_up;//1 for data
    SCK_up;
    
    
    SCK_down;
    for(int i=0; i<8; i++)
    {
        if(data&0x80)       {MOSI_up;}
        else                {MOSI_down;}
        
        SCK_up;
        data<<=1;//command = command<<1;
        //0xE1
        //11100001
        //11000010
        //10000100
        SCK_down;
    }
}

void user_delay(unsigned long delay)
{while(--delay);}

void display_symbol(char symbol)
{
    transmit_data(nlcd_Font[symbol][0]);
    transmit_data(nlcd_Font[symbol][1]);
    transmit_data(nlcd_Font[symbol][2]);
    transmit_data(nlcd_Font[symbol][3]);
    transmit_data(nlcd_Font[symbol][4]);
}

void display_symbols_array(char array[])
{
    for(int i=0; *(array+i)!='\n'; i++)
    {
        display_symbol(*(array+i));
        transmit_data(0x00); //space between symbols
    }
    
}

void page_and_column_address_set(char page, char column)
{
    //page address set
    transmit_command(0xB0|page);
    //page=0 for page 0
    //page=8 for page 8
    
    //column address set
    int c0=((column&0x70)>>4)|0x10;
    int c1=column&0x0F;
    transmit_command(c0);
    transmit_command(c1);
}

void ste2007_display_driver(command_word word)
{
    if(word==display_initialization)
    {
    LED_up;
    CS_down;
    RESET_up;//delay 2.1 ms
    user_delay(290);//for 2.1 ms
    
    transmit_command(0xE2);//internal reset
    user_delay(20);
    transmit_command(0xA4);//all points OFF
    user_delay(20);
    transmit_command(0x2F);//booster on
    user_delay(20);
    transmit_command(0xAF);//display on
    }
    else if(word==clear_all)
    {
        char space[17]="                \n";
        page_and_column_address_set(0, 0);
        display_symbols_array(space);
        
        page_and_column_address_set(1, 0);
        display_symbols_array(space);

        page_and_column_address_set(2, 0);
        display_symbols_array(space);
        
        page_and_column_address_set(3, 0);
        display_symbols_array(space);
        
//        page_and_column_address_set(4, 0);
//        display_symbols_array(space);
//        
//        page_and_column_address_set(5, 0);
//        display_symbols_array(space);
//
//        page_and_column_address_set(6, 0);
//        display_symbols_array(space);
//        
//        page_and_column_address_set(7, 0);
//        display_symbols_array(space);
//        
//        page_and_column_address_set(8, 0);
//        display_symbols_array(space);
    }
    else if(word==permanent_words)
    {
        char first_line[]="First_line\n";
        char second_line[]="Second_line\n";
        char third_line[]="Ещё строка\n";
        
        page_and_column_address_set(0, 0);
        display_symbols_array(first_line);
        
        page_and_column_address_set(1, 0);
        display_symbols_array(second_line);
        
        page_and_column_address_set(2, 0);
        display_symbols_array(third_line);
        
        
    }
}