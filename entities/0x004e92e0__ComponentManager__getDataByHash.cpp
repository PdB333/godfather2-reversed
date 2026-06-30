// FUNC_NAME: ComponentManager::getDataByHash
// Function address: 0x004e92e0
// Retrieves a value from a component identified by a hash constant.
// Calls virtual method at vtable+0x10 (index 4) with hash and output pointer.
// On success, returns the uint32 at offset 0x218 from the retrieved pointer.

__thiscall uint32 ComponentManager::getDataByHash(int* thisPtr) {
    uint32 result = 0;
    bool found = (**(bool (__thiscall**)(int*, uint32, uint32*))(*(uint32*)thisPtr + 0x10))(thisPtr, 0xae986323, &result);
    if (found) {
        return *(uint32*)(result + 0x218);
    }
    return 0;
}