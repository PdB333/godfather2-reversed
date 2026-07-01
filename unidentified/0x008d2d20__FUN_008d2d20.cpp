// FUNC_NAME: UnknownClass::getDataAtOffset78
// Address: 0x008d2d20
// Returns pointer to sub-structure or data at offset 0x78 from this.
void* UnknownClass::getDataAtOffset78() const {
    return reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(this) + 0x78);
}