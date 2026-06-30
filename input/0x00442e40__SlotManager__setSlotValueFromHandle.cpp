// FUNC_NAME: SlotManager::setSlotValueFromHandle
void SlotManager::setSlotValueFromHandle(void* handle, int value) {
    // This function is actually a small setter that uses the address of the first parameter
    // as a handle to look up a writable slot pointer via FUN_00443500.
    // The handle is passed by value on the stack; we take its address to access the pointer itself.
    // This is typical for a setter that operates on a double pointer or a handle table.
    int* slotPtr = (int*)FUN_00443500(&handle);
    if (slotPtr != nullptr) {
        *slotPtr = value;       // Write the value into the resolved slot
    }
}