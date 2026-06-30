// FUNC_NAME: UnknownClass::getFloatFromInterface
void UnknownClass::getFloatFromInterface(float* outResult)
{
    // param_1 is actually a pointer to a struct with:
    // +0x00: float output field
    // +0x100: pointer to an interface (COM-style) with vtable
    // The function queries the interface for a specific GUID (0x383225a1),
    // and if successful and a global object (unaff_ESI, likely a singleton) is valid,
    // it computes a float via FUN_006e3f90 and stores it in the output field.
    
    int base = (int)outResult;                     // base of the struct
    undefined4** vtablePtr = (undefined4**)(base + 0x100); // pointer to interface vtable
    
    // QueryInterface pattern
    void* interfacePtr = nullptr;
    char result = (**(code**)(*(*vtablePtr) + 0x10))(0x383225a1, &interfacePtr);
    
    if (result != 0 && unaff_ESI != 0) {
        // unaff_ESI is likely a global singleton (e.g., GameManager or SimManager)
        // with a field at +0x2888
        float computedValue = (float)FUN_006e3f90(base,
                                                   unaff_retaddr,
                                                   *(undefined4*)(unaff_ESI + 0x2888),
                                                   _DAT_00d5fa88,
                                                   DAT_00d5ccf8);
        *outResult = computedValue; // write result to the struct's float field
    } else {
        *outResult = 0.0f;
    }
}