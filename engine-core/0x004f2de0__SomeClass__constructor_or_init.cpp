// FUNC_NAME: SomeClass::constructor_or_init
void SomeClass::constructor_or_init(char *param_1) {
    // Call base class constructor/initializer
    FUN_00533cc0();

    // Set vtable pointer (first field of this object)
    *reinterpret_cast<int**>(this) = &PTR_FUN_00e375e8;

    // Check flag at offset 0xD in an associated object (EDI in asm) 
    if (*(reinterpret_cast<char*>(unaff_EDI) + 0xD) == '\0') {
        // Copy string from param_1 into buffer at this+0x28
        // Original code uses a twist: dest = (char*)this + 0x28 - (int)param_1 + index
        // Likely a decompiler artifact; assuming simple string copy to fixed offset
        char *dest = reinterpret_cast<char*>(this) + 0x28;
        char *src = param_1;
        for (char c = *src; c != '\0'; c = *++src) {
            *dest++ = c;
        }
        *dest = '\0';

        // Copy a DWORD from source string at offset 0x20 into this+0x24 (unaff_ESI[9] = field at +0x24)
        reinterpret_cast<int*>(this)[9] = *reinterpret_cast<int*>(param_1 + 0x20);
    }
}