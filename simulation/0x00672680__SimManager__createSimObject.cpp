// FUNC_NAME: SimManager::createSimObject
int SimManager::createSimObject(void) {
    int newObject = 0;
    this->m_errorCode = 0; // +0x00: reset error

    int handle = acquireHandle(); // FUN_00672e60
    if (this->m_errorCode == 0) {
        this->m_errorCode = 0; // redundant reset
        int ready = isSystemReady(); // FUN_00673070
        if (ready != 0) {
            allocateObject(&newObject); // FUN_00672630
            if (newObject != 0) {
                *(int *)(newObject + 0x28) = handle; // +0x28: object handle
                *(int *)(newObject + 0x2c) = 0;      // +0x2c: flags
                *(int *)(newObject + 0x30) = 0;      // +0x30: timer
                return newObject;
            }
        }
        this->m_errorCode = 0x2718; // error code: timeout / creation failure
    }
    return 0;
}
