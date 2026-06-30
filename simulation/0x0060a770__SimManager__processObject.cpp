// FUNC_NAME: SimManager::processObject
void SimManager::processObject(int objectIndex, int param, char flag)
{
    if (param == 0) {
        return;
    }
    // Global table: array of 16-byte entries, first member is pointer to object
    // Table base address: 0x011eb8f4
    void* const* tableEntry = reinterpret_cast<void* const*>(0x011eb8f4 + objectIndex * 0x10);
    void* object = *tableEntry;
    if (object != 0) {
        // Offset 0x34 in object holds a function pointer ( __thiscall )
        void (*callback)(void*, int, int, char) = 
            *reinterpret_cast<void (**)(void*, int, int, char)>(static_cast<char*>(object) + 0x34);
        // Global constant passed as second argument (0x01205750)
        callback(object, 0x01205750, param, flag);
    }
}