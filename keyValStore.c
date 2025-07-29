#include "keyValStore.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

typedef struct {
    char key[MAX_KEY_LEN];
    char value[MAX_VALUE_LEN];
    int in_use; // 0 = frei, 1=Eintrag belegt
} KeyValue; // Datensatz mit einem Key und dem zugehörigen Value

static KeyValue *store = NULL;
static int shm_id;

int initStore() {


     shm_id = shmget(IPC_PRIVATE, sizeof(KeyValue) * MAX_ENTRIES, IPC_CREAT | 0666);
     // bei Fehlschlag:
     if (shm_id < 0) {
        perror("shmget");
        return -1;
    }

    store = (KeyValue *)shmat(shm_id, NULL, 0);
    // bei Fehlschalag wird "-1" als ungültiger Zeigerwert zurückgegeben
    if (store == (void *) -1) {
        perror("shmat");
        exit(1);
}
    // store ist halt ein Array
    // Jede Element im store[] Array wird zur Nutzung freigegeben
    for (int i = 0; i < MAX_ENTRIES; i++) { // durchlaufen die store[] array
        store[i].in_use = 0; // 0 -> frei
    }
    return 0;
}

int put(const char *key, const char *value) {
    for (int i = 0; i < MAX_ENTRIES; i++) {
        if (store[i].in_use && strcmp(store[i].key, key) == 0) {
            strncpy(store[i].value, value, MAX_VALUE_LEN - 1);
            store[i].value[MAX_VALUE_LEN - 1] = '\0';
            return 0;
        }
    }

    for (int i = 0; i < MAX_ENTRIES; i++) {
        if (!store[i].in_use) {
            store[i].in_use = 1;
            strncpy(store[i].key, key, MAX_KEY_LEN - 1);
            store[i].key[MAX_KEY_LEN - 1] = '\0';
            strncpy(store[i].value, value, MAX_VALUE_LEN - 1);
            store[i].value[MAX_VALUE_LEN - 1] = '\0';
            return 0;
        }
    }
    return -1;
}

int get(const char *key, char *result) {
    for (int i = 0; i < MAX_ENTRIES; i++) {
        if (store[i].in_use && strcmp(store[i].key, key) == 0) {
            strncpy(result, store[i].value, MAX_VALUE_LEN);
            result[MAX_VALUE_LEN - 1] = '\0';
            return 0;
        }
    }
    return -1;
}

int del(const char *key) {
    for (int i = 0; i < MAX_ENTRIES; i++) {
        if (store[i].in_use && strcmp(store[i].key, key) == 0) {
            store[i].in_use = 0;
            return 0;
        }
    }
    return -1;
}

int closeStore() {
    return 0;
}