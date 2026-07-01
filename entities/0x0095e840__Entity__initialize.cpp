// FUNC_NAME: Entity::initialize
void __fastcall Entity::initialize(int this)
{
    // Initializes base components
    FUN_0095e490();  // Base entity initialization
    FUN_009630a0();  // Another base component init

    // Set default member values
    *(int*)(this + 0xdc) = 0;         // someState, default 0
    *(int*)(this + 0xe0) = 2;         // someMode, enum value 2
    *(int*)(this + 0xe4) = 0x10;      // someCount or flag, 16
    *(int*)(this + 0xe8) = 0;         // timer or ID, 0
    *(int*)(this + 0xf0) = 0;         // unknown field
    *(int*)(this + 0xf4) = 0;         // unknown field
    *(int*)(this + 0xfc) = 0;         // unknown field
    *(int*)(this + 0x100) = 0;        // unknown field
}