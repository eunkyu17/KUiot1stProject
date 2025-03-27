#ifndef DHT11_H_
#define DHT11_H_

#include <avr/io.h>
#include <util/delay.h>

#define DHT11_PIN PF0  // DHT11 데이터 핀 (PF0)
#define DHT11_DDR DDRF
#define DHT11_PORT PORTF
#define DHT11_PINR PINF

uint8_t DHT11_Read(uint8_t *temperature, uint8_t *humidity);

#endif /* DHT11_H_ */
