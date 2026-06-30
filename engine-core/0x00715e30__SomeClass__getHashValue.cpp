// FUNC_NAME: SomeClass::getHashValue
// Function address: 0x00715e30
// Returns a 32-bit hash based on game variant index and a flag from this+0x18->0x8e0 bit 1
// Used by functions at 0x0076c290 (likely VehicleBrain::someMethod) and 0x0076d020 (likely WheeledVehicle::someMethod)

unsigned int __fastcall SomeClass::getHashValue(void* thisPtr)
{
    // Get game variant index (0-based? returns 1-4? actually called with -1 in switch)
    int variantIndex = getGameVariantIndex(); // FUN_00800b60

    // Dereference thisPtr+0x18 to get a pointer, then read uint at +0x8e0 and test bit 1
    // This likely indicates whether some alternate mode is active (e.g., multiplayer vs singleplayer)
    bool bitFlag = (*(unsigned int*)(*(int*)((char*)thisPtr + 0x18) + 0x8e0) >> 1) & 1;

    unsigned int result = 0;

    if (!bitFlag)
    {
        switch (variantIndex - 1)
        {
        case 0:
            return 0xCB67D47A; // hash for variant 1, normal mode
        case 1:
            return 0x385ADADA;
        case 2:
            return 0x8C44B682;
        case 3:
            result = 0xE9365884;
        }
    }
    else
    {
        switch (variantIndex - 1)
        {
        case 0:
            return 0x480D6D84; // hash for variant 1, alternate mode
        case 1:
            return 0xEAC53CD8;
        case 2:
            return 0x22BB33CA;
        case 3:
            return 0x57B88648;
        }
    }

    return result; // default 0 if variantIndex not in 1..4
}