// FUNC_NAME: UnknownClass::getDataFromMember
// Function address: 0x005c2880
// Returns a DWORD at offset 0x10 from the pointer stored at +0x4, or 0 if null.
// Field offsets: this+0x4 = pointer to some data structure
uint32_t UnknownClass::getDataFromMember() {
    void* pData = *(void**)((uint8_t*)this + 0x4);
    if (pData != nullptr) {
        return *(uint32_t*)((uint8_t*)pData + 0x10);
    }
    return 0;
}