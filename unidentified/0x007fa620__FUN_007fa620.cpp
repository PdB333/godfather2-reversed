// FUNC_NAME: SomeClass::checkMask
// Address: 0x007fa620
// Role: Checks a capability flag via vtable call; returns the mask if the capability is active, otherwise 0.
// Decompiled from Ghidra: calls vtable[4] (offset 0x10) with mask and a dummy output pointer.
uint __thiscall SomeClass::checkMask(SomeClass* this, uint mask) {
    int dummy = 0; // Unused output parameter, initialized to 0.
    // vtable[4] signature: char (__thiscall*)(SomeClass*, uint, int*)
    char result = ((char (__thiscall*)(SomeClass*, uint, int*))(*(void***)this)[4])(this, mask, &dummy);
    // If result is non-zero, return the mask; otherwise return 0.
    return (result != 0) ? mask : 0;
}