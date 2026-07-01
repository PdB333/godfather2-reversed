// FUNC_NAME: CrimeSceneManager::handleStingResult
void CrimeSceneManager::handleStingResult(void)
{
    uint *flagsPtr;
    int stingObject;
    uint globalGameInstance;
    int playerId;
    uint *somePtr;
    int someOtherValue;
    undefined1 *stringPtr;
    undefined1 *stingResultString;
    int resultInt1;
    int resultInt2;
    code *resultCallback;
    undefined1 localBuffer[4112]; // large stack buffer for string formatting

    globalGameInstance = g_gameData; // DAT_012234a4 - global game data pointer
    resultCallback = nullptr;
    resultInt2 = 0;
    resultInt1 = 0;
    stingResultString = nullptr;

    stingObject = getCurrentStingObject(); // FUN_008bf420
    if (stingObject == 0) {
        // No active sting, show failure message
        displayStingMessage(globalGameInstance, &stingResultString, "$dv_sting_fail"); // FUN_006038f0
    } else {
        // Active sting exists
        somePtr = (uint *)(*(int *)(stingObject + 8)); // deref stingObject+8 -> pointer to a structure
        uint *localeManager = (uint *)getLocaleManager(); // FUN_00790610
        playerId = getPlayerIndex(); // FUN_00791300

        beginSoundContext(); // FUN_00604be0 - push sound context

        stringPtr = (undefined1 *)*localeManager; // get current string from locale manager
        if (stringPtr == nullptr) {
            stringPtr = &g_defaultLocaleString; // DAT_0120546e - fallback string
        }

        playSoundEvent(0x6e, stringPtr); // FUN_00604c10 - play sting success sound (0x6e = 110)

        displayStingMessage(globalGameInstance, localBuffer, &stingResultString, "$dv_sting_success"); // FUN_006038a0
        // localBuffer used for formatted output, stingResultString may be set to callback info

        if (playerId == 0) {
            // Check flags at offset +0x5c of the structure pointed by somePtr
            if ((*(uint *)(somePtr + 0x5c) & 0x60000) != 0) {
                flagsPtr = (uint *)(somePtr + 0x5c);
                *flagsPtr = *flagsPtr | 0x80000000; // set top bit
            }
        } else {
            // Handle non-zero playerId: set flag at offset 0x3c
            setPlayerFlag(playerId + 0x3c); // FUN_004088c0 - likely modifies a player state
        }

        releaseStingObject(stingObject); // FUN_008bd890 - cleanup
        endSoundContext(); // FUN_00604c00 - pop sound context
    }

    // If stingResultString was set, call the stored callback
    if (stingResultString != nullptr) {
        processStingCallback(stingResultString); // FUN_00891290
        if (stingResultString != nullptr) {
            (*resultCallback)(stingResultString); // call the callback function pointer
        }
    }
    return;
}