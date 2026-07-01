// FUNC_NAME: Player::~Player

// Function address: 0x007c8d80
// Destructor for Player class (EARS engine, EA Godfather 2)
// Releases owned modules, cleans up attributes, resets audio state,
// shuts down entity, and calls base destructors.

void __fastcall Player::~Player(uint* thisPtr)
{
    char cVar1;
    int* piVar2;
    int iVar3;
    
    // Set vtable to base class (SimNpc/Entity)
    *thisPtr = (uint)&PTR_LAB_00d6e940;

    // Bit 0x4000 (bit 14) in thisPtr[0x4a] indicates an active entity shutdown
    if (((thisPtr[0x4a] >> 0xe) & 1) != 0) {
        thisPtr[0x4a] &= 0xffffbfff;      // clear bit 14
        // Call entity::shutdown() at vtable offset 0x304
        (**(code**)(*(int*)thisPtr[0x16] + 0x304))();
    }

    // Release stream/module handles (indices 0x18...0x31)
    // These correspond to audio, input, etc.
    FUN_007f6420(0x18);
    FUN_007f6420(0x19);
    FUN_007f6420(0x1a);
    FUN_007f6420(0x1b);
    FUN_007f6420(0x1c);
    FUN_007f6420(0x1d);
    FUN_007f6420(0x1e);
    FUN_007ab4d0(0x15);
    FUN_007ab4d0(0x21);
    FUN_007f6420(0x1f);
    FUN_007f6420(0x31);

    // Release module slot 0x20 via the module manager singleton
    piVar2 = (int*)FUN_007ab130();           // get module manager
    (**(code**)(*piVar2 + 4))(0x20);         // release/delete module

    // Free a previously stored module pointer (thisPtr[0x4b])
    if (thisPtr[0x4b] != 0) {
        piVar2 = (int*)FUN_007ab130();
        (**(code**)(*piVar2 + 4))(thisPtr[0x4b]);
        thisPtr[0x4b] = 0;
    }

    // Release audio resource #2 via another manager singleton
    piVar2 = (int*)FUN_007ab150();           // get audio manager
    (**(code**)(*piVar2 + 4))(2);

    // Reset master volume and play a UI sound (likely menu exit)
    FUN_007ab110(1, _DAT_00d6e8f0, 3);       // setMasterVolume(1, _, 3)
    FUN_00551390(1, _DAT_00d6e8f0, 3);       // playUISound(1, _, 3)

    piVar2 = thisPtr + 0x32;                 // pointer to attribute override (offset 0xC8)
    // If attribute override is nonzero and not 0x48 (72) – possibly a stored height/trait
    if ((thisPtr[0x32] != 0) && (thisPtr[0x32] != 0x48)) {
        if (*piVar2 == 0) {
            iVar3 = 0;
        } else {
            iVar3 = *piVar2 - 0x48;          // convert from height to index?
        }
        // Set trait on the entity (entity + 0x2494) using the calculated index
        FUN_00424df0(*(undefined4*)(0x2494 + thisPtr[0x16]), iVar3, _DAT_00d6e910, 2, 0, 0);
    }

    // Reset the entity's special state flag at offset 0x30ac
    *(undefined4*)(thisPtr[0x16] + 0x30ac) = 0;

    // If not in multiplayer (bit 15 clear), check if we need to reset
    if (((thisPtr[0x4a] >> 0xf) & 1) == 0) {
        cVar1 = FUN_00481620();              // isMultiplayerActive?
        if (cVar1 != '\0') {
            FUN_007c8a30(&stack0xfffffff7, 10); // leaveGame or resetState
        }
    }

    // Check byte at +0x12a (0x12A), bit 0 – likely indicates "dead" or "inactive"
    if ((*(byte*)((int)thisPtr + 0x12a) & 1) != 0) {
        FUN_00472130(1);                     // setDead/disable
        thisPtr[0x4a] &= 0xfffeffff;         // clear bit 16
    }

    // Replace vtable pointer with derived class vtable (component base)
    thisPtr[0x35] = (uint)&PTR_FUN_00d6e930;
    if (thisPtr[0x37] != 0) {
        FUN_004daf90(thisPtr + 0x37);        // free sub-object at offset 0xDC
    }

    thisPtr[0x35] = (uint)&PTR_LAB_00d6ba68;
    if (*piVar2 != 0) {
        FUN_004daf90(piVar2);                // free attribute override object
    }

    // Set final base vtable (Entity::vtable)
    *thisPtr = (uint)&PTR_LAB_00d6b95c;
    FUN_0080ea60();                          // final cleanup / deallocate
    return;
}