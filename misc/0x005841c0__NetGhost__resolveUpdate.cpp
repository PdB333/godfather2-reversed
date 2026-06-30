// FUNC_NAME: NetGhost::resolveUpdate
void __thiscall NetGhost::resolveUpdate(NetGhost* param_1, NetGhost* param_2) {
    char cVar1;
    NetGhost* destObject;
    NetGhost* srcObject;
    void* destData;
    void* srcData;
    int i;

    // Interpret param_1 and param_2 as sources; this (in_EAX) is the destination
    cVar1 = *param_2->statusPtr;
    if (*param_1->statusPtr == 0x02) {
        // Source 1 is valid
        *this->statusPtr = 0x02;
        if (cVar1 == 0x02) {
            // Both sources valid – conflict, handle externally
            FUN_00582b70();
            return;
        }
        srcObject = param_1;
    } else {
        if (cVar1 != 0x02) {
            // No valid source
            *this->statusPtr = 0x00;
            return;
        }
        // Source 2 is valid
        *this->statusPtr = 0x02;
        srcObject = param_2;
    }

    // Copy 32 bytes from source data to destination data
    destData = this->dataPtr;
    srcData = srcObject->dataPtr;
    for (i = 0; i < 8; i++) {
        ((unsigned int*)destData)[i] = ((unsigned int*)srcData)[i];
    }
}