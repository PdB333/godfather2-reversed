// FUNC_NAME: StreamManager::~StreamManager
void __thiscall StreamManager::~StreamManager(void) {
    // Release all stream pointers (array of 14 at offset 0x88)
    // Each stream object's vtable first entry is a release function (arg = 1)
    for (int i = 0; i < 14; i++) {
        void** ppStream = (void**)(this + 0x88 + i * 4); // offsets: 0x88, 0x8c, ..., 0xbc
        if (*ppStream != nullptr) {
            // Call release through vtable
            (*(void(__thiscall**)(void*, int))(*ppStream))(*ppStream, 1);
            *ppStream = nullptr;
        }
    }

    // Destroy sub-object at offset 0x6c (likely base class part or member)
    FUN_005c22c0(this + 0x6c);

    // Restore vtable to base class (EARS::Framework::Object) at offset 0x68
    *(void***)(this + 0x68) = &PTR_LAB_00e3e74c;

    // Additional cleanup / finalize
    FUN_005c0a90();

    // Set another vtable pointer to base class at offset 0x18
    *(void***)(this + 0x18) = &PTR_LAB_00e3e74c;

    // Clear reference counting or flags
    *(int*)(this + 0x10) = 0;
    *(int*)(this + 0xC) = 0;

    // Release a dynamically allocated resource at offset 0x8
    if (*(int*)(this + 0x8) != 0) {
        // Call delete through a global memory manager vtable
        (*(void(__thiscall**)(void*, int))(*((int*)DAT_012234ec + 1) + 4))(*(void**)(this + 0x8), 0);
    }
    *(int*)(this + 0x8) = 0;

    // Final destructor step (e.g., Object::~Object)
    FUN_005c40d0();
}