// FUNC_NAME: processGameObjectMessage
void processGameObjectMessage(int* pObject)
{
    int* pInternal;
    bool success;
    int outId = 0;
    int* outPointer = 0;

    if (pObject == 0) return;                                  // Null check
    if (*pObject != 3) return;                                 // Object type check (likely 3 = some game object)
    pInternal = (int*)pObject[1];                              // +0x04: pointer to internal data
    if (pInternal == 0) return;                                // Null check
    if ((uint)pObject[2] <= 0xF) return;                      // +0x08: size or count check (>15)
    if (*pInternal != 0xCAE87F32) return;                     // +0x00: magic signature (vtable/interface ID)
    if (pInternal[1] != 1) return;                             // +0x04: version or subtype check

    success = FUN_006a8be0(0x3596a436, &outId, &outPointer);  // Resolve object handle 0x3596a436
    if (success) {
        FUN_006a8dd0(outId, outPointer);                       // Process resolved object
    }
}