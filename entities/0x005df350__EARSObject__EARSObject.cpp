// FUNC_NAME: EARSObject::EARSObject
// Function at 0x005df350 - Constructor for base EARSObject
// Sets vtable and calls base initializer, handles allocation flag

unsigned int* __thiscall EARSObject::EARSObject(unsigned int* thisPtr, byte constructorFlag)
{
    // Set vtable pointer (offset +0x00)
    *thisPtr = &PTR_FUN_00e3f2e8; // vtable for EARSObject

    // Call base class initializer (likely EAObject::EAObject or similar)
    FUN_004de130();

    // If object was heap-allocated (bit0 set), perform additional cleanup/deallocation
    if ((constructorFlag & 1) != 0) {
        FUN_009c8eb0(thisPtr); // likely destructor or operator delete for heap allocation
    }

    return thisPtr;
}