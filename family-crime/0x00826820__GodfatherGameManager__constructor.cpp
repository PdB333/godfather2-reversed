// FUNC_NAME: GodfatherGameManager::constructor
// Function address: 0x00826820
// Initializes the GodfatherGameManager singleton, sets up vtable pointers,
// calls base class constructors, and initializes subsystems.

void __fastcall GodfatherGameManager::constructor(GodfatherGameManager* this)
{
    // Set initial vtable pointers (base class vtables)
    this->vtable0 = &PTR_FUN_00d73558;          // +0x00: Base class vtable
    this->vtable1 = &PTR_LAB_00d73548;          // +0x04: Another base vtable
    this->vtable2 = &PTR_LAB_00d7352c;          // +0x08: Yet another base vtable
    this->field_0x44 = &PTR_LAB_00d7351c;       // +0x44: Some vtable or function pointer
    this->field_0x50 = &PTR_LAB_00d73518;       // +0x50: Another pointer
    this->field_0x58 = &PTR_LAB_00d73514;       // +0x58: Initial pointer (overridden later)

    // Call base class constructors / initializers for global singletons
    FUN_004086d0(&DAT_012069c4);                // Likely initializes some global data
    FUN_004086d0(&DAT_0112db7c);                // Another global initialization
    FUN_004086d0(&DAT_0112db74);                // Yet another global initialization

    // Override vtable pointer at +0x58 with a new value
    this->field_0x58 = &PTR_LAB_00e32854;       // +0x58: Updated vtable for derived class

    // Call another initialization function (subsystem setup)
    FUN_0046c640();                             // Probably initializes game subsystems

    // Override vtable pointers again after subsystem init
    this->vtable1 = &PTR_LAB_00e30fe0;          // +0x04: Updated derived vtable
    this->vtable0 = &PTR_LAB_00d734fc;          // +0x00: Final vtable for this class

    // Reset a global flag
    DAT_0112a53c = 0;                           // Some global state flag
}