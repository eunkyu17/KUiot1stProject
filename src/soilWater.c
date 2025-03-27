#include "clcd.h"
#include "dht11.h"
#include "uart.h"
#include <avr/interrupt.h> // AVR 인터럽트에 대한 헤더파일
#include <avr/io.h>        // AVR 입출력에 대한 헤더 파일
#include <stdio.h>
#include <string.h>
#include <util/delay.h>    // delay 함수사용을 위한 헤더파일

uint16_t ADC_Read(uint8_t channel);


int main(void) {
    uart0_init();
    i2c_lcd_init();
    char str0[16] = "LED:???/CDS:0000";
    char str1[16] = "T:--.-C/Hu:--.-%";

    i2c_lcd_string(0, 0, str0);
    i2c_lcd_string(1, 0, str1);

    char buffer[20];  // 문자열 버퍼
    uint16_t soil_value, moisture_value;

    ADMUX = (1 << REFS0);  // AVCC 기준 전압 설정
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // ADC 활성화, 분주비 128

    while (1) {
        soil_value = ADC_Read(2) - 300;  // ADC2 (PF2)에서 데이터 읽기
        moisture_value = (750 - soil_value) * 10 / 75;
        sprintf(str0, "Soil:%u        ", soil_value);
        sprintf(str1, "Mois:%u%%      ", moisture_value);

        i2c_lcd_string(0, 0, str0);
        i2c_lcd_string(1, 0, str1);

        _delay_ms(1000);  // 1초마다 측정
    }
}

// ADC 값 읽기 (0~1023)
uint16_t ADC_Read(uint8_t channel) {
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F); // ADC 채널 설정
    ADCSRA |= (1 << ADSC); // 변환 시작
    while (ADCSRA & (1 << ADSC)); // 변환 완료 대기
    return ADC;
}
