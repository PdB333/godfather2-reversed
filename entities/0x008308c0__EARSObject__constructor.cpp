// FUNC_NAME: EARSObject::constructor
undefined4* __thiscall EARSObject::constructor(EARSObject* this, byte allocFlag)
{
    int* allocPtr;
    
    // Set base vtable pointer at offset +0x00
    *(void**)this = (void*)&PTR_FUN_00d73790;
    // Call base class constructor (likely initializes base members)
    baseClassConstructor(); // FUN_0082a3c0
    // Set secondary vtable pointer at offset +0x30 (0xc words)
    *(void**)((uint8_t*)this + 0x30) = (void*)&PTR_LAB_00e32854;
    // Additional initialization (maybe sets up other fields)
    secondaryInit(); // FUN_00821f60
    if ((allocFlag & 1) != 0) {
        // Allocate memory (e.g., operator new or pool allocator)
        allocPtr = (int*)allocator(); // FUN_009c8f80
        // Call a second vtable function (offset +4) on the allocated block,
        // passing this pointer and size 0x100 (possibly a placement new or copy constructor)
        (**(code**)(*allocPtr + 4))(this, 0x100);
    }
    return this;
}