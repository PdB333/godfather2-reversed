// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
// Function address: 0x0096ed10
// Role: Constructor for GodfatherGameManager class (EARS engine manager)

extern uint DAT_00d5c454;   // Some global configuration value
extern uint DAT_00d8dc8c;   // Another global data pointer

// Forward declarations of helper functions called during construction
void __cdecl BaseClass::BaseClass();                    // FUN_005bf9b0
void __cdecl setSomeParameter(int param, uint value);   // FUN_00968d80
void __cdecl initSubsystem();                           // FUN_009627b0

void __thiscall GodfatherGameManager::GodfatherGameManager(GodfatherGameManager* this)
{
    uint uVar1;

    // Call base class constructor (likely EARSObject or similar)
    BaseClass::BaseClass();

    uVar1 = DAT_00d5c454;

    // Set initial vtable pointers (base class vtable)
    this->vtable0 = &PTR_FUN_00d8ee98;   // +0x00
    this->vtable4 = &PTR_LAB_00d8ee70;   // +0x04

    // Initialize unknown fields (likely counters or flags)
    this->field_0x4C = 0;   // +0x4C (param_1[0x13])
    this->field_0x50 = 0;   // +0x50 (param_1[0x14])
    this->field_0x54 = 0;   // +0x54 (param_1[0x15])

    // Call initialization with parameter 6 and global value
    setSomeParameter(6, uVar1);

    this->field_0x70 = 0;   // +0x70 (param_1[0x1c])

    // Override vtable pointers with derived class vtable
    this->vtable0 = &PTR_FUN_00d8f038;   // +0x00
    this->vtable4 = &PTR_LAB_00d8f010;   // +0x04

    // Additional subsystem initialization
    initSubsystem();

    // Assign global data pointer and clear adjacent fields
    this->field_0x184 = DAT_00d8dc8c;               // +0x184 (param_1[0x61])
    *(byte*)((uint)&this->field_0x180) = 0;         // +0x180 (param_1[0x60]) – byte clear
    this->field_0x188 = 0;                          // +0x188 (param_1[0x62])
}