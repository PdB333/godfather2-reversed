// FUNC_NAME: BitArray::allocate

// Reconstructed from 0x00582470 - Allocates a bitset struct header and zero-initialized data array
// The class uses a virtual memory allocator (vtable[0]) for both the header and the bit storage.

struct BitArrayHeader {
    uint32_t* data;  // +0x00: pointer to allocated bit array
    uint32_t size;   // +0x04: number of bits requested
};

BitArrayHeader* __thiscall BitArray::allocate(uint32_t numBits)
{
    uint32_t* bitData;
    BitArrayHeader* header;
    uint32_t wordCount;
    uint32_t* curWord;
    uint32_t byteSize;

    // Locals initialized to 0 (used as dummy argument for allocator)
    uint32_t dummy = 0;

    // Number of 32-bit words needed to store numBits
    wordCount = (numBits + 31) >> 5;

    // Allocate memory for bit data (size = wordCount * 4 bytes)
    byteSize = wordCount * 4;
    bitData = (uint32_t*)(this->vtable[0])(byteSize, &dummy);

    // Clear dummy for second call (allocation header)
    dummy = 0;

    // Allocate 8-byte header structure
    header = (BitArrayHeader*)(this->vtable[0])(8, &dummy);
    if (header == nullptr) {
        return nullptr;
    }

    // Fill header
    header->data = bitData;
    header->size = numBits;

    // Zero‑initialize the bit data words
    curWord = bitData;
    for (uint32_t i = 0; i < wordCount; ++i) {
        *curWord++ = 0;
    }

    return header;
}