// FUNC_NAME: UnknownClass::getComponentPtr
int __thiscall UnknownClass::getComponentPtr(char index) {
    // Returns pointer to element at offset 0x150 in the object
    // Each element is 8 bytes; index is the slot index
    return reinterpret_cast<int>(this) + 0x150 + index * 8;
}