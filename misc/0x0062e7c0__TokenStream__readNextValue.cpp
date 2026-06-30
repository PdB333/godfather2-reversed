// FUNC_NAME: TokenStream::readNextValue

bool TokenStream::readNextValue(int* this) {
    int* startPtr = *(int**)(this + 0x8);
    int* endPtr = *(int**)(this + 0xC);
    uint64_t currentToken = (uint64_t)((ulonglong)endPtr << 32) | (ulonglong)startPtr;

    // Validate current position
    if (!(startPtr <= endPtr) || (endPtr == nullptr) || (*(int*)endPtr == -1)) {
        reportError(this, 1, "value expected");
    }

    int* tokenPtr = (int*)((ulonglong)currentToken >> 32); // upper 32 bits?
    // Actually CONCAT44( lower, upper ) so tokenPtr is lower, higher is piVar1
    // But the decompiled uses uVar5 = CONCAT44(lower, upper), then piVar3 = (int*)(uVar5 >> 32), piVar1 = (int*)uVar5
    // So: piVar3 = upper, piVar1 = lower. Let me rederive.

    tokenPtr = (int*)((ulonglong)currentToken & 0xFFFFFFFF);
    int* nextPtr = (int*)((ulonglong)currentToken >> 32);

    // Check for empty or end marker
    if (!(nextPtr <= tokenPtr) || (tokenPtr == nullptr) ||
        (*tokenPtr == 0 || (*tokenPtr == 1 && *(tokenPtr + 1) == 0))) {
        char* tokenData = (char*)(tokenPtr + 2);
        if ((tokenData < nextPtr) && (tokenData != nullptr) && (*(int*)tokenData > 0)) {
            goto LAB_0062e825;
        }
        tokenData = "assertion failed!";
        do {
            logMessage(&DAT_00e3625c, tokenData);
            nextPtr = extraout_EDX; // Not defined, assume updated by log
LAB_0062e825:
            if ((nextPtr <= tokenData) || ((int*)tokenData == nullptr)) break;
            if (*(int*)tokenData == 4) {
                tokenData = (char*)(*(int*)((int)tokenData + 4) + 0x10);
            } else {
                int result = advanceToNextToken(this);
                if (result == 0) {
                    tokenData = nullptr;
                } else {
                    tokenData = (char*)(*(int*)((int)tokenData + 4) + 0x10);
                }
                if (*(uint*)(*(int*)(this + 0x10) + 0x20) <= *(uint*)(*(int*)(this + 0x10) + 0x24)) {
                    growBuffer();
                }
            }
        } while ((int*)tokenData != nullptr);
        currentToken = findString(PTR_s_string_00e2a8ac);
    }

    // Clear processed token area
    uint32_t currentLow = (uint32_t)(currentToken & 0xFFFFFFFF);
    uint32_t currentHigh = (uint32_t)(currentToken >> 32);
    if (currentHigh < currentLow + 8) {
        do {
            **(undefined4**)(this + 8) = 0;
            *(int*)(this + 8) = *(int*)(this + 8) + 8;
        } while (*(uint*)(this + 8) < *(int*)(this + 0xC) + 8);
    }

    *(int*)(this + 8) = *(int*)(this + 0xC) + 8;
    return 1;
}