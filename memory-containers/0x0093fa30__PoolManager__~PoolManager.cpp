// FUNC_NAME: PoolManager::~PoolManager

#include <cstdint>

// Forward declarations of external functions
extern bool  __cdecl checkActive(void* ptr);          // FUN_00402080 – checks if global object is active
extern void  __cdecl destroyObject(void* ptr);        // FUN_004086d0 – destroys the global object
extern void  __cdecl deallocatePoolSlot(int32_t slotIndex); // FUN_0093f8f0 – frees a resource pool slot (3 here)
extern void  __cdecl globalShutdown();                // FUN_004083d0 – global cleanup/shutdown

// Global variables
extern uint32_t g_globalObject;   // DAT_012069c4 – handle/pointer to a global object (e.g. a memory pool)
extern int32_t  g_globalFlag;     // DAT_0112a560 – global flag, reset to 0 in destructor

// Vtable pointers (declared as extern pointers to tables)
extern void* PTR_FUN_00d8b080;    // vtable for “scalar deleting destructor” phase
extern void* PTR_LAB_00d8b070;    // second vtable pointer (stored at +0x04)
extern void* PTR_LAB_00d8b06c;    // final vtable (base class) after destruction

class PoolManager {
public:
    void* m_vtable;              // +0x00
    void* m_secondVtable;        // +0x04 – appears to be another vtable pointer
    // fields at +0x08, +0x0C, +0x10, +0x14, +0x18, +0x1C, etc.
    // We only access +0x10, +0x18, +0x1C from this function:
    void* m_subObject;           // +0x10 – pointer to a sub-object; if non-null, deallocated via pool
    int32_t field_18;            // +0x18
    int32_t field_1C;            // +0x1C

    // __thiscall destructor
    void __fastcall ~PoolManager() {
        // Step 1: Set vtable to destructor version (first phase)
        this->m_vtable = &PTR_FUN_00d8b080;
        this->m_secondVtable = &PTR_LAB_00d8b070;

        // Step 2: If the global object is active, destroy it
        if (checkActive(&g_globalObject)) {
            destroyObject(&g_globalObject);
        }

        // Step 3: Zero out two fields at +0x18 and +0x1C
        this->field_18 = 0;
        this->field_1C = 0;

        // Step 4: If the sub-object pointer is non-null, free it from pool slot 3
        if (this->m_subObject != 0) {
            deallocatePoolSlot(3);   // likely frees the resource block associated with slot index 3
        }

        // Step 5: Perform global shutdown (e.g. final cleanup of singletons)
        globalShutdown();

        // Step 6: Switch vtable to final (base class) vtable after all cleanup
        this->m_vtable = &PTR_LAB_00d8b06c;

        // Step 7: Reset the global flag to indicate manager is destroyed
        g_globalFlag = 0;
    }
};