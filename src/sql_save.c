
#include "farmsql.h"
#include "serial.h"
#include "pthread.h"

int main(void){

    MySQLConnection sqlinfo; // sql 데이터 저장 변수
    SaveDataArgs args;       // sql, sensordata 넣는 구조체
    SensorData rx;           // 수신 sensor data 저장
    const char *port_name;   // 포트이름 설정
    volatile unsigned int adcResult = 0; // 범위 0~1023
    uint16_t buffer[10];     // 수신데이터 저장
    struct sp_port *port;    // 포트 포인터 저장 변수
    pthread_t save_thread;   // pthread ID
    initMySQL(*sqlinfo);     // sql 초기화
    port = setup_serial_port(port_name);     //시리얼 포트 설정
    
    stdin = &INPUT;
    stdout = &OUTPUT;

    while(1){
    
        
        // save data in sql
        receive_serial_data(port, buffer);    //SensorData rx에 데이터 저장
        args.mysql = sqlinfo;
        args.data = rx;

        // pthread를 사용해 스레드 생성
        pthread_create(&save_thread, NULL, saveDataThread, &args);
        // 스레드 종료 대기
        pthread_join(save_thread, NULL); // 스레드 종료 대기
        // MySQL 연결 종료
        closeMySQL(sqlinfo);


    
    }



}

