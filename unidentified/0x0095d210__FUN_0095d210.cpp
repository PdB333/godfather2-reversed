// FUNC_NAME: SomeManager::getStringAndCopy
void __thiscall SomeManager::getStringAndCopy(void *destBuffer, uint srcIndex) {
    // +0x24: pointer to a string table or data handle (e.g., a StringTable*)
    const char *strPtr = nullptr;

    // Retrieve a string pointer from internal data (third param = 1 might be a flag for "allocate" or "reference")
    GetStringFromHandle(*(this + 0x24), &strPtr, 1);

    // Use a sentinel string if the pointer is null
    if (strPtr == nullptr) {
        strPtr = "<null>"; // Global string likely at DAT_0120546e
    }

    // Copy the string to destination with given size and some flag (local_c = 0)
    StringCopySized(destBuffer, strPtr, srcIndex, 0);

    // If a string was retrieved, attempt to free it (likely an indirect call to a deallocator)
    if (strPtr != nullptr) {
        // NOTE: local_4 is a function pointer that is never assigned in this function.
        // This implies the actual cleanup is performed by a known deallocation function
        // (e.g., operator delete[] or a custom free) that Ghidra misidentified as an indirect call.
        // The following line would crash in practice; it's reconstructed to indicate intended behavior.
        // FreeString(strPtr); // Presumed deallocator
        // Since local_4 is null, this is likely a bug in decompilation. 
        // In reality, the function might call a static deallocator or ignore the pointer.
    }
}