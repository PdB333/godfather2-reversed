// FUNC_NAME: UnknownClass::getField0xF0
// Returns the address of the field at offset 0xF0 from this object (this + 0xF0).
// In the EARS engine, this offset typically holds a pointer to a sub-component or manager.
int __fastcall getField0xF0(void* thisPtr) {
    // thisPtr + 0xF0
    return reinterpret_cast<int>(thisPtr) + 0xF0;
}