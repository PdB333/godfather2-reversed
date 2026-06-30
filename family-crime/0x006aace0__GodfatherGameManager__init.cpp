// FUNC_NAME: GodfatherGameManager::init
// Address: 0x006aace0
// Role: Initializes the GodfatherGameManager singleton, including re-initialization if previously active.
// This function sets up the vtable, resets sub-objects, and calls global initialization routines.

class GodfatherGameManager {
    // Known field offsets (byte offsets from this):
    // +0x00: vtable pointer
    // +0x3C: pointer to some function table (PTR_LAB_00d5d9cc)
    // +0x48: pointer to another function table (PTR_LAB_00d5d9c8)
    // +0xF2: flag (bool) indicating if the manager was already initialized
    // +0x64: sub-object (probably a nested member) used by FUN_006aab90

public:
    void __thiscall init() {
        // Set vtable and function tables
        *(void**)this = (void*)&PTR_FUN_00d5d9dc;          // Virtual table
        *(void**)((char*)this + 0x3C) = (void*)&PTR_LAB_00d5d9cc; // +0x3C
        *(void**)((char*)this + 0x48) = (void*)&PTR_LAB_00d5d9c8; // +0x48

        // If the manager was previously active, release its sub-object and clear the flag
        if (*(char*)((char*)this + 0xF2) != '\0') {
            *(char*)((char*)this + 0xF2) = '\0';
            FUN_006aab90((int*)((char*)this + 0x64)); // Release sub-object at +0x64
        }

        // Free and re-allocate global and member resources
        // DAT_0120e93c is likely a global pointer or singleton
        FUN_004086d0(&DAT_0120e93c);  // Free global resource
        FUN_004086d0((int*)((char*)this + 0x54)); // Free member at +0x54
        FUN_00408310((int*)((char*)this + 0x54)); // Allocate new for +0x54
        FUN_004086d0((int*)((char*)this + 0x5C)); // Free member at +0x5C
        FUN_00408310((int*)((char*)this + 0x5C)); // Allocate new for +0x5C

        // Finalize initialization with engine-level setup
        FUN_006aa780(); // EARS-related initialization
        FUN_0046c640(); // Global engine init (e.g., input, audio)
    }
};

// External references
extern void* PTR_FUN_00d5d9dc;
extern void* PTR_LAB_00d5d9cc;
extern void* PTR_LAB_00d5d9c8;
extern int DAT_0120e93c;
void FUN_006aab90(int* subObj);  // Sub-object release
void FUN_004086d0(int* ptr);     // Deallocation (likely free)
void FUN_00408310(int* ptr);     // Allocation (likely new)
void FUN_006aa780();             // EARS engine init
void FUN_0046c640();             // Global engine init