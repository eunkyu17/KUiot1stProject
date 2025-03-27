#include "clcd.h"
#include "dht11.h"
#include "uart.h"
#include <avr/interrupt.h> // AVR 인터럽트에 대한 헤더파일
#include <avr/io.h>        // AVR 입출력에 대한 헤더 파일
#include <stdio.h>
#include <string.h>
#include <util/delay.h>    // delay 함수사용을 위한 헤더파일

#define RELAY_PIN PB0    // 릴레이 제어 핀

uint16_t ADC_Read(uint8_t channel);

int main(void)
{
    uint8_t temperature, humidity, temp_dec, humi_dec;
    uint16_t cds_value, light_value, soil_value, moisture_value;

    // 릴레이 핀을 출력으로 설정
    DDRB |= (1 << RELAY_PIN);

    ADMUX = (1 << REFS0);  // AVCC 기준 전압 설정
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // ADC 활성화, 분주비 128

    DDRE = _BV(PE3);    // 서보모터 PE3 출력 설정.

    TCCR3A = _BV(COM3A1) | _BV(WGM31);
    TCCR3B = _BV(WGM33) | _BV(WGM32) | _BV(CS31);
    // 분주비 8, fast PWM mode, timer3
    ICR3 = 40000;   // 20ms -> 16000000 / 8 = 2000000 Hz -> 500us * 40000 = 20ms
    OCR3A = 3000;   // 40000 : 20 = ? : 1.5 -> ? = 60000 / 20 = 3000 -> 2000~4000 -> -90 ~ 90

    uart0_init();
    i2c_lcd_init();
    char str0[16] = "CDS:00/Soil:000%%";
    char str1[16] = "T:--.-C/Hu:--.-%%";

    i2c_lcd_string(0, 0, str0);
    i2c_lcd_string(1, 0, str1);

    while (1)
    {
        cds_value = ADC_Read(0);            // ADC0 (PF0)에서 데이터 읽기
        light_value = (1023 - cds_value) * 10 / 103;    // 빛 세기 0~100
        soil_value = ADC_Read(2) - 300;     // ADC2 (PF2)에서 데이터 읽기
        moisture_value = (750 - soil_value) * 10 / 75;  // 토양수분함량 (%)
        DHT11_Read_Dec(&temperature, &humidity, &temp_dec, & humi_dec); // 온습도 측정 (디지털)
        sprintf(str0, "CDS:%02u/Soil:%u%%   ", light_value, moisture_value);
        i2c_lcd_string(0, 0, str0);
        sprintf(str1, "T:%u.%uC/Hu:%u.%u%%  ", temperature, temp_dec, humidity, humi_dec);
        i2c_lcd_string(1, 0, str1);

        if (cds_value > 800)
        {
            PORTB |= (1 << RELAY_PIN);  // 릴레이 ON
            
        }
        else
        {
            PORTB &= ~(1 << RELAY_PIN); // 릴레이 OFF
        }

        if (moisture_value < 30)
        {
            for (uint16_t pulse = 4000; pulse > 1800; pulse -= 40)
            {
                OCR3A = pulse;
                _delay_ms(50);
            }
            _delay_ms(1000);
            OCR3A = 4000;
        }

        _delay_ms(2000);
    }
}

// ADC 값 읽기 (0~1023)
uint16_t ADC_Read(uint8_t channel) {
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F); // ADC 채널 설정
    ADCSRA |= (1 << ADSC); // 변환 시작
    while (ADCSRA & (1 << ADSC)); // 변환 완료 대기
    return ADC;
}