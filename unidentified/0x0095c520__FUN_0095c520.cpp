// FUNC_NAME: SomeClass::constructor
void SomeClass::constructor(void *this) {
    // Allocate 0x80 (128) bytes using custom allocator with flags 0
    void *allocatedBuffer = AllocateMemory(0x80, 0);
    // Initialize internal structure with allocated buffer
    InitializeObject(this, allocatedBuffer);
}