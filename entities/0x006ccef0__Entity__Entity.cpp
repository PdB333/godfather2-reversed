// FUNC_NAME: Entity::Entity
// Function address: 0x006ccef0
// Role: Constructor for Entity base class. Initializes vtable pointers, debug sentinel values, and default fields.

void * __fastcall Entity::Entity(Entity *thisObject)
{
    // Call base class constructor (likely EARSObject or similar)
    FUN_004737b0();

    // Set up virtual function table pointers (multiple inheritance)
    // PTR_FUN_00d5f134 is the primary vtable
    thisObject->vtable = &PTR_FUN_00d5f134;
    // +0x3C (0xF*4) - secondary vtable
    thisObject->vtable2 = &PTR_LAB_00d5f124;
    // +0x48 (0x12*4) - tertiary vtable
    thisObject->vtable3 = &PTR_LAB_00d5f120;
    // +0x50 (0x14*4) - quaternary vtable
    thisObject->vtable4 = &PTR_LAB_00d5f11c;

    // Initialize two groups of debug sentinel values (memory corruption detection)
    // Group A at +0x58, +0x5C, +0x60, +0x64
    thisObject->sentinelA1 = 0xbadbadba;
    thisObject->sentinelA2 = 0xbeefbeef;
    thisObject->sentinelA3 = 0xeac15a55;
    thisObject->sentinelA4 = 0x91100911;

    // Group B at +0x68, +0x6C, +0x70, +0x74
    thisObject->sentinelB1 = 0xbadbadba;
    thisObject->sentinelB2 = 0xbeefbeef;
    thisObject->sentinelB3 = 0xeac15a55;
    thisObject->sentinelB4 = 0x91100911;

    // Clear six fields (flags/state) at +0x78 through +0x8C
    thisObject->stateFlags1 = 0;
    thisObject->stateFlags2 = 0;
    thisObject->stateFlags3 = 0;
    thisObject->stateFlags4 = 0;
    thisObject->stateFlags5 = 0;
    thisObject->stateFlags6 = 0;

    // Set global object reference and an initialization counter
    // +0x90 - pointer to some global data (DAT_00d5d740)
    thisObject->globalData = DAT_00d5d740;
    // +0x94 - initial value (0x21 = 33)
    thisObject->initCounter = 0x21;

    return thisObject;
}