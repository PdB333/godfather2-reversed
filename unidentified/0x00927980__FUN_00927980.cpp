// FUNC_NAME: UnknownClass::cleanupFlags
// Address: 0x00927980
// Role: Checks two flag bytes in the object and calls a release function on the address of the flag if non-zero.
// Offsets: +0x0C likely a flag or first char of a buffer; +0x19C another flag/buffer start.
// The callee FUN_00927910 is assumed to perform cleanup/release for the given buffer/flag.

void __fastcall UnknownClass::cleanupFlags(UnknownClass* this) {
    // Check if the byte at offset 0x19C is non-zero (flag or first char of a buffer)
    if (*(char*)((int)this + 0x19C) != '\0') {
        // Call release function on the address of that byte
        FUN_00927910((char*)((int)this + 0x19C));
        return;
    }
    // Otherwise check the byte at offset 0x0C
    if (*(char*)((int)this + 0x0C) != '\0') {
        FUN_00927910((char*)((int)this + 0x0C));
    }
}