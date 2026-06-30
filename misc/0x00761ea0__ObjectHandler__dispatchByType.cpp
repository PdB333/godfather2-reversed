// FUNC_NAME: ObjectHandler::dispatchByType
void __thiscall ObjectHandler::dispatchByType(uint thisPtr, uint32_t* pOutputBuffer) {
    int typeHash = (*(int (__thiscall**)(uint32_t*))*pOutputBuffer)(pOutputBuffer);
    if (typeHash == 0x6862a74c) {
        if (*(int*)(thisPtr + 0x54) != 0) {
            releaseSubObject(*(uint32_t*)(thisPtr + 0x5c));
        }
        // Set function-pointer pairs and a type flag
        *(uint64_t*)(pOutputBuffer + 0x1e) = CONCAT44((uint32_t)&LAB_00761a60, thisPtr);
        *(uint64_t*)(pOutputBuffer + 0x20) = uStack_10;
        *(uint64_t*)(pOutputBuffer + 0x22) = CONCAT44((uint32_t)&LAB_00761aa0, (uint32_t)uStack_8);
        *(uint64_t*)(pOutputBuffer + 0x24) = CONCAT44((uint32_t)&LAB_00761a80, thisPtr);
        *(uint64_t*)(pOutputBuffer + 0x26) = uStack_10;
        *(uint64_t*)(pOutputBuffer + 0x28) = CONCAT44((uint32_t)&LAB_00761aa0, (uint32_t)uStack_8);
        pOutputBuffer[0x3c] = 2; // set type flag at offset 0xF0
        return;
    }
    if (typeHash == 0x6b4fe568) {
        uint32_t counterA = getCounterA(); // FUN_007347e0
        uint32_t counterB = getCounterB(); // FUN_0072f960
        pOutputBuffer[0x38] = counterA;
        pOutputBuffer[0x39] = counterB;
        resetComponentA((void*)(thisPtr + 0x54)); // FUN_007608a0
        resetComponentB((void*)(thisPtr + 0x60)); // FUN_00760900
        pOutputBuffer[0x29] = *(uint32_t*)(*(int*)(thisPtr + 0x70) + 0x30);
        pOutputBuffer[0x3a] |= 0x20; // set flag
        if ((*(uint32_t*)(thisPtr + 0x80) >> 4 & 1) != 0) {
            resetComponentB((void*)(thisPtr + 0x60)); // FUN_00760900
        }
    }
    return;
}