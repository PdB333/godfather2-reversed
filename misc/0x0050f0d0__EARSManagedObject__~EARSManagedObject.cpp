// FUNC_NAME: EARSManagedObject::~EARSManagedObject
// Function address: 0x0050f0d0
// Destructor for EARSManagedObject
// Frees child objects and returns them to a global free list, then releases a main resource pointer.

class EARSManagedObject
{
public:
    // Vtable pointer at +0x00
    uint32_t* vtable;

    // State/type byte at +0x1c (0,1,2,3,6 observed)
    uint8_t state;

    // Handle/resource at +0x50 (offset 0x14 *4)
    uint32_t handle;

    // Pointer to a resource that needs special cleanup at +0x58 (offset 0x16 *4)
    void* resourcePtr;

    // Child object pointers at +0x5c, +0x60, +0x64, +0x68 (offsets 0x17-0x1a *4)
    void* children[4];

    // Constructor/destructor etc.
};

// Global manager used for free list (DAT_012068e8)
struct GlobalManager
{
    // Offset +0x14: pointer to the current free list position
    void** freeListPtr;
};
extern GlobalManager g_globalManager; // DAT_012068e8

// External functions
extern "C" void __cdecl unknownFunc1(void); // FUN_004bfcf0
extern "C" void* __cdecl getMemoryManager(void); // FUN_009c8f80
extern "C" void __cdecl globalCallback(void* ptr); // DAT_0120ec84

void __thiscall EARSManagedObject::~EARSManagedObject(EARSManagedObject* this)
{
    uint8_t state = this->state;

    // Set vtable to base class destructor vtable
    this->vtable = &PTR_FUN_00e380ec;

    if (state != 0)
    {
        if (state < 3)
            goto skipChildren; // state 1 or 2 – just skip to resource cleanup
        if (state == 6)
        {
            // Special state: free the handle resource using memory manager
            uint32_t handle = this->handle;
            if (handle != 0)
            {
                unknownFunc1(); // Possibly some deallocation prelude
                void* memMgr = getMemoryManager();
                // Call vfunc at offset 4 (likely a deallocation/destructor) with arg 0xa0
                (*(void(__thiscall**)(void*, uint32_t))(*((uint32_t*)memMgr) + 4))(handle, 0xa0);
            }
            goto skipChildren;
        }
    }

    // Reclaim children into global free list
    for (int i = 0; i < 4; ++i)
    {
        if (this->children[i] != 0)
        {
            void** freeListHead = &g_globalManager.freeListPtr;
            // Insert child into free list (simple stack push)
            *freeListHead = &PTR_LAB_01124ba8; // sentinel
            *freeListHead = (void*)((uint8_t*)*freeListHead + 4);
            *(void**)*freeListHead = this->children[i];
            *freeListHead = (void*)((uint8_t*)*freeListHead + 4);
            this->children[i] = 0;
        }
    }

skipChildren:
    // Handle the main resource pointer
    if (this->resourcePtr != 0)
    {
        if (globalCallback != 0)
            globalCallback(this->resourcePtr);
        void* memMgr = getMemoryManager();
        // Deallocate resource with size hint 0xb0
        (*(void(__thiscall**)(void*, uint32_t))(*((uint32_t*)memMgr) + 4))(this->resourcePtr, 0xb0);
    }

    // Final vtable switch to indicate fully destructed
    this->vtable = &PTR_LAB_00e37304;
}