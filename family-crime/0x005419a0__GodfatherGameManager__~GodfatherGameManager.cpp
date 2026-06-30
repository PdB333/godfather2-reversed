// FUNC_NAME: GodfatherGameManager::~GodfatherGameManager
void __fastcall GodfatherGameManager::destructor(GodfatherGameManager* this) {
    // Set vtable pointers for multiple inheritance (restore most-derived class vtable during destruction)
    this->vtable = (void*)&VTable_GodfatherGameManager;              // +0x00 primary vtable
    *(void**)((uintptr_t)this + 0x3C) = &VTable_Interface2;         // +0x3C secondary vtable
    *(void**)((uintptr_t)this + 0x48) = &VTable_Interface3;         // +0x48
    *(void**)((uintptr_t)this + 0x50) = &VTable_Interface4;         // +0x50
    *(void**)((uintptr_t)this + 0x54) = &VTable_Interface5;         // +0x54
    *(void**)((uintptr_t)this + 0x58) = &VTable_Interface6;         // +0x58

    // Engine-specific debug/lock call (likely entering a critical section)
    EngineDebugLock(&DAT_0120e93c);

    // If there is an existing sub-object at offset 0x260, release it
    if (this->subObject1 != nullptr) {                               // +0x260
        ReleaseSubObject1();                                         // global cleanup
        // Call virtual function at vtable offset 8 on object at offset 0x190
        void* obj = *(void**)((uintptr_t)this + 0x190);             // +0x190
        (*(void(__fastcall**)(void*, uint32_t))((*(uintptr_t*)obj) + 8))(obj, 0);
    }

    // If there is a second sub-object at offset 0x264, call its Release(1) and zero pointer
    if (this->subObject2 != nullptr) {                               // +0x264
        void* obj2 = this->subObject2;
        // Call virtual function at vtable offset 0x10 (Release with argument 1)
        (*(void(__fastcall**)(void*, uint32_t))((*(uintptr_t*)obj2) + 0x10))(obj2, 1);
        this->subObject2 = nullptr;
    }

    // Final static cleanup functions
    CleanupResourceManager();                                        // FUN_00562030
    CleanupEngineSubsystem();                                        // FUN_0046ea20
}