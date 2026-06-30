// Xbox PDB: AptDisplayList::placeObject
// FUNC_NAME: AptDisplayList::updateDisplayList

// Function at 0x005b6340: Updates Apt display list for characters/items.
// Called from AptDisplayList rendering pipeline (file: ..\source\Apt\AptDisplayList.cpp)
// Processes display list entries, handles special sprite types (0x0D, 0x12) for characters/items.

int AptDisplayList::updateDisplayList(int arg)
{
    // local helpers (inlined from Apt utilities)
    int param0 = Apt::getParam(0);           // FUN_005a0d00(0)
    int param1 = Apt::getParam(1);           // FUN_005a0d00(1)
    int param2 = Apt::getParam(2);           // FUN_005a0d00(2)
    uint* param3Ptr = nullptr;               // local_5c
    if (arg >= 4) {
        param3Ptr = (uint*)Apt::getParam(3); // FUN_005a0d00(3)
    }

    // Initialize a stack buffer for iteration
    AptString iterString;                     // local_34 points to local_30
    uint8_t iterBuf[24];                     // local_30, local_28, local_20?? Actually size 24
    AptString_init(&iterString, (ulong*)&iterBuf); // FUN_005a92b0

    int foundFlag = 0;                       // iVar8
    void* displayListEntry = AptDisplayList::getFirstEntry(); // FUN_0059c3b0
    while (displayListEntry != nullptr) {
        foundFlag = AptDisplayList::iterateEntry(&iterString); // FUN_005b62e0
        if (foundFlag != 0) break;
        displayListEntry = *(void**)((int)displayListEntry + 0x54); // next entry offset +0x54
    }

    // Second iteration buffer
    AptString secondString;                  // local_18 points to local_14
    uint8_t secondBuf[24];                   // local_14, local_c
    AptString_init(&secondString, (ulong*)&secondBuf); // FUN_005a92b0

    void* renderState = AptDisplayList::getRenderState(); // FUN_0059c3b0 (reused?)
    AptString* pSecondString = &secondString; // local_54
    void* transform = AptRenderer::getTransform(); // FUN_005a8fe0
    void* root = AptRenderer::getRoot();           // FUN_005a19c0
    uint* outHandle = nullptr;                     // param_2 (reused as output)
    int outFlags = 0;                              // local_60

    if (foundFlag == 0) {
        // Assertion macro: "pCharacter || pItem" at AptDisplayList.cpp line 0x1a2
        AptAssert("pCharacter || pItem", "..\\source\\Apt\\AptDisplayList.cpp", 0x1a2, 2, &DAT_01129016); // FUN_0059bf00
    }

    // Main rendering call
    AptRenderer::drawItem( (int)root + 0x1c, (int)transform + 0x4000, foundFlag,
                          pSecondString, renderState, 1, 0xffffffff,
                          &outHandle, &outFlags ); // FUN_005b24b0

    if (outHandle != nullptr) {
        if ( (outFlags != 0) && (AptDisplayList::getState() == 5) ) { // FUN_005a3f20
            // Check if handle is already in the global display list
            int idx = 0;
            uint** displayListArray = (uint**)(DAT_aptManager + 0x1d14); // DAT_0119a9cc + 0x1d14
            while (idx < 0x200) {
                if (displayListArray[idx] == outHandle) {
                    break; // Already registered
                }
                idx++;
            }
            if (idx >= 0x200) {
                AptDisplayList::registerHandle(outHandle); // FUN_005b9140
            }
        }

        uint handleType = *outHandle & 0x7FFF; // lower 15 bits: type
        // Check high bit (0x8000) meaning "valid" and type 0x0D (character) or 0x12 (item)
        if ( ((*outHandle & 0x8000) != 0) &&
             ((handleType == 0x0D || handleType == 0x12)) &&
             (param3Ptr != nullptr) &&
             ((*param3Ptr & 0x8000) != 0) ) {
            // Iterate and update character/item properties
            void* iterator = AptDisplayList::getIterator(); // FUN_005bc1e0
            void** entry = (void**)AptDisplayList::getNextEntry(iterator); // FUN_005bb260
            while (entry != nullptr) {
                AptCharacter::updateProperties(outHandle, 0, entry[3], (int)entry[1], 1, 1); // FUN_005ad5b0
                entry = (void**)AptDisplayList::getNextEntry(iterator); // FUN_005bb2a0
            }
        }
    }

    AptRenderer::endFrame(DAT_aptManager); // FUN_005a5ea0

    // Free temporary strings if they were allocated dynamically
    if ( (&secondString != (AptString*)&secondBuf) && (&secondString != nullptr) ) {
        (*DAT_freeFunc)(secondString); // DAT_0119caf4
    }

    int result = DAT_globalReturnValue; // DAT_0119cbbc

    if ( (&iterString != (AptString*)&iterBuf) && (&iterString != nullptr) ) {
        (*DAT_freeFunc)(iterString);
    }

    return result;
}