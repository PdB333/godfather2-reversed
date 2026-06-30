// FUNC_NAME: SomeClass::copyDataArray
void SomeClass::copyDataArray(const void* source, uint count) {
    uint* destArray = *(uint**)(this + 0x8); // pointer to destination array at offset +0x8
    if (destArray != 0) {
        const uint* src = (const uint*)source;
        for (uint i = 0; i < count; i++) {
            destArray[i] = src[i];
        }
    }
}