// #include "clcd.h"
// #include "uart.h"
// #include <avr/io.h>
// #include <util/delay.h>
// #include <string.h>

// #define SWITCH_PIN PE0   // 푸시 스위치 입력 핀
// #define RELAY_PIN PB0    // 릴레이 제어 핀

// void setup() {
//     // 릴레이 핀을 출력으로 설정
//     DDRB |= (1 << RELAY_PIN);
    
//     // 스위치 핀을 입력으로 설정 + 내부 풀업 저항 활성화
//     DDRE &= ~(1 << SWITCH_PIN);
//     PORTE |= (1 << SWITCH_PIN);  // 내부 풀업 저항 활성화
// }

// int main(void) {
//     setup();
//     uart0_init();
//     i2c_lcd_init();

//     char str0[16] = "ATmega128-LCD";
//     char str1[16] = "LED : ???";

//     i2c_lcd_string(0, 0, str0);
//     i2c_lcd_string(1, 0, str1);

//     while (1) {
//         if (!(PINE & (1 << SWITCH_PIN)))
//             break;
//     }

//     while (1) {
//         // 스위치를 누르면 (LOW 상태, GND 연결됨)
//         if (!(PINE & (1 << SWITCH_PIN)))
//         {
//             PORTB |= (1 << RELAY_PIN);  // 릴레이 ON
//             strcpy(str1, "LED : ON!");
//             i2c_lcd_string(1, 0, str1);
//         }
//         else
//         {
//             PORTB &= ~(1 << RELAY_PIN); // 릴레이 OFF
//             strcpy(str1, "LED : OFF");
//             i2c_lcd_string(1, 0, str1);
//         }
//     }

//     return 0;
// }
