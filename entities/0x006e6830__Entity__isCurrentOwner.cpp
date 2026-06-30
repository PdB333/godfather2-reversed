// FUNC_NAME: Entity::isCurrentOwner
// Function address: 0x006e6830
// Checks if the object referenced by the internal pointer (offset +0x60) matches the given object pointer,
// and that a flag at offset +0x8a (bit 0) is set. The pointer at +0x60 is adjusted by subtracting 0x48,
// likely to convert from a base class vtable pointer to the derived object address (multiple inheritance).
bool __thiscall Entity::isCurrentOwner(int thisPtr, int objectPtr)
{
    int adjustedPtr; // Derived object address from the internal pointer
    bool result;

    // +0x60: pointer to a base class subobject or vtable (null if not set)
    if (*(int*)(thisPtr + 0x60) == 0) {
        adjustedPtr = 0;
    } else {
        // Subtract 0x48 to get the actual derived object address
        adjustedPtr = *(int*)(thisPtr + 0x60) - 0x48;
    }

    // +0x8a: flag byte; bit 0 indicates the reference is active/valid
    if ((adjustedPtr != objectPtr) || ((*(byte*)(thisPtr + 0x8a) & 1) == 0)) {
        result = false;
    } else {
        result = true;
    }
    return result;
}