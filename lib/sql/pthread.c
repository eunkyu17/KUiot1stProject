#include "pthread.h"

void *saveDataThread(void *arg) {
    SaveDataArgs *data_args = (SaveDataArgs *)arg;

    saveData(data_args->mysql, data_args->data);

    return NULL;
}
