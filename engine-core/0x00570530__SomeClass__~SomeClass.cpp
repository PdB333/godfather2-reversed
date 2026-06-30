// FUNC_NAME: SomeClass::~SomeClass
// Function address: 0x00570530
// Identified as destructor that calls base destructor (vtable[0]) then frees four member pointers using a global memory manager.

// Forward declaration: global memory manager (likely a singleton with vtable)
struct MemoryManager;
extern MemoryManager* g_pMemoryManager; // DAT_0120556c points to this

// The destructor is __thiscall, uses "this" from ECX (here ESI in decompiled)
void __thiscall SomeClass::~SomeClass(void)
{
    // Call base virtual destructor at vtable offset 0 with argument 0
    reinterpret_cast<void(__thiscall*)(int)>(*(uintptr_t*)this)(0);

    // Free member at offset 0xA0 (index 0x28)
    if (*(void**)((uintptr_t)this + 0xA0) != nullptr) {
        // Call memory manager's release function (vtable[1]) with object and flag 0
        reinterpret_cast<void(__fastcall*)(void*, int)>(
            *(uintptr_t*)(*(uintptr_t*)g_pMemoryManager + 4)
        )(*(void**)((uintptr_t)this + 0xA0), 0);
        *(void**)((uintptr_t)this + 0xA0) = nullptr;
    }

    // Free member at offset 0xA4 (index 0x29)
    if (*(void**)((uintptr_t)this + 0xA4) != nullptr) {
        reinterpret_cast<void(__fastcall*)(void*, int)>(
            *(uintptr_t*)(*(uintptr_t*)g_pMemoryManager + 4)
        )(*(void**)((uintptr_t)this + 0xA4), 0);
        *(void**)((uintptr_t)this + 0xA4) = nullptr;
    }

    // Free member at offset 0x128 (index 0x4a)
    if (*(void**)((uintptr_t)this + 0x128) != nullptr) {
        reinterpret_cast<void(__fastcall*)(void*, int)>(
            *(uintptr_t*)(*(uintptr_t*)g_pMemoryManager + 4)
        )(*(void**)((uintptr_t)this + 0x128), 0);
        *(void**)((uintptr_t)this + 0x128) = nullptr;
    }

    // Free member at offset 0xB4 (index 0x2d)
    if (*(void**)((uintptr_t)this + 0xB4) != nullptr) {
        reinterpret_cast<void(__fastcall*)(void*, int)>(
            *(uintptr_t*)(*(uintptr_t*)g_pMemoryManager + 4)
        )(*(void**)((uintptr_t)this + 0xB4), 0);
        *(void**)((uintptr_t)this + 0xB4) = nullptr;
    }
}