// FUNC_NAME: UnknownClass::constructor
void __thiscall UnknownClass::constructor(int* thisPtr, undefined4 param2, undefined8 param3, undefined8 param4, undefined4 param5, undefined8 param6, undefined4 param7)
{
    // Dereference thisPtr to get the actual object address (handle-like pattern)
    int* objectPtr = *thisPtr;

    // Set vtable pointer at offset +0x14 to a new vtable (PTR_FUN_01124f94)
    *(void**)(objectPtr + 0x14) = &PTR_FUN_01124f94;

    // Increment the vtable pointer by 4 bytes (likely to skip first entry or adjust for some reason)
    *(int**)(objectPtr + 0x14) = *(int**)(objectPtr + 0x14) + 1;

    // Call base class constructor or initialization function with remaining parameters
    FUN_00503410(param2, param3, param4, param5, param6, param7);
}