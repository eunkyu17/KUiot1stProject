// #include <avr/io.h>
// #include <util/delay.h>
// #include "dht11.h"

// #define F_CPU 16000000UL
// #define BAUD 115200
// #define MYUBRR F_CPU/16/BAUD-1

// void UART_Init(unsigned int ubrr) {
//     UBRR0H = (unsigned char)(ubrr >> 8);
//     UBRR0L = (unsigned char)ubrr;
//     UCSR0B = (1 << RXEN0) | (1 << TXEN0);   // 송수신 활성화
//     UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8비트 데이터
// }

// void UART_Transmit(char data) {
//     while (!(UCSR0A & (1 << UDRE0)));  // 버퍼가 비어 있는지 확인
//     UDR0 = data;
// }

// void UART_SendString(const char *str) {
//     while (*str) {
//         UART_Transmit(*str++);
//     }
// }

// void UART_SendInt(uint8_t num) {
//     char buffer[4];
//     itoa(num, buffer, 10);  // 정수를 문자열로 변환
//     UART_SendString(buffer);
// }

// int main(void) {
//     uint16_t temperature, humidity;
    
//     UART_Init(MYUBRR);  // UART 초기화
//     _delay_ms(1000);    // 안정화 대기

//     UART_SendString("DHT11 Sensor Test\r\n");

//     while (1) {
//         if (DHT11_Read(&temperature, &humidity) == 0) {
//             UART_SendString("Temperature: ");
//             UART_SendInt(temperature);
//             UART_SendString("°C, Humidity: ");
//             UART_SendInt(humidity);
//             UART_SendString("%\r\n");
//         } else {
//             UART_SendString("DHT11 Read Error!\r\n");
//         }

//         _delay_ms(2000); // 2초마다 측정
//     }
// }
