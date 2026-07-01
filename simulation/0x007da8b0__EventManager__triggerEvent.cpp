// FUNC_NAME: EventManager::triggerEvent
// Address: 0x007da8b0
// This function appears to trigger a contextual sound or effect event based on a configuration type and player state.
// It reads event data from a table indexed by eventType (derived from a config struct), then either creates a new event handle or reuses an existing one.
// Later it calls a sound/effect function with a type code (0, 3, or 5) and timing.

void __thiscall EventManager::triggerEvent(int this, char immediateFlag)
{
    int *slotState; // this+0xa8
    int *gameState; // this+0x58
    int configPtr; // this+0x74
    int eventType; // configPtr[1] (e.g., 4, 16, 32, other)
    int eventData0, eventData1, eventData2, eventData3; // the four magic values
    float currentTime;
    uint flags;
    int soundId;
    int handleId;
    float timeArg;
    int *allocObj1; // local_5c
    int *allocObj2; // local_64
    char audioDataBuffer[40]; // local_8c
    undefined4 unusedLocal98, unusedLocal94, unusedLocal90; // used for allocation call
    undefined8 unknownData; // local_10
    undefined4 unknownData2; // local_8

    slotState = (int *)(this + 0xa8);
    gameState = *(int **)(this + 0x58);

    // If slot is already active and not in a reset state, return early
    if ((*slotState != 0) && (*slotState != 0x48)) {
        return;
    }

    configPtr = *(int *)(this + 0x74);
    eventType = *(int *)(configPtr + 4); // +4 offset: size indicator (e.g., 4, 16, 32)

    // Initialize sentinel values for event data (like "BEEF", "EA CLASS", etc.)
    eventData0 = -0x45245246; // 0xBAD0BEEF?
    eventData1 = 0xbeefbeef;
    eventData2 = 0xeac15a55;
    eventData3 = 0x91100911;

    // Set the this pointer for later use
    int thisCopy = this;
    int eventTypeCopy = eventType;
    currentTime = (float)FUN_006d03b0(); // get current time or a float value

    // Select the appropriate set of four ints from gameState based on eventType
    // Offsets are relative to gameState (0x2c04 base, plus increments for different types)
    if (eventType == 4) {
        eventData0 = *(int *)(gameState + 0x2c24 / 4);
        eventData1 = *(int *)(gameState + 0x2c28 / 4);
        eventData2 = *(int *)(gameState + 0x2c2c / 4);
        eventData3 = *(int *)(gameState + 0x2c30 / 4);
    }
    else if (eventType == 0x10) {
        eventData0 = *(int *)(gameState + 0x2c34 / 4);
        eventData1 = *(int *)(gameState + 0x2c38 / 4);
        eventData2 = *(int *)(gameState + 0x2c3c / 4);
        eventData3 = *(int *)(gameState + 0x2c40 / 4);
    }
    else if (eventType == 0x20) {
        currentTime = (float)FUN_006d03c0(); // alternate time source
        eventData0 = *(int *)(gameState + 0x2c14 / 4);
        eventData1 = *(int *)(gameState + 0x2c18 / 4);
        eventData2 = *(int *)(gameState + 0x2c1c / 4);
        eventData3 = *(int *)(gameState + 0x2c20 / 4);
    }
    else {
        eventData0 = *(int *)(gameState + 0x2c04 / 4);
        eventData1 = *(int *)(gameState + 0x2c08 / 4);
        eventData2 = *(int *)(gameState + 0x2c0c / 4);
        eventData3 = *(int *)(gameState + 0x2c10 / 4);
    }

    // If all event data are zero, create a new event handle via allocation
    if ((eventData0 == 0) && (eventData1 == 0) && (eventData2 == 0) && (eventData3 == 0)) {
        unusedLocal98 = 2;   // allocation type?
        unusedLocal94 = 0x10;
        unusedLocal90 = 0;
        int allocResult = FUN_009c8ed0(0xf4, &unusedLocal98); // allocate 0xf4 bytes?
        if (allocResult == 0) {
            handleId = 0;
        }
        else {
            handleId = FUN_006d6ae0(); // get a handle from the allocation
        }
    }
    else {
        // Convert the four data values into a handle (maybe a quaternion or vector)
        handleId = FUN_00446130(&eventData0, 0);
    }

    // Register/initialize the event
    FUN_007d9910(handleId);
    // Some global synchronization
    FUN_006d69c0();

    // Prepare slot index: subtract 0x48 if slot state is non-zero
    int slotIndex;
    if (*slotState == 0) {
        slotIndex = 0;
    }
    else {
        slotIndex = *slotState - 0x48; // 0x48 = 72, possibly slot size offset
    }
    // Pass slot index to a buffer initialization function
    FUN_006bfa70(slotIndex + 0x68);

    // Copy some data to a global buffer (DAT_01129944)
    int *globalBuffer = (int *)DAT_01129944;
    *(undefined8 *)(globalBuffer + 0x108 / 4) = unknownData;
    *(undefined4 *)(globalBuffer + 0x110 / 4) = unknownData2;

    // Determine if a special condition applies (playing as player type?)
    int isSpecialState = 0;
    int playerState = FUN_007a5f40(); // returns 0,1,2?
    if ((playerState == 2) && (*(int *)(gameState + 0x74c / 4) != 0) &&
        (*(int *)(gameState + 0x74c / 4) != 0x48) &&
        (*(char *)(*(int *)(gameState + 0x74c / 4) + 0x165) == '\x18')) {
        isSpecialState = 1;
    }

    // Build flags: set bit 0 if any event data is non-zero, else clear it
    if ((eventData0 == 0) && (eventData1 == 0) && (eventData2 == 0)) {
        flags = CONCAT31(flags._1_3_, 1); // set low byte to 0x01
        if (eventData3 != 0) goto skipFlagClear;
    }
    else {
skipFlagClear:
        flags = flags & 0xffffff00; // clear low byte
    }

    // Update some state with flags and special status
    FUN_006d76c0(gameState, flags, isSpecialState);

    // Another condition: if eventType is 32 (0x20) or global is 32, clear something
    if ((eventTypeCopy == 0x20) || (DAT_0112bacc == 0x20)) {
        // local_3c is unnamed; set to 0 (used later? but not referenced)
        // (The decompiled code set local_3c = 0; but it's unused afterward)
    }

    // Initialize audio buffer
    FUN_006bfa70(audioDataBuffer);

    // Reset global flags
    DAT_0112a863 = 0;
    DAT_0112a868 = 0;

    // Determine the type and timing for the sound/effect call based on immediateFlag and state
    soundId = *(int *)(&DAT_00002494 + (int)gameState); // e.g., an asset ID from a table
    if (immediateFlag == '\0') {
        // Check for a critical/important event
        if ((gameState != 0) &&
            ((*(uint *)(gameState + 0x24a4 / 4) >> 0xd & 1) != 0) &&
            ((*(uint *)(*(int *)(thisCopy + 0x58) + 0x8e4 / 4) >> 0x1e & 1) == 0) &&
            (FUN_007aefe0(0x3f) == '\0')) {
            // Important event: use global time and type 5
            if (*slotState == 0) {
                slotIndex = 0;
            }
            else {
                slotIndex = *slotState - 0x48;
            }
            timeArg = *(float *)&_DAT_00d5c458; // a global time value
            int typeCode = 5;
            FUN_00424dc0(soundId, slotIndex, timeArg, typeCode, 0);
        }
        else {
            // Normal event: use local time and type 3
            if (*slotState == 0) {
                slotIndex = 0;
            }
            else {
                slotIndex = *slotState - 0x48;
            }
            timeArg = currentTime;
            int typeCode = 3;
            FUN_00424dc0(soundId, slotIndex, timeArg, typeCode, 0);
        }
    }
    else {
        // Immediate event (forced, no delay)
        if (*slotState == 0) {
            slotIndex = 0;
        }
        else {
            slotIndex = *slotState - 0x48;
        }
        timeArg = 0.0f;
        int typeCode = 0;
        FUN_00424dc0(soundId, slotIndex, timeArg, typeCode, 0);
    }

    // Clean up allocated objects if they exist
    if (allocObj1 != 0) {
        FUN_004daf90(allocObj1);
    }
    if (allocObj2 != 0) {
        FUN_004daf90(allocObj2);
    }
    return;
}