// FUNC_NAME: ContainerClass::getIndexFromPointer
int __thiscall ContainerClass::getIndexFromPointer(void* thisPtr, void* elementPtr)
{
    // ((elementPtr - thisPtr) - 0x180) / 0x38
    // Compute the index of an element given its pointer, assuming:
    // - The container has a header of 0x180 (384) bytes before the array
    // - Each element has size 0x38 (56) bytes
    // +0x180: header offset to start of array
    // +0x38: size of each element
    return reinterpret_cast<int>(
        (reinterpret_cast<uintptr_t>(elementPtr) - reinterpret_cast<uintptr_t>(thisPtr) - 0x180) / 0x38
    );
}