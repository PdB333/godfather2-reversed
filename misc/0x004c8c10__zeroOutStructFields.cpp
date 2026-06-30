// FUNC_NAME: zeroOutStructFields
void __thiscall zeroOutStructFields(void *thisPtr) {
    // +0x00: first 4-byte field
    *(uint32_t *)thisPtr = 0;
    // +0x04: second 4-byte field
    *(uint32_t *)((uint8_t *)thisPtr + 4) = 0;
    // +0x10..0xAF: 20 blocks of 8 bytes each (likely an array of uint64)
    *(uint64_t *)((uint8_t *)thisPtr + 0x10) = 0;
    *(uint64_t *)((uint8_t *)thisPtr + 0x18) = 0;
    *(uint64_t *)((uint8_t *)thisPtr + 0x20) = 0;
    *(uint64_t *)((uint8_t *)thisPtr + 0x28) = 0;
    *(uint64_t *)((uint8_t *)thisPtr + 0x30) = 0;
    *(uint64_t *)((uint8_t *)thisPtr + 0x38) = 0;
    *(uint64_t *)((uint8_t *)thisPtr + 0x40) = 0;
    *(uint64_t *)((uint8_t *)thisPtr + 0x48) = 0;
    *(uint64_t *)((uint8_t *)thisPtr + 0x50) = 0;
    *(uint64_t *)((uint8_t *)thisPtr + 0x58) = 0;
    *(uint64_t *)((uint8_t *)thisPtr + 0x60) = 0;
    *(uint64_t *)((uint8_t *)thisPtr + 0x68) = 0;
    *(uint64_t *)((uint8_t *)thisPtr + 0x70) = 0;
    *(uint64_t *)((uint8_t *)thisPtr + 0x78) = 0;
    *(uint64_t *)((uint8_t *)thisPtr + 0x80) = 0;
    *(uint64_t *)((uint8_t *)thisPtr + 0x88) = 0;
    *(uint64_t *)((uint8_t *)thisPtr +0x90) = 0;
    *(uint64_t *)((uint8_t *)thisPtr +0x98) = 0;
    *(uint64_t *)((uint8_t *)thisPtr +0xa0) = 0;
    *(uint64_t *)((uint8_t *)thisPtr +0xa8) = 0;
}