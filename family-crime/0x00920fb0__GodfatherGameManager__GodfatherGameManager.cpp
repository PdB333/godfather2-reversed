// FUNC_NAME: GodfatherGameManager::GodfatherGameManager

// Constructor for the main game manager (0x00920fb0)
// Sets up vtables (primary + secondary), initializes subsystems
// Called from two locations (base/derived constructors or factory functions)

class GodfatherGameManager {
public:
    // Virtual function table for this class
    void** vtable; // +0x00

    // Secondary vtable (e.g., for an interface or base class)
    void* secondaryVtable; // +0x04 (offset 0x10 from start? actually param_1[4] = byte offset 0x10)

    // More vtable pointers (offsets 0x14 and 0x15 relative to param_1 pointer => byte 0x50 and 0x54)
    void* thirdVtable;   // +0x50 (initial &PTR_LAB_00d862f8)
    void* fourthVtable;  // +0x54 (initial &PTR_LAB_00d862e0)

    // Subsystem object pointer (offset 0x26 -> byte 0x98)
    void* subsystem1;    // +0x98

    // Another subsystem object pointer (offset 0x29 -> byte 0xA4)
    void* subsystem2;    // +0xA4

    void __thiscall constructor();
};

void __thiscall GodfatherGameManager::constructor() {
    // Set primary vtable
    this->vtable = (void**)0x00d86320; // &PTR_FUN_00d86320

    // Initialize secondary vtables
    *(void**)((char*)this + 0x10) = (void*)0x00d862fc;
    *(void**)((char*)this + 0x50) = (void*)0x00d862f8;
    *(void**)((char*)this + 0x54) = (void*)0x00d862e0;

    // Initialize first subsystem (pointer at +0x98)
    FUN_009c8f10(this->subsystem1); // likely some create/init call

    // If second subsystem exists, process it
    if (this->subsystem2 != nullptr) {
        FUN_004daf90(&this->subsystem2); // release/destroy or setup
    }

    // Call base class initialization twice (resembles chain: base then derived)
    FUN_00920cf0(); // possibly base class constructor
    FUN_00920cf0(); // derived part

    // Override one of the secondary vtables (derived substitution)
    *(void**)((char*)this + 0x50) = (void*)0x00d862dc;

    // Reset global flag (e.g., initialization complete)
    DAT_0112e2e8 = 0;

    // Final initialization step
    FUN_00957d90();

    return;
}