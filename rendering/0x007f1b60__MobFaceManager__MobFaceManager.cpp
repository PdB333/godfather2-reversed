// FUNC_NAME: MobFaceManager::MobFaceManager
// Address: 0x007f1b60
// Constructor for MobFaceManager. Sets up three vtable-like pointers, initializes a sub‑object at offset +0x60,
// and calls a global initialization routine. The parameter `flags` bit 0 controls optional deallocation (likely a debug path).

extern void* PTR_FUN_00d700ac;    // main vtable
extern void* PTR_LAB_00d7009c;    // interface vtable #1
extern void* PTR_LAB_00d70098;    // interface vtable #2

struct MobFaceManager
{
    void** vtable;               // +0x00
    uint8 pad_0x04[0x38];        // +0x04 – +0x3B
    void** interfaceVtable1;     // +0x3C
    void** interfaceVtable2;     // +0x48
    uint8 pad_0x4C[0x14];        // +0x4C – +0x5F
    // sub‑object of size 0x8 at offset +0x60
    void* subObject0;            // +0x60
    void* subObject1;            // +0x64
};

// Helper functions (inferred from Ghidra)
void __thiscall FUN_004086d0(void*);          // sub‑object constructor part 1
void __thiscall FUN_00408310(void*);          // sub‑object constructor part 2
void __cdecl    FUN_0046c640();               // global one‑time initializer
void __cdecl    FUN_0043b960(void*, uint size); // operator delete (size)

MobFaceManager* __thiscall MobFaceManager::MobFaceManager(MobFaceManager* this, byte flags)
{
    // Set primary vtable (class vtable)
    this->vtable = (void**)&PTR_FUN_00d700ac;
    // Set two interface vtables
    this->interfaceVtable1 = (void**)&PTR_LAB_00d7009c; // +0x3C
    this->interfaceVtable2 = (void**)&PTR_LAB_00d70098; // +0x48

    // Construct embedded sub‑object at offset +0x60
    void* subObj = (void*)(this + 0x18); // pointer arithmetic gives byte offset 0x60
    FUN_004086d0(subObj);
    FUN_00408310(subObj);

    // Global engine initialisation (e.g. MemoryManager::init)
    FUN_0046c640();

    // If the `flags` low bit is set, deallocate the entire object
    if ((flags & 1) != 0)
    {
        FUN_0043b960(this, 0x68); // total size of the object
    }

    return this;
}