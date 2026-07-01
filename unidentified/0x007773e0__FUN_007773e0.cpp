// FUNC_NAME: SomeClass::processTransitionWithAuxObject
void __thiscall SomeClass::processTransitionWithAuxObject(void) {
    // Call to an engine initialization/debug function at 0x00624d00
    unknownEngineFunction();

    // Check if aux object pointer (at this+0x70) is valid and not a sentinel (0x48)
    if ((*(int*)(this + 0x70) != 0) && (*(int*)(this + 0x70) != 0x48)) {
        int resultBuffer = 0;       // local_8
        int unused = 0;             // local_4

        // Primary object pointer at this+0x5c
        int* primaryObj = *(int**)(this + 0x5c);

        // Base pointer for the aux object: subtract 0x48 to get the owning structure's vtable
        int* auxBase;
        if (*(int*)(this + 0x70) == 0) {
            auxBase = (int*)0;
        } else {
            auxBase = (int*)(*(int*)(this + 0x70) - 0x48);
        }

        // Call virtual function at vtable+0x1f8 on aux object: (primaryObj, &resultBuffer)
        (**(code**)(*auxBase + 0x1f8))(primaryObj, &resultBuffer);

        // Recalculate auxBase (same as above) then call vtable+0x280 to get some value
        if (*(int*)(this + 0x70) == 0) {
            auxBase = (int*)0;
        } else {
            auxBase = (int*)(*(int*)(this + 0x70) - 0x48);
        }
        int returnValue = (**(code**)(*auxBase + 0x280))(&resultBuffer);

        // Call virtual function at vtable+0x14c on primary object: (returnValue, 1, 0)
        (**(code**)(*primaryObj + 0x14c))(returnValue, 1, 0);
    }
}