// FUN_00433650: EARSObject::handleSlotAction

// Defined offsets from the internal data structure
#define DATA_FLAGS_OFFSET         0x3AF8
#define ACTION_ARRAY_OFFSET       0x1230
#define ACTION_ELEMENT_SIZE       0x06A0
#define SPECIAL_ACTION1_OFFSET    0x18D0
#define SPECIAL_ACTION2_OFFSET    0x2610

// Forward declaration of sub‑functions (actual addresses known)
void SubObjectInitialize(void* pSubObj, int param4, int param3, uint flags);
void DataProcess(void* pData, int param4, int param3, void* pSubObj, int value, int zero);

void __thiscall EARSObject::handleSlotAction(int param2, int param3, int param4, uint param5)
{
    // Get the internal data block pointer (offset +0x04 from this)
    void* pData = *(void**)((char*)this + 4);

    // Check bit 3 of the flags word; if set, OR 0x400 into param5
    if (((*(uint*)((char*)pData + DATA_FLAGS_OFFSET) >> 3) & 1) != 0)
    {
        param5 |= 0x400;
    }

    // Extract 3 bits from bits 11‑13 of the flags word
    uint3 bits113 = (uint3)(*(uint*)((char*)pData + DATA_FLAGS_OFFSET) >> 0xB);
    void* pSubObj = nullptr;
    uint iVar2;

    switch (param2)
    {
    case 0:
    case 5:
        // Direct call to sub‑object initializer using an array element
        SubObjectInitialize(
            (char*)pData + ACTION_ARRAY_OFFSET + param2 * ACTION_ELEMENT_SIZE,
            param4, param3, param5);
        return;

    case 1:
        pSubObj = (char*)pData + SPECIAL_ACTION1_OFFSET;
        goto checkFlag16;

    case 2:
        break;  // pSubObj stays null

    case 3:
        pSubObj = (char*)pData + SPECIAL_ACTION2_OFFSET;
        break;

    default:
        if (param2 == 1)
            goto checkFlag16;
    }

    // Normal path: compute iVar2 from the 3‑bit field shifted left by 8
    iVar2 = (uint)bits113 << 8;
    goto callDataProcess;

checkFlag16:
    if ((param5 & 0x10) == 0)
    {
        // Special path for case 1: set iVar2 to (bits113 with a 1 in the high byte)
        iVar2 = (1 << 24) | (uint)bits113;   // CONCAT31(bits113, 1)
        goto callDataProcess;
    }
    // Otherwise fall through (pSubObj set, iVar2 computed as on normal path)
    iVar2 = (uint)bits113 << 8;

callDataProcess:
    DataProcess(pData, param4, param3, pSubObj, iVar2, 0);
    return;
}