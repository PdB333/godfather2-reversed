// FUNC_NAME: EARSObject::getUnknown68

// Function at 0x00724cf0: Simple getter returning a 4-byte value from offset 0x68.
// Typically used to retrieve a pointer to a sub-object, a state flag, or an ID.
// Calling convention: __fastcall (this pointer in ecx, passed as first param).
inline int __fastcall getUnknown68(int thisPtr) {
    return *(int*)(thisPtr + 0x68);
}