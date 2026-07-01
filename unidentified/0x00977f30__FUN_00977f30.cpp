// FUNC_NAME: UnknownClass::clearAndResetContainers

void __thiscall UnknownClass::clearAndResetContainers(UnknownClass* this) {
    // Offset 0x14 holds a pointer to a container/list
    void* listPtr;
    if (this == nullptr) {
        listPtr = nullptr;
    } else {
        listPtr = reinterpret_cast<uint8_t*>(this) + 0x14;
    }
    FUN_005c0c50(listPtr, reinterpret_cast<void*>(0x009767b0)); // First clear with comparator A

    // Recompute list pointer (same offset) for second call
    if (this == nullptr) {
        listPtr = nullptr;
    } else {
        listPtr = reinterpret_cast<uint8_t*>(this) + 0x14;
    }
    FUN_005c0c50(listPtr, reinterpret_cast<void*>(0x00976800)); // Second clear with comparator B

    // Reset the list using comparator B and value 0
    if (this != nullptr) {
        FUN_005c0d50(reinterpret_cast<uint8_t*>(this) + 0x14, reinterpret_cast<void*>(0x00976800), 0);
    } else {
        FUN_005c0d50(nullptr, reinterpret_cast<void*>(0x00976800), 0);
    }
}