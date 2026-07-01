// FUNC_NAME: BaseObject::BaseObject

extern void __stdcall initGlobalRefCounter();   // FUN_004df590 - possibly increments ref count
extern void __stdcall initSubObject(void* addr); // FUN_00408310 - initialize sub-object
extern void __stdcall registerWithGlobal(void* addr); // FUN_004086d0 - attach to global singleton
extern void __stdcall releaseSubObject(void* addr);   // FUN_004daf90 - release owned resource
extern void __stdcall finalizeConstructor();          // FUN_004083d0 - constructor epilogue

// VTable pointers from data section
extern void* g_BaseVTable;   // PTR_FUN_00d6990c
extern void* g_DerivedVTable;// PTR_FUN_00d587e0

void __fastcall BaseObject::BaseObject(BaseObject* this)
{
    int i;

    // Set base vtable
    this->vtable = &g_BaseVTable;

    // Initialize reference counter or lock (called twice)
    i = 2;
    do {
        initGlobalRefCounter();
        i--;
    } while (i != 0);

    // Clear byte at offset +0xE4 (0x39 * 4)
    *((uint8_t*)this + 0xE4) = 0;

    // Initialize sub‑objects at offsets +0x74 and +0x7C
    initSubObject((uint32_t*)this + 0x1d); // offset +0x74
    initSubObject((uint32_t*)this + 0x1f); // offset +0x7C

    // Register with global singletons
    registerWithGlobal((void*)0x0112afb0);
    registerWithGlobal((void*)0x0112afa8);

    // Release owned sub‑object if present at offset +0xE8
    if (this->subObjectPtr != NULL) {
        releaseSubObject(&this->subObjectPtr);
    }

    // Clear two smart‑pointers at offsets +0xCC and +0xC8
    int* ptr1 = (int*)((uint32_t*)this + 0x33 - 1); // +0xCC
    int* ptr2 = (int*)((uint32_t*)this + 0x33 - 2); // +0xC8
    for (i = 1; i >= 0; i--) {
        if (*ptr1 != 0) {
            *(int*)(*ptr1 + 8) = 0; // clear some field inside the pointed object
            *ptr1 = 0;
        }
        ptr1--;
    }

    // Replace vtable with derived class vtable
    this->vtable = &g_DerivedVTable;

    // Finalize construction
    finalizeConstructor();
}