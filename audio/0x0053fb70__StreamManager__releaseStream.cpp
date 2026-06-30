// FUNC_NAME: StreamManager::releaseStream
void __thiscall StreamManager::releaseStream(void) {
    // +0x58: pointer to a stream buffer or output object
    void* streamBuffer = *(void**)(this + 0x58);
    FUN_009e61e0(streamBuffer); // likely a release or cleanup call
    if (streamBuffer != NULL) {
        // virtual function at index 0 (release with arg 1)
        (*(void(__thiscall**)(void*, int))streamBuffer)(streamBuffer, 1);
    }

    // +0x54: reference-counted object (vtable at offset 0)
    RefCountedObject* refObj = *(RefCountedObject**)(this + 0x54);
    *(void**)(this + 0x58) = NULL;

    if (refObj != NULL && *(short*)(refObj + 2) != 0) {
        // decrement reference count at +0x6
        *(short*)((int)refObj + 6) = *(short*)((int)refObj + 6) - 1;
        if (*(short*)((int)refObj + 6) == 0) {
            // virtual release when ref count reaches 0
            (*(void(__thiscall**)(RefCountedObject*, int))refObj)(refObj, 1);
        }
    }

    // +0x28 and +0x2c: conditional cleanup flags
    if (*(char*)(this + 0x28) != 0 && *(int*)(this + 0x2c) != 0) {
        FUN_00540390(); // additional cleanup
    }

    // +0x24: another reference-counted object
    RefCountedObject* anotherRef = *(RefCountedObject**)(this + 0x24);
    if (anotherRef != NULL && *(short*)(anotherRef + 2) != 0) {
        *(short*)((int)anotherRef + 6) = *(short*)((int)anotherRef + 6) - 1;
        if (*(short*)((int)anotherRef + 6) == 0) {
            (*(void(__thiscall**)(RefCountedObject*, int))anotherRef)(anotherRef, 1);
        }
    }
    *(void**)(this + 0x24) = NULL;

    // +0x10: interface object with vtable at +0x8 (reset with two zeros)
    void* intfObj = *(void**)(this + 0x10);
    (*(void(__thiscall**)(void*, int, int))((*(int**)intfObj) + 8))(intfObj, 0, 0);

    // +0x14: handle used with TLS and audio stream function
    int handle = *(int*)(this + 0x14);
    TlsGetValue(*(DWORD*)(DAT_01139810));
    FUN_00aa28e0(handle);
    FUN_00c6ed40();

    // Release interface object if present
    if (intfObj != NULL) {
        // virtual at +0x10 (release with arg 1)
        (*(void(__thiscall**)(void*, int))((*(int**)intfObj) + 16))(intfObj, 1);
    }
}