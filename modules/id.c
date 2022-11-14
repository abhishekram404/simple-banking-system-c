#include <time.h>
#include <stdlib.h>
#include "id.h"

int generateId() {
    srand(time(NULL));
    return rand() % 100000000000000;
}