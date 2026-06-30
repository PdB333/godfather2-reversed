// FUNC_NAME: GameManager::initRandomPool
int __thiscall GameManager::initRandomPool(void) {
    uint8_t *buffer = (uint8_t *)_calloc(4, 0x40); // 4 * 64 bytes pool
    if (buffer == nullptr) {
        return -2;
    }

    int loopCounter = 0;          // local_10
    int poolSize = 0x40;          // local_c – unused, maybe intended for loop limit
    int flags = 0;                // local_8 – unused

    int initResult = FUN_00665ce0(); // some initialization check
    if (initResult == 0) {
        int index = 0;
        while (loopCounter != 0) { // never enters loop because loopCounter is 0
            *(uint8_t *)(index + (int)this) = *buffer; // copy first byte of pool to this
            index++;
            int randStatus = FUN_00666300(&loopCounter, 8, &loopCounter, 0); // seed loopCounter with random?
            if (randStatus != 0) {
                FUN_00665b40(); // cleanup
                return randStatus;
            }
        }
        FUN_0066bb10(); // finalization
        FUN_00665b40(); // cleanup
        initResult = 0;
    }
    return initResult;
}