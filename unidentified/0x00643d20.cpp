// Function at 0x643d20: returns a pointer to internal data structure (offset +0x30)
// FUNC_NAME: getInternalDataPointer
void* getInternalDataPointer(void* objectPointer) {
    return (void*)((char*)objectPointer + 0x30);
}