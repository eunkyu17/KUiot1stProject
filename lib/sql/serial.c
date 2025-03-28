#include "farmsql.h"
#include "serial.h"

// 시리얼 포트 설정 함수   ATmega uart 송수신 설정값과 동일하게 셋팅 필요
struct sp_port *setup_serial_port(const char *port_name) {
    struct sp_port *port;
    sp_get_port_by_name(port_name, &port);
    sp_open(port, SP_MODE_READ_WRITE);
    sp_set_baudrate(port, 9600);  // Baud rate 설정
    printf("Serial port %s opened successfully.\n", port_name);
    
    return port;
}

// 시리얼 데이터 전송    port pointer  온도, 습도, 상태 등 데이터 전달 어떤형식으로?
void *send_serial_data(struct sp_port *port, SensorData *tx) {
    int tx_bytes;

    tx_bytes = sp_blocking_write(data->port, tx, sizeof(*tx), 1000);
    if (tx_bytes > 0){
        printf("Sent serial data\n");
    }
    else {
        printf("Error reading data: %d\n", tx_bytes);
    }

    return 0;
}

// 시리얼 데이터 수신 함수
void *receive_serial_data(struct sp_port *port, uint16_t *buffer) {
    int read_bytes;

    read_bytes = sp_blocking_read(port, buffer, sizeof(buffer), 1000);
    if (read_bytes > 0){
        printf("Received serial data \n");

        // SensorData 구조체로 매핑
        rx.temperature = buffer[0];
        rx.humidity = buffer[1];
        rx.soil = buffer[2];
        rx.sun = buffer[3];
        rx.cond = buffer[4];
        
    }
    else{
        printf("Error reading data: %d\n", read_bytes);
    }
    return 0;
}

// https://www.joinc.co.kr/w/Site/Thread/Beginning/PthreadApiReference              pthread
// https://sigrok.org/api/libserialport/unstable/a00018.html                        libserialport
// https://docs.oracle.com/cd/E26502_01/html/E35303/tlib-1.html#tlib-79569          pthread