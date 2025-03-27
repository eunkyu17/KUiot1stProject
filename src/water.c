// #include <avr/io.h>
// #include <util/delay.h>
// #include "clcd.h"
// #include "uart.h"

// int main(void)
// {
//     uart0_init();
//     i2c_lcd_init();
//     DDRA &= ~(1 << PA0);  // PA1 입력

//     PORTA |= (1 << PA0); // ← 내부 풀업 제거함

//     while (1)
//     {
//         if ((PINA & (1 << PA0)))  // HIGH → 수분 부족
//         {
//             i2c_lcd_string(0, 0, "Water, please   ");
//             printf("센서: HIGH → 물 필요\r\n");
//         }
//         else
//         {
//             i2c_lcd_string(0, 0, "Enough!!     ");
//             printf("센서: LOW → 수분 충분\r\n");
//         }
//         _delay_ms(1000);
//     }
// }



// // 값이 제대로 나오지 않음

// /*
// #include <avr/io.h>
// #include <util/delay.h>
// #include <stdio.h>
// #include "clcd.h"
// #include "uart.h"

// void ADC_Init(void)
// {
//     ADMUX = (1 << REFS0);  // AVCC 기준 전압
//     ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1); // ADC 활성화, 분주비 64
// }

// uint16_t ADC_Read(uint8_t channel)
// {
//     ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
//     ADCSRA |= (1 << ADSC);
//     while (ADCSRA & (1 << ADSC));
//     return ADC;
// }

// int main(void)
// {
//     uart0_init();
//     i2c_lcd_init();
//     ADC_Init();

//     while (1)
//     {
//         uint16_t adc_value = ADC_Read(0); // PA0 (ADC0)
//         double voltage = (double)adc_value * (5.0 / 1023.0);
//         double moisture = (voltage / 5.0) * 100;  // 지금 네 센서 기준 올바른 해석

//         char line0[16];
//         char line1[16];

        
//         // 수분 상태에 따라 문구 변경
//         if (moisture <= 40.0)
//         {
//             snprintf(line0, sizeof(line0), "Water, please   ");
//         }
//         else
//         {
//             snprintf(line0, sizeof(line0), "Enough          ");
//         }

//         snprintf(line0, sizeof(line0), "Moisture: %d", (int)moisture);
//         snprintf(line1, sizeof(line1), "ADC:%d V:%.2f", adc_value, voltage);
        
//         i2c_lcd_string(0, 0, line0);
//         i2c_lcd_string(1, 0, line1);

//         _delay_ms(1000);
//     }
// }
// */