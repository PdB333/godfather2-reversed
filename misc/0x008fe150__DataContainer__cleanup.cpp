// FUNC_NAME: DataContainer::cleanup
void __thiscall DataContainer::cleanup() {
    // Offset +0x78: pointer to allocated sub-object (int*)
    int** ppData = reinterpret_cast<int**>(reinterpret_cast<uintptr_t>(this) + 0x78);

    // Step 1: global release/reset with argument 0
    doGlobalCleanup(0);

    // Step 2: conditional execution – pass this if it's not the sentinel value 0x50, otherwise null
    doConditionalProcess((this != reinterpret_cast<DataContainer*>(0x50)) ? this : nullptr);

    // Step 3: free internal pointer if non‑null, then clear the member
    if (*ppData != nullptr) {
        safeRelease(ppData);          // frees *ppData and sets *ppData = nullptr
    }
}