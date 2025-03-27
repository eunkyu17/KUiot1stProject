#include "clcd.h"          // 추가: lcd 라이브러리 포함
#include "uart.h"
#include <avr/interrupt.h> // AVR 인터럽트에 대한 헤더파일
#include <avr/io.h>        //AVR 입출력에 대한 헤더 파일
#include <stdio.h>         // 추가: sprintf 사용
#include <string.h>        // 추가: strlen 사용
#include <util/delay.h>    // delay 함수사용을 위한 헤더파일

#define RELAY_PIN PB0    // 릴레이 제어 핀

volatile unsigned int adcResult = 0; // 범위 0~1023

int main(void)
{
    // 릴레이 핀을 출력으로 설정
    DDRB |= (1 << RELAY_PIN);

    ADMUX = 0x40;   // ADC0선택 //single mode, 0번 채널, 3.3V 외부 기준전압(AREF)
    ADCSRA = 0xAF;  // 10101111 //ADC 허가, free running Mode, Interrupt 허가, 128분주
    ADCSRA |= 0x40; // ADSC AD 개시(Start)
    sei();

    uart0_init();
    i2c_lcd_init();
    char str0[16] = "LED:???/CDS:0000";
    char str1[16] = "T:--.-C/Hu:--.-%";

    i2c_lcd_string(0, 0, str0);
    i2c_lcd_string(1, 0, str1);

    while (1)
    {

        // 추가: ADC 값을 LCD에 표시
        // sprintf(str0, "CDS : %u   ", adcResult); // ADC 원시값 표시, 공백으로 이전 자리 지움.
        // i2c_lcd_string(0, 0, str0);

        if (adcResult > 800)
        {
            PORTB |= (1 << RELAY_PIN);  // 릴레이 ON
            sprintf(str0, "LED:ON!/CDS:%u   ", adcResult); // ADC 원시값 표시, 공백으로 이전 자리 지움.
            i2c_lcd_string(0, 0, str0);
            // strcpy(str1, "LED : ON!");
            // i2c_lcd_string(1, 0, str1);
        }
        else
        {
            PORTB &= ~(1 << RELAY_PIN); // 릴레이 OFF
            sprintf(str0, "LED:OFF/CDS:%u   ", adcResult); // ADC 원시값 표시, 공백으로 이전 자리 지움.
            i2c_lcd_string(0, 0, str0);
            // strcpy(str1, "LED : OFF");
            // i2c_lcd_string(1, 0, str1);
        }

        _delay_ms(1000);
    }
}

ISR(ADC_vect)
{
    cli();
    adcResult = ADC; // 2^16 -> 0 ~ 1023
    sei();
}