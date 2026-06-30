// FUNC_NAME: LevelResourceManager::releaseResource
void __thiscall LevelResourceManager::releaseResource(void *this, int unused, int *resourceIdPtr)
{
    int id;
    int index;
    short *refCountPtr;
    int *globalPtr;
    char levelName[16];

    id = *resourceIdPtr;
    resourceIdPtr = (int *)id;
    index = someLookupFunction(&resourceIdPtr); // FUN_005be1a0 - looks up index for given resource ID
    if (index < 0) {
        refCountPtr = (short *)0x0;
    }
    else {
        // this+0x2c points to an array of 8-byte entries; each entry has a short at offset 4
        refCountPtr = (short *)(*(int *)((int)this + 0x2c) + 4 + index * 8);
    }
    *refCountPtr = *refCountPtr - 1;
    if (*refCountPtr == 0) {
        // Format level name: "_level%u"
        _sprintf(levelName, "_level%u", id);
        // Call DestructAux with the level name (likely destroys the level resource)
        callDestructAux("DestructAux", 0, levelName, 1, levelName); // FUN_005a04a0
        // Access global manager at DAT_01206880, offset 0x14 (some pointer chain)
        globalPtr = (int *)(DAT_01206880 + 0x14);
        **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_011260cc; // Set vtable pointer?
        *globalPtr = *globalPtr + 4; // Advance pointer
        *(int *)*globalPtr = id + 1; // Write new ID
        *globalPtr = *globalPtr + 4; // Advance pointer again
        // Call another lookup function (maybe to update some state)
        index = someLookupFunction(&resourceIdPtr); // FUN_005be1a0 again
        if (index >= 0) {
            someUpdateFunction(); // FUN_005be150
        }
    }
}