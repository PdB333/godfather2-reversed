// FUNC_NAME: UIManager::showPopup
void __fastcall UIManager::showPopup(int this) {
    undefined4 buffer[5]; // Actually a 20-byte buffer for string
    LocalStruct localStruct; // 12-byte struct (local_28, local_24, local_20)
    int unknownArray[2]; // Possibly a pointer or array (uninitialized in decompiled)

    setFlag(0);                              // Clear some flag
    initSomething(this, 1);                  // Initialize with this and 1
    loadHashString(0x49a4733, (char*)buffer);// Load string for hash 0x49a4733 (e.g., "mission_complete")
    useGlobalPtr(*(int*)(g_globalBase + 8), 0); // Use global data at offset +8

    localStruct.field0 = g_globalData;       // Copy global data into local struct
    localStruct.field4 = 0;                  // Zero out other fields
    localStruct.field8 = 0;
    processLocalStruct(&localStruct, 0);     // Initialize or process struct

    playSound(0x2e);                         // Play sound effect (ID 46)

    if (unknownArray[0] != 0) {              // If array is non-null
        freeArray(unknownArray);             // Free it
    }
}