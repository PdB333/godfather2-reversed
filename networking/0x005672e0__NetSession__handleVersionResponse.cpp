// FUNC_NAME: NetSession::handleVersionResponse
void __thiscall NetSession::handleVersionResponse(void* thisPtr, void* packetData) {
    char* versionStr;
    char cVar2;
    undefined4 errorCode;
    char* pcVar4;
    char localVersionBuffer[32]; // +0x20 buffer for local version string

    if (packetData != 0) {
        cVar2 = plasmaGetTOS(); // FUN_00adc2d0 - check if TOS (Type of Service) error
        if (cVar2 != '\0') {
            errorCode = plasmaGetErrorString(); // FUN_00adc2e0
            logError(errorCode, "Plasma GetTOS returned an error"); // FUN_005676d0
            *(undefined4*)((int)thisPtr + 0x10) = 9; // state = 9 (error)
            return;
        }
        cVar2 = stringCopy("version", localVersionBuffer, 0x20); // FUN_00adc4f0 - get local version string
        if (cVar2 == '\0') {
            localVersionBuffer[0] = 0;
        }
        if (*(int*)((int)thisPtr + 0x20) != 0) { // if version string already allocated
            *(undefined4*)((int)thisPtr + 0x24) = 0; // reset length
            freeMemory(*(int*)((int)thisPtr + 0x20)); // FUN_009c8f10 - free old string
        }
        pcVar4 = *(char**)((int)packetData + 0xc); // pointer to version string in packet
        // compute length of packet version string
        char* start = pcVar4;
        pcVar4 = start + 1;
        do {
            cVar2 = *start;
            start = start + 1;
        } while (cVar2 != '\0');
        int length = (int)start - (int)pcVar4; // strlen of packet version
        *(int*)((int)thisPtr + 0x24) = length; // store length
        void* newBuffer = allocateMemory(length + 1); // FUN_009c8e80
        *(undefined4*)((int)thisPtr + 0x20) = (int)newBuffer; // store pointer
        stringCopy(&DAT_00e3a5e0, newBuffer, *(int*)((int)thisPtr + 0x24)); // copy from global version string? (DAT_00e3a5e0 likely "version" or packet version)
        *(char*)(*(int*)((int)thisPtr + 0x24) + *(int*)((int)thisPtr + 0x20)) = 0; // null-terminate
        if ((*(uint*)((int)thisPtr + 0x2c) >> 2 & 1) == 0) { // check flag bit 2
            *(char*)((int)thisPtr + 0x14) = 2; // substate = 2
            *(undefined4*)((int)thisPtr + 0x10) = 0; // state = 0 (success)
            return;
        }
        *(undefined4*)((int)thisPtr + 0x10) = 8; // state = 8 (version mismatch?)
    }
    return;
}