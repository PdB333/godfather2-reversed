// FUNC_NAME: GhostUpdatePool::initialize
void __thiscall GhostUpdatePool::initialize(uint count) {
    // this = ESI, count = EDI (unaff_EDI)
    // Global constant likely a size or sentinel value, e.g., buffer size
    const uint kDefaultSize = DAT_00e35654; // +0x0C constant

    // Initialize first buffer (inner structure) - offset +0x00 points to a small header
    this->innerBuffer = (InnerHeader*)FUN_009c8e50(0xC); // size 12 bytes
    if (this->innerBuffer == NULL) {
        this->innerBuffer = NULL;
    } else {
        uint arraySize = (count + 1) * 4; // Array of 32-bit values, one extra slot
        this->innerBuffer->firstArray = (uint*)FUN_009c8e80(arraySize);
    }

    // Store the inner buffer pointer at offset 0
    this->innerBufferPtr = this->innerBuffer; // Actually *this is the pointer, but we treat as field

    // Zero out the first array (count+1 elements)
    uint* arr = this->innerBuffer->firstArray;
    for (uint i = 0; i <= count; i++) {
        arr[i] = 0;
    }

    // Allocate second array (same size as first)
    uint arraySize2 = (count + 1) * 4;
    this->secondArray = (uint*)FUN_009c8e80(arraySize2);

    // Note: other fields: this->field4 = 0; this->count = count; this->constant = kDefaultSize; this->field16 = 0;
    // But these are already set in the decompiled code before loops.
    // We'll keep them as assignments:
    this->field4 = 0;          // +0x04
    this->count = count;       // +0x08
    this->constant = kDefaultSize; // +0x0C
    this->field16 = 0;         // +0x10
}