// FUNC_NAME: UnknownClass::getFieldAt40
// Address: 0x00556e50
// Role: Trivial getter that returns the value at offset 0x40 (likely a pointer to a subobject or data member).
// This is a __thiscall member function.
// Offset 0x40 may correspond to a data pointer (e.g., "m_pData", "m_pOwner", etc.) in many EARS classes.

int __thiscall UnknownClass::getFieldAt40(void* thisPtr) {
    return *(int*)((int)thisPtr + 0x40);
}