// FUNC_NAME: ComponentList::findComponentByValue
// Function address: 0x00599aa0
// Role: Iterates over a list of component indices (stored as bytes) and returns the first component whose virtual function at vtable+3 returns the given value (param_2). Skips components with status -2.

int* ComponentList::findComponentByValue(int param_2)
{
    int* componentPtr;
    int status;
    int idx;
    uint byteIdx;

    idx = 0;
    // m_componentCount at +0x58
    if (*(byte*)(this + 0x58) != 0) {
        do {
            byteIdx = (uint)*(byte*)(this + 0x59 + idx); // byte index into component table
            // m_componentManager at +0x1BC
            int* mgr = *(int**)(this + 0x1BC);
            // Check status array at mgr+0x18 (array of ints keyed by byteIdx)
            status = *(int*)(*(int*)(mgr + 0x18) + byteIdx * 4);
            if (status != -2) {
                // Call global vtable function (slot 1) - likely preload/validate
                (**(code**)(*DAT_01205590 + 4))();
            }
            // Get component pointer from mgr's component array at +0x14
            componentPtr = *(int**)(*(int*)(mgr + 0x14) + byteIdx * 4);
            // Call component's vtable function at offset 0xC (slot 3) - returns a comparison value
            int cmpVal = (**(code**)(*componentPtr + 0xC))();
            if (cmpVal == param_2) {
                return componentPtr;
            }
            idx++;
        } while (idx < (int)(uint)*(byte*)(this + 0x58));
    }
    return nullptr;
}