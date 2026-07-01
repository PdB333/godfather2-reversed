// FUNC_NAME: checkAnyActiveFlag
byte __thiscall checkAnyActiveFlag(void* thisPtr) {
    byte result;
    byte anyActive = 0;
    uint i;

    // Loop over first list at offset +0x10c (count)
    i = 0;
    if (*(int*)((char*)thisPtr + 0x10c) != 0) {
        do {
            result = getSomeFlag(); // FUN_006b5a30
            i++;
            anyActive = anyActive | result;
        } while (i < *(uint*)((char*)thisPtr + 0x10c));
    }

    // Loop over second list at offset +0x118 (count)
    i = 0;
    if (*(int*)((char*)thisPtr + 0x118) != 0) {
        do {
            result = getSomeFlag(); // FUN_006b5a30
            i++;
            anyActive = anyActive | result;
        } while (i < *(uint*)((char*)thisPtr + 0x118));
    }

    return anyActive;
}