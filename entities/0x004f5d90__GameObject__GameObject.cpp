// FUNC_NAME: GameObject::GameObject
// Function address: 0x004f5d90
// Constructor for a game object that registers itself in a global allocation list.
// Sets base and derived vtables, then if the object has a non-zero ID (offset 0x10),
// it stores (vtable, ID) in a globally managed buffer.

// Forward declarations for callees
void __fastcall baseConstructor(void);  // FUN_004ebba0 - likely base class init
void __fastcall initFunction(void);     // FUN_004f70f0 - some initialization

// Global memory manager base address
extern void* g_memoryManagerBase;       // DAT_01206880
// At offset 0x14 from base, there is a pointer to a write cursor (int*)
#define MEM_MGR_WRITE_CURSOR_OFFSET 0x14

// Vtable symbols from Ghidra labels
extern void* PTR_FUN_00e37828;          // Base class vtable
extern void* PTR_FUN_00e37110;          // Derived class vtable (overrides base)
extern void* PTR_LAB_01123be8;          // Vtable for stored objects in the allocator

void __thiscall GameObject::GameObject(GameObject* this) // param_1
{
    // Set base class vtable
    this->vtable = &PTR_FUN_00e37828;

    // Call base constructor and additional initializer
    baseConstructor();       // FUN_004ebba0
    initFunction();          // FUN_004f70f0

    // Set derived class vtable (overrides base)
    this->vtable = &PTR_FUN_00e37110;

    // Check field at offset 0x10 (e.g., an object identifier or pointer to external data)
    int objectData = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x10); // param_1[4]
    if (objectData != 0)
    {
        // Retrieve the current write cursor from the memory manager
        int* writeCursor = *reinterpret_cast<int**>(static_cast<char*>(g_memoryManagerBase) + MEM_MGR_WRITE_CURSOR_OFFSET);

        // Store a vtable pointer at the current cursor position
        *reinterpret_cast<void**>(writeCursor) = &PTR_LAB_01123be8;
        writeCursor++;

        // Store the object's data (e.g., the identifier)
        *writeCursor = objectData;
        writeCursor++;

        // Update the write cursor in the memory manager
        *reinterpret_cast<int**>(static_cast<char*>(g_memoryManagerBase) + MEM_MGR_WRITE_CURSOR_OFFSET) = writeCursor;

        // Clear the fields in this object after it's been recorded
        *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x10) = 0; // param_1[4]
        *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x14) = 0; // param_1[5]
    }
    return;
}