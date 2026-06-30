// FUNC_NAME: lookupKeyedData

int* __fastcall lookupKeyedData(char* inputKey)
{
    int* piVar1;
    int iVar2;

    if (*inputKey == '\0') {
        // Empty key path: look at offset +0x0C for a pointer
        piVar1 = *(int**)(inputKey + 0x0C);
        // Check magic number at piVar1+6 (short) = 0x25E3
        if (*(short*)((int)piVar1 + 6) != 0x25E3) {
            // Not the expected structure – return pointer + 8 bytes
            return piVar1 + 2;
        }
        iVar2 = *piVar1;
        if (iVar2 == 0) {
            // Fallback to a static global data block
            return &DAT_0120e700;  // static global
        }
        piVar1 = (int*)piVar1[2]; // follow pointer at offset +8
    } else {
        // Non‑empty key: look at offset +0x04 for a pointer
        piVar1 = *(int**)(inputKey + 4);
        iVar2 = *piVar1;
        if (iVar2 == 0) {
            // Check and possibly initialize a global flag/block
            if ((_DAT_01223d10 & 1) == 0) {
                _DAT_01223d10 |= 1;
                DAT_01223d00 = 0;
                DAT_01223d04 = 0;
                DAT_01223d08 = 0;
                DAT_01223d0c = 0;
            }
            return &DAT_01223d00;
        }
    }
    // Calculate final result: base + offset
    return (int*)((int)piVar1 + iVar2);
}