// FUNC_NAME: GodfatherGameManager::constructor
// Address: 0x007aabe0
// Description: Constructor for GodfatherGameManager singleton. Sets up dual vtables (base and interface) and calls engine creation function with class hash.

undefined4* __thiscall GodfatherGameManager::constructor(undefined4* thisPointer, undefined4 param2)
{
    // Initialize vtable pointers: primary class vtable at +0x00, interface vtable at +0x04
    thisPointer[1] = (undefined4*)&PTR_LAB_00d6ba98;       // +0x04: temporary/first interface vtable
    *(undefined4**)thisPointer = (undefined4*)&PTR_FUN_00d6baa0; // +0x00: primary vtable
    thisPointer[1] = (undefined4*)&PTR_LAB_00d6ba9c;       // +0x04: correct interface vtable

    // Store global reference to this singleton instance
    DAT_01129958 = thisPointer;

    // Call engine object creation with class ID hash (0x7b80c13a = likely GodfatherGameManager)
    FUN_00463980(0x7b80c13a, thisPointer, param2);
    return thisPointer;
}