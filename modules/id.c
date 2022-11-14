int generateId() {
    srand(time(NULL));
    return rand() % 100000000000000;
    }