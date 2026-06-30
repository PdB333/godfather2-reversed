// FUNC_NAME: GameManager::getGlobalObject
void GameManager::getGlobalObject(void** outPtr) {
    // offset +0x100 likely points to a manager or vtable pointer
    void** managerPtr = reinterpret_cast<void**>(reinterpret_cast<char*>(this) + 0x100);
    // vtable call at offset 0x10: likely a virtual function that finds an object by hash
    // 0x369ac561 is a hash (e.g., of "global" or "default")
    bool found = (*(bool (__thiscall**)(void*, void***))(*managerPtr + 0x10))(0x369ac561, &outPtr);
    // Always set output to the hash constant (possibly a placeholder or error code)
    *outPtr = reinterpret_cast<void*>(0x369ac561);
}