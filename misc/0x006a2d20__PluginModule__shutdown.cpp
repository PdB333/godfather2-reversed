// FUNC_NAME: PluginModule::shutdown
// Address: 0x006a2d20
// Role: Unloads a dynamically loaded module (DLL) and releases resources.
// Structure offsets: dllHandle +0x90, refCount +0x94, releaseCallback +0x98,
//                    otherCallback1 +0x9C, otherCallback2 +0xA0, otherCallback3 +0xA4

extern bool __fastcall canReleaseModule(void); // FUN_006a2950

void __fastcall PluginModule::shutdown(void* thisPtr)
{
    // +0x90: HMODULE dllHandle
    // +0x98: void (*releaseCallback)()
    int* DllHandle = (int*)((char*)thisPtr + 0x90);
    void** ReleaseCallback = (void**)((char*)thisPtr + 0x98);
    // +0x94: int refCount
    // +0x9C, +0xA0, +0xA4: other callbacks/state

    if (canReleaseModule()) {
        if (*ReleaseCallback != nullptr) {
            (*(void (**)())*ReleaseCallback)();
        }
    }

    FreeLibrary((HMODULE)*DllHandle);
    *DllHandle = 0;                 // zero dllHandle
    *(int*)((char*)thisPtr + 0x94) = 0; // zero refCount
    *ReleaseCallback = 0;           // zero releaseCallback
    *(void**)((char*)thisPtr + 0x9C) = 0; // zero otherCallback1
    *(void**)((char*)thisPtr + 0xA0) = 0; // zero otherCallback2
    *(void**)((char*)thisPtr + 0xA4) = 0; // zero otherCallback3
}