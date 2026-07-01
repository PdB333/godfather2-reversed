// FUNC_NAME: SomeManager::getCurrentEntry
int* SomeManager::getCurrentEntry()
{
    // Return a pointer to an element in an array starting at offset 0x2e2c
    // Each element is 0x10 (16) bytes.
    // The index is stored at offset 0x3120 in this object.
    return reinterpret_cast<int*>(
        reinterpret_cast<char*>(this) + 0x2e2c +
        *(reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x3120)) * 0x10
    );
}