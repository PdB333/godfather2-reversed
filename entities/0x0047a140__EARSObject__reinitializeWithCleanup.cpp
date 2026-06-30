// FUNC_NAME: EARSObject::reinitializeWithCleanup

#include <cstdint>

// Forward declarations
void __fastcall FUN_0047a870(EARSObject* obj);
void __fastcall FUN_004086d0(void* ptr);
void __fastcall FUN_00408310(void* ptr);
void __fastcall FUN_0047a040(void);
void __fastcall FUN_0046c640(void);

// Global variables – named based on usage pattern
extern uint32_t g_earsResourceA;  // DAT_0120e924
extern uint32_t g_earsResourceB;  // DAT_0120e91c

// Represents the object being initialized. Offsets inferred from decompilation.
class EARSObject {
public:
    // +0x00: vtable pointer
    void** vtable;

    // Offset 0x3C (+0x0F * 4): pointer to secondary vtable or function table
    void** secondaryVtable;  

    // Offset 0x48 (+0x12 * 4): another pointer (likely a callback table)
    void** callbackTable;    

    // Offset 0x5E: bitfield of flags
    uint16_t flags;

    // Offset 0x50 (+0x14 * 4): pointer to a sub-object (e.g., a resource manager)
    void* subObject;          

    // Offset 0x58 (+0x16 * 4): another sub-object pointer (e.g., a renderer)
    void* anotherSubObject;   
};

// Bitmask constants
constexpr uint16_t FLAG_GLOBAL_RESOURCES_ALLOCATED = 0x4000;

// Reinitialize this game object, cleaning up any previously allocated global resources
void __fastcall EARSObject::reinitializeWithCleanup(EARSObject* thisPtr) {
    // Set up vtable and function tables
    thisPtr->vtable = &PTR_FUN_00e33050;            // Main vtable
    thisPtr->secondaryVtable = &PTR_LAB_00e3306c;   // Additional table 1
    thisPtr->callbackTable = &PTR_LAB_00e3307c;     // Additional table 2

    // Check if global resources were previously allocated
    if ((thisPtr->flags & FLAG_GLOBAL_RESOURCES_ALLOCATED) != 0) {
        // Clear the flag
        thisPtr->flags &= ~FLAG_GLOBAL_RESOURCES_ALLOCATED;

        // Free the global resources (likely handles or memory blocks)
        FUN_004086d0(&g_earsResourceA);
        FUN_004086d0(&g_earsResourceB);
    }

    // Perform subclass-specific initialization (likely a virtual or CRM method)
    FUN_0047a870(thisPtr);

    // Reset the sub-object at offset 0x50: first deallocate, then zero-initialize
    FUN_004086d0(&thisPtr->subObject);      // Free if non-null (inside implementation)
    FUN_00408310(&thisPtr->subObject);      // Set to zero (memset or default init)

    // If another sub-object exists, call its cleanup routine
    if (thisPtr->anotherSubObject != nullptr) {
        FUN_0047a040();                     // Possibly deallocate or shutdown
    }

    // Perform global shutdown/cleanup
    FUN_0046c640();
}