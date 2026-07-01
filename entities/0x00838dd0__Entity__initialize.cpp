// FUNC_NAME: Entity::initialize
void __fastcall Entity::initialize(int thisPtr)
{
    // Call base class initialization (likely Entity base or component)
    FUN_00838c80();

    // Setup a GUID or identifier structure
    // local_c is the first DWORD, local_8 second DWORD, local_4 a byte (maybe part of a 9-byte struct)
    undefined4 guidPart1 = DAT_0112dbec;   // Global base GUID value
    undefined4 guidPart2 = 0;
    undefined1 guidPart3 = 0;

    // Register this entity with some manager using the GUID and a flag (0)
    FUN_00408a00(&guidPart1, 0);

    // Set entity type/state to 5 (e.g., eType_Player, eState_Active, etc.)
    *(undefined4 *)(thisPtr + 0xe4) = 5;
}