// FUNC_NAME: Serializer::readField
void __thiscall Serializer::readField(Serializer *this, CallbackFuncPtr *callbackPtr)
{
    char flagByte;
    int *nextPtr;
    int count;
    int alignmentSize;
    uint alignedOffset;
    char *fieldData;

    // Read count and alignment size from current position in buffer (+0x18)
    nextPtr = *(int **)(this + 0x18);          // current buffer pointer
    count = *nextPtr;                         // number of items (probably 4-byte each)
    *(int **)(this + 0x18) = nextPtr + 1;     // advance past count
    alignmentSize = nextPtr[1];                // alignment / size of each item
    *(int **)(this + 0x18) = nextPtr + 2;     // advance past alignment

    // Compute aligned data offset (round up to multiple of alignmentSize)
    alignedOffset = ((uint32_t)nextPtr + (uint32_t)alignmentSize + 7) & ~((uint32_t)alignmentSize - 1U);
    // Compute pointer to field data (count words of 4 bytes each from aligned offset)
    fieldData = (char *)(count * 4 + alignedOffset);
    *(char **)(this + 0x18) = fieldData;      // store new buffer position (before flag?)

    flagByte = *fieldData;                     // Read flag byte from field start
    // Align buffer pointer to next 4-byte boundary after flag byte
    *(uint32_t *)(this + 0x18) = (uint32_t)(fieldData + 4) & 0xFFFFFFFCu;

    // Call the callback function with: 
    //   high32 = count, low32 = (count ? alignedOffset : 0) ???
    //   alignmentSize, and a byte built from flagByte condition and high bits of alignedOffset
    (*(void (*)(uint64_t, int, uint32_t))*callbackPtr)(
        (uint64_t)count | ((uint64_t)(-(uint32_t)(count != 0)) & (uint64_t)alignedOffset) << 32,
        alignmentSize,
        ((uint32_t)((int3)(alignedOffset >> 8)) << 8) | (uint8_t)(flagByte != '\0'));
}