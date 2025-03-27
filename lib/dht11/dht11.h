#ifndef DHT11_H_
#define DHT11_H_

#include <avr/io.h>
#include <util/delay.h>

#define DHT11_PIN PC0  // DHT11 데이터 핀 (PC0)
#define DHT11_DDR DDRC
#define DHT11_PORT PORTC
#define DHT11_PINR PINC

uint8_t DHT11_Read(uint8_t *temperature, uint8_t *humidity);
uint8_t DHT11_Read_Dec(uint8_t *temperature, uint8_t *humidity, uint8_t *temp_dec, uint8_t *humi_dec);

#endif /* DHT11_H_ */
