// FUNC_NAME: EARSObject::getOwner
int __thiscall EARSObject::getOwner(int this) {
    // Check if pointer to owner's embedded field exists at +0x1c
    if (*(int*)(this + 0x1c) != 0) {
        // The pointer at +0x1c points to a field 0x48 bytes into the owner structure,
        // so subtract 0x48 to get the owner's base address.
        return *(int*)(this + 0x1c) - 0x48;
    }
    return 0;
}