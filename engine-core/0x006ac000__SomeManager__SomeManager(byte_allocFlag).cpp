// FUNC_NAME: SomeManager::SomeManager(byte allocFlag)
// Address: 0x006ac000
// This is a constructor for a class (likely a manager) with size 0x5C.
// It initializes its own vtable and two additional function pointers,
// then constructs a sub-object at offset 0x14, calls a global init on DAT_0120e93c,
// calls a global initialization routine, and optionally frees the object if allocFlag & 1.

class SomeManager
{
public:
    // Virtual table pointer (set to PTR_FUN_00d5da8c)
    void *vfptr;

    // Additional vtable-like pointers at offsets 0x3C and 0x48
    void *m_extraVtable1;  // +0x3C
    void *m_extraVtable2;  // +0x48

    // Sub-object embedded at offset 0x14 (size depends on SubObject class)
    // This is initialized by FUN_004086d0 and FUN_00408310
    char m_subObject[0x48]; // Placeholder; actual type unknown; +0x14 to +0x5C

    // Constructor
    // param_1 is 'this', param_2 is allocFlag (byte)
    // allocFlag & 1 indicates whether the object was heap-allocated; if set, object is freed afterwards.
    SomeManager(byte allocFlag)
    {
        // Set main vtable
        this->vfptr = &PTR_FUN_00d5da8c;

        // Set additional vtable-like pointers
        this->m_extraVtable1 = &PTR_LAB_00d5da7c; // +0x3C
        this->m_extraVtable2 = &PTR_LAB_00d5da78; // +0x48

        // Initialize sub-object at offset 0x14 with two separate calls
        subObjectInit(this + 0x14);
        subObjectConfigure(this + 0x14);

        // Initialize global object at DAT_0120e93c (likely a static singleton)
        subObjectInit(&g_globalObject);

        // Global initialization routine (e.g., singleton manager setup)
        globalInit();

        // If heap-allocated flag is set, delete this object before returning
        // Note: This pattern is unusual; the object is freed but returned anyway.
        // Possibly a mistake in decompilation or a custom memory management scheme.
        if (allocFlag & 1)
        {
            operator delete(this, 0x5C);
        }
    }
};

// Forward declarations for called functions
void __thiscall subObjectInit(void *obj);   // FUN_004086d0
void __thiscall subObjectConfigure(void *obj); // FUN_00408310
void __cdecl globalInit();                   // FUN_0046c640
void __cdecl operator delete(void *ptr, int size); // FUN_0043b960

// Global static instance (size unknown, but likely the same class)
extern byte g_globalObject[0x]; // DAT_0120e93c