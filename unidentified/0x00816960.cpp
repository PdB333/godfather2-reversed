// FUN_00816960: GodfatherGameManager::GodfatherGameManager
GodfatherGameManager* __fastcall GodfatherGameManager::GodfatherGameManager(GodfatherGameManager* this)
{
    // Call base class constructor (likely EARS::Framework::Object or similar)
    FUN_0049c610();

    // Initialize vtable pointer at +0x00 (primary vtable)
    this[0] = (GodfatherGameManager*)&PTR_FUN_00d73190;
    // +0x00: vtable for GodfatherGameManager (virtual function table)

    // +0x08: second vtable pointer (possibly for an implemented interface or virtual base)
    this[2] = (undefined4*)&PTR_LAB_00d73188;
    // Initially set to one table, then overwritten below

    // Set global singleton pointer (g_pGodfatherGameManager)
    DAT_011298dc = (undefined4*)this;

    // Overwrite the second vtable pointer
    this[2] = (undefined4*)&PTR_LAB_00d7318c;

    // Initialize member fields at +0x0C, +0x10, +0x14 to zero
    this[3] = 0; // +0x0C
    this[4] = 0; // +0x10
    this[5] = 0; // +0x14

    // Register this instance with the global manager list (or similar)
    // FUN_0049c6e0 likely takes a static variable and a flag (1 = add? register?)
    FUN_0049c6e0(&DAT_00d7317c, 1);

    return this;
}