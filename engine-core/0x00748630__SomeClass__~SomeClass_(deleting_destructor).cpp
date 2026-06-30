// FUNC_NAME: SomeClass::~SomeClass (deleting destructor)
// Address: 0x00748630
// This is the scalar deleting destructor for a game object. It calls internal cleanup functions,
// destroys a member at offset +0x58 (0x16 * 4), and optionally frees the memory if deleteFlag bit 0 is set.

typedef unsigned char uint8_t;

// Forward declarations for unknown helper functions
void FUN_00751ec0(void);          // Likely base destructor or resource cleanup
void FUN_004daf90(void* ptr);     // Destructor for a member object (calls with address at this+0x58)
void FUN_0080ea60(void);          // Additional cleanup
void FUN_00624da0(void* ptr);     // operator delete (or internal deallocation)

// Forward declaration of the class
class SomeClass;   // Replace with actual class name from debug symbols

// Vtable symbol from the binary
extern void* PTR_LAB_00d6415c;   // Likely the vtable for SomeClass

// This is the deleting destructor (MSVC pattern with a byte flag)
SomeClass* __thiscall SomeClass::`scalar deleting destructor'(uint8_t deleteFlag)
{
    // Set vtable pointer to this class's vtable (ensures correct virtual dispatch during destruction)
    *(void**)this = &PTR_LAB_00d6415c;

    // Call base class destructor or general cleanup
    FUN_00751ec0();

    // Check if the member at offset +0x58 (0x16 * sizeof(void*)) is non-null
    // This member is likely a pointer to another object or a managed resource
    if (*(void**)((uint8_t*)this + 0x58) != 0)
    {
        // Destroy the member object pointed to by this+0x58
        FUN_004daf90((void*)((uint8_t*)this + 0x58));
    }

    // Additional cleanup (e.g., releasing subsystems, decrementing reference counts)
    FUN_0080ea60();

    // If the delete flag indicates memory deallocation (bit 0 set), free the object
    if ((deleteFlag & 1) != 0)
    {
        FUN_00624da0(this);  // operator delete or custom deallocator
    }

    return this;
}