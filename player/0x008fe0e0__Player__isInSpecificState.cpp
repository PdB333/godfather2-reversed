// FUNC_NAME: Player::isInSpecificState
bool __fastcall Player::isInSpecificState() {
    // Offset 0xC8 (200) is likely a pointer to a sub-object or state component
    int subObjPtr = *(int*)((char*)this + 0xC8);
    int adjustedPtr;
    if (subObjPtr == 0) {
        adjustedPtr = 0;
    } else {
        adjustedPtr = subObjPtr - 0x48; // Subtract 72 bytes to get parent structure
    }
    // FUN_008c6d50 performs a conversion/cast and returns a pointer to a type info structure
    int* result = (int*)FUN_008c6d50(adjustedPtr);
    if (result != nullptr) {
        // Check type ID at offset +4 (likely an enum for state or type)
        return result[1] == 7;
    }
    return false;
}