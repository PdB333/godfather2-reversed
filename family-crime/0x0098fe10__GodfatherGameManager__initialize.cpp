// FUNC_NAME: GodfatherGameManager::initialize
// Address: 0x0098fe10
// This function initializes the main game manager singleton, sets up vtable pointers,
// initializes static subsystems, and performs cleanup of any existing state.

void __fastcall GodfatherGameManager::initialize(GodfatherGameManager* this)
{
    // Set primary vtable (main class)
    this->vtable = &PTR_FUN_00d91c68; // +0x00

    // Set secondary vtable (possibly base class or interface)
    this->field_0x10 = &PTR_LAB_00d91c44; // +0x10

    // Set tertiary vtables for sub-objects
    this->field_0x4C = &PTR_LAB_00d91c34; // +0x4C
    this->field_0x58 = &PTR_LAB_00d91c30; // +0x58

    // Initialize static subsystem globals (constructors/allocators)
    initializeStaticData(&DAT_01130930); // subsystem A
    initializeStaticData(&DAT_01130928); // subsystem B
    initializeStaticData(&DAT_01130920); // subsystem C

    // Initialize (or reinitialize) the static subsystems
    initSubsystem(&DAT_01130930);
    initSubsystem(&DAT_01130918);
    initSubsystem(&DAT_01130928);
    initSubsystem(&DAT_01130920);

    // Initialize member sub-object at offset +0x17C
    initSubsystem(&this->field_0x17C); // +0x17C

    // Cleanup any previously allocated pointer (e.g., from a previous initialization)
    if (this->field_0x16C != 0) // +0x16C
    {
        // Call destructor through vtable at offset +0x178
        (*(void (__thiscall**)(void*))this->field_0x178)(this->field_0x16B); // +0x178
    }

    // Set additional vtables (overwrites earlier values)
    this->field_0xE8 = &PTR_LAB_00d83b18; // +0xE8
    this->field_0x64 = &PTR_LAB_00d83b18; // +0x64
    this->field_0x58 = &PTR_LAB_00d91c2c; // +0x58 (overwrites previous)

    // Reset global initialization flag
    g_gameManagerInitialized = 0; // DAT_01130910

    // Final system-level initialization
    initializeCoreSystems(); // FUN_004083d0
    initializeNetworkSubsystem(); // FUN_005c16e0
}