#include "dht11.h"

uint8_t DHT11_Read(uint8_t *temperature, uint8_t *humidity) {
    uint8_t data[5] = {0, 0, 0, 0, 0};
    
    // 1. DHT11에 신호를 보냄
    DHT11_DDR |= (1 << DHT11_PIN);   // 출력 모드
    DHT11_PORT &= ~(1 << DHT11_PIN); // LOW 신호 전송
    _delay_ms(18);                   // 18ms 이상 유지
    DHT11_PORT |= (1 << DHT11_PIN);  // HIGH
    _delay_us(30);                   

    // 2. DHT11 응답 대기
    DHT11_DDR &= ~(1 << DHT11_PIN);  // 입력 모드
    _delay_us(40);
    if (DHT11_PINR & (1 << DHT11_PIN)) return 1;
    _delay_us(80);
    if (!(DHT11_PINR & (1 << DHT11_PIN))) return 2;
    _delay_us(80);

    // 3. 데이터 읽기 (40비트)
    for (uint8_t i = 0; i < 5; i++) {
        for (uint8_t j = 0; j < 8; j++) {
            while (!(DHT11_PINR & (1 << DHT11_PIN))); // LOW 대기
            _delay_us(30);
            if (DHT11_PINR & (1 << DHT11_PIN))
                data[i] = (data[i] << 1) | 1;
            else
                data[i] = (data[i] << 1);
            while (DHT11_PINR & (1 << DHT11_PIN)); // HIGH 대기
        }
    }

    // 4. 체크섬 확인
    if ((data[0] + data[1] + data[2] + data[3]) != data[4]) return 3;

    *humidity = data[0];
    *temperature = data[2];

    return 0;  // 정상
}

uint8_t DHT11_Read_Dec(uint8_t *temperature, uint8_t *humidity, uint8_t *temp_dec, uint8_t *humi_dec) {
    uint8_t data[5] = {0, 0, 0, 0, 0};

    // 1. DHT11 신호 전송 (Start Signal)
    DHT11_DDR |= (1 << DHT11_PIN);   // 출력 모드 설정
    DHT11_PORT &= ~(1 << DHT11_PIN); // LOW 신호 전송
    _delay_ms(18);                   // 18ms 이상 LOW 유지 (시작 신호)
    DHT11_PORT |= (1 << DHT11_PIN);  // HIGH 신호로 전환
    _delay_us(30);                   

    // 2. DHT11 응답 대기
    DHT11_DDR &= ~(1 << DHT11_PIN);  // 입력 모드 전환
    _delay_us(40);
    if (DHT11_PINR & (1 << DHT11_PIN)) return 1; // 응답 없음
    _delay_us(80);
    if (!(DHT11_PINR & (1 << DHT11_PIN))) return 2; // 응답 오류
    _delay_us(80);

    // 3. 데이터 수신 (40비트)
    for (uint8_t i = 0; i < 5; i++) {
        for (uint8_t j = 0; j < 8; j++) {
            while (!(DHT11_PINR & (1 << DHT11_PIN))); // LOW 상태 대기
            _delay_us(30);
            if (DHT11_PINR & (1 << DHT11_PIN))
                data[i] = (data[i] << 1) | 1; // 1 비트 저장
            else
                data[i] = (data[i] << 1); // 0 비트 저장
            while (DHT11_PINR & (1 << DHT11_PIN)); // HIGH 상태 대기
        }
    }

    // 4. 체크섬 확인
    if ((data[0] + data[1] + data[2] + data[3]) != data[4]) return 3; // 오류

    *humidity = data[0];   // 습도 정수 부분
    *humi_dec = data[1];   // 습도 소수 부분
    *temperature = data[2]; // 온도 정수 부분
    *temp_dec = data[3];    // 온도 소수 부분 (대부분 0)

    return 0;  // 정상 데이터 수신 완료
}
