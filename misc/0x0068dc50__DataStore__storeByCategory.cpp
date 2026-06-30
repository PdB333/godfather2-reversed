// FUNC_NAME: DataStore::storeByCategory
int __thiscall DataStore::storeByCategory(void* thisPtr, const uint8_t* source, uint32_t extra, uint32_t category) {
    uint8_t buffer[28]; // 3x8 from source + 4 from extra
    memcpy(buffer, source, 24);
    *(uint32_t*)(buffer + 24) = extra;

    if (category < 6) {
        uintptr_t sizePtr = 6;
        return FUN_0068d790((uint8_t*)thisPtr + 0x14, &sizePtr, buffer);
    }
    if (category < 0x10) {
        uintptr_t sizePtr = 0x10;
        return FUN_0068d790((uint8_t*)thisPtr + 0x29c, &sizePtr, buffer);
    }
    if (category < 0x1f) {
        uintptr_t sizePtr = 0x1f;
        return FUN_0068d790((uint8_t*)thisPtr + 0x95c, &sizePtr, buffer);
    }
    return -1;
}