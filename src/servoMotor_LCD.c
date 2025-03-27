// #include "clcd.h"
// #include "dht11.h"
// #include "uart.h"
// #include <avr/io.h>
// #include <util/delay.h>
// #include <stdlib.h>

// int main(void)
// {
//     DDRE = _BV(PE3);    // PE3 출력 설정.

//     TCCR3A = _BV(COM3A1) | _BV(WGM31);
//     TCCR3B = _BV(WGM33) | _BV(WGM32) | _BV(CS31);
//     // 분주비 8, fast PWM mode, timer3
//     ICR3 = 40000;   // 20ms -> 16000000 / 8 = 2000000 Hz -> 500us * 40000 = 20ms
//     OCR3A = 3000;   // 40000 : 20 = ? : 1.5 -> ? = 60000 / 20 = 3000 -> 2000~4000 -> -90 ~ 90

//     uart0_init();
//     i2c_lcd_init();
//     char str0[16] = "--Servo  Motor--";
//     char str1[16] = "pulse:0000";

//     i2c_lcd_string(0, 0, str0);
//     i2c_lcd_string(1, 0, str1);
//     _delay_ms(2000);

//     while(1)
//     {
//         for(uint16_t pulse = 4000; pulse > 1800; pulse -= 40)
//         {
//             OCR3A = pulse;
//             sprintf(str1, "pulse:%u ", pulse);
//             i2c_lcd_string(1, 0, str1);
//             _delay_ms(20);
//         }
//         _delay_ms(1000);
//         OCR3A = 4000;
//         i2c_lcd_string(1, 0, "pulse:4000");
//         _delay_ms(5000);
//     }

//     return 0;
// }