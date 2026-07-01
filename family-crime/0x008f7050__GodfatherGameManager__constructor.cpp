// FUNC_NAME: GodfatherGameManager::constructor
// Address: 0x008f7050
// Initializes the GodfatherGameManager singleton, sets vtable pointers, constructs static members, and resets the initialization flag.
void __fastcall GodfatherGameManager::constructor(GodfatherGameManager* this)
{
    // Set primary vtable pointer (base class)
    *this = &PTR_FUN_00d8121c;                         // +0x00: vtable

    // Construct static member objects (likely serialized data managers, audio, etc.)
    FUN_004086d0(&DAT_012069d4);                       // static object at 0x012069d4
    FUN_004086d0(&DAT_012069c4);                       // static object at 0x012069c4
    FUN_004086d0(&DAT_012069f4);                       // static object at 0x012069f4

    // Set secondary vtable pointer at offset +0x0C (for another base or interface)
    this->field_0C = &PTR_FUN_00d81218;                // +0x0C: intermediate vtable

    // Construct additional static objects
    FUN_00408310(&DAT_0112fe5c);                       // static object at 0x0112fe5c
    FUN_00408310(&DAT_0112fe54);                       // static object at 0x0112fe54

    // Perform further module‑level initialization
    FUN_008f6fa0();                                    // subsystem init (e.g., input, file system)

    // Switch to final vtable for the derived class
    this->field_0C = &PTR_LAB_00d81214;                // +0x0C: final vtable

    // Reset global initialization state (0 = not fully initialized yet)
    DAT_0112a580 = 0;                                  // g_bInitializationComplete = false;

    // Final static constructor (e.g., last module to initialize)
    FUN_004083d0();                                    // static object constructor at unknown address
}