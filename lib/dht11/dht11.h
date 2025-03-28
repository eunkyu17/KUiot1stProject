#ifndef DHT11_H_
#define DHT11_H_

#include <avr/io.h>
#include <util/delay.h>

#define DHT11_PIN PF3  // DHT11 데이터 핀 (PF3)
#define DHT11_DDR DDRF
#define DHT11_PORT PORTF
#define DHT11_PINR PINF

uint8_t DHT11_Read(uint8_t *temperature, uint8_t *humidity);
uint8_t DHT11_Read_Dec(uint8_t *temperature, uint8_t *humidity, uint8_t *temp_dec, uint8_t *humi_dec);

#endif /* DHT11_H_ */
