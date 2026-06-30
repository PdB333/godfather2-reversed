// FUNC_NAME: TNLConnection::TNLConnection
void __thiscall TNLConnection::TNLConnection(void)
{
    // in_EAX is 'this' (implicit __thiscall)
    TNLConnection* thisPtr = this; // Use this directly

    // Get pointer from offset +0x0C of 'this' (if not null)
    void* somePtr = (this != 0) ? *(void**)((int)this + 0x0C) : 0;

    // Initialize fields (offsets relative to this)
    *(int*)((int)thisPtr + 0x04) = 0;   // +0x04: some counter/state
    *(int*)((int)thisPtr + 0x08) = 0;   // +0x08: another counter
    *(int*)((int)thisPtr + 0x10) = 1;   // +0x10: flag or count
    *(int*)((int)thisPtr + 0x0C) = 1;   // +0x0C: overwritten? Note: above we got from +0x0C, but now we set it. This is a field.
    *(void**)(thisPtr) = &PTR_LAB_00e317dc; // +0x00: first vtable (base class)
    *(int*)((int)thisPtr + 0x18) = 0;   // +0x18: null pointer or 0
    FUN_00452df0(somePtr);               // Call some initializer with the pointer
    *(int*)((int)thisPtr + 0x24) = 1;   // +0x24: another flag
    *(void**)(thisPtr) = &PTR_LAB_00e335b0; // +0x00: overwrite vtable (derived class)
    *(void**)((int)thisPtr + 0x28) = &PTR_LAB_00e33620; // +0x28: second vtable or interface pointer
    *(void**)((int)thisPtr + 0x30) = &LAB_00482410; // +0x30: function pointer (callback?)
    *(int*)((int)thisPtr + 0x34) = 0;   // +0x34: null
    // Self-reference: field at +0x14 points to address of field at +0x28
    *(void**)((int)thisPtr + 0x14) = (void*)((int)thisPtr + 0x28);
    return;
}