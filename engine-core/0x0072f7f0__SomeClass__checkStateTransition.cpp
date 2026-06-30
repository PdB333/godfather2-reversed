// FUNC_NAME: SomeClass::checkStateTransition
bool __thiscall SomeClass::checkStateTransition(int thisPtr, int* interfacePtr) {
    // interfacePtr points to a pointer to an object (likely a manager or factory) 
    // that has a virtual function table. The function at vtable+0x10 (index 4) 
    // expects a hash (0x383225a1) and a pointer to a pointer, and returns bool.
    // This is likely a component existence check (e.g., for combat system).
    if (interfacePtr == nullptr) {
        return false;
    }

    int vtable = *interfacePtr;
    // Temporarily set interfacePtr to null, then pass its address to the function.
    // Decompiler artifact? The function may modify it, but we ignore the output.
    interfacePtr = nullptr;
    bool componentExists = ((bool (*)(int, int**))(*(int**)(vtable + 4))[4])(0x383225a1, &interfacePtr);
    if (!componentExists) {
        return false;
    }

    // unaff_EBX is an implicit parameter passed in the EBX register (set by caller).
    // It holds a pointer to another entity (likely this object's target).
    int otherEntity = (int)unaff_EBX; // from register
    if (otherEntity == 0) {
        return false;
    }

    // Check flags at offset 0x8e6 (byte, bit 0) on both this and the other entity.
    // If the other entity has bit 0 set and this entity has it clear, return true.
    bool otherHasFlag = (*(unsigned char*)(otherEntity + 0x8e6) & 1) != 0;
    bool thisHasFlag = (*(unsigned char*)(thisPtr + 0x8e6) & 1) != 0;
    if (otherHasFlag && !thisHasFlag) {
        return true; // Transition allowed
    }

    return false; // Not allowed
}