// FUNC_NAME: SubmixManager::setupMasterSubmix
// Function at 0x005ed150: Initializes master submix buses, including reverb send configuration.
// Likely part of EARS audio subsystem (Wwise/ProTools-style submix routing).
// Uses custom calling convention: `this` pointer in EAX, additional parameter (audioEngine*) on stack.

int SubmixManager::setupMasterSubmix(void* audioEngine) {
    int* submixData;       // points to internal submix slot array
    int* sendSlotArray;    // derived from submixData + 5
    int submixIndex;       // index into submixData
    int tempIndex;         // temporary slot index
    char** namePtr;        // pointer to string pointer
    int sendSlotHandle;    // handle for send slot creation

    submixData = this;     // this is the SubmixManager object (passed in EAX)
    sendSlotArray = submixData + 5; // offset +0x14? (5 ints = 20 bytes)

    // Initialize some internal audio engine components
    FUN_005ef9a0(); // likely init audio mixer
    FUN_005ef890(); // init send buses

    // Get ID for "SUBMIX2" bus
    submixIndex = FUN_004dafd0("SUBMIX2"); // string-to-ID function
    submixData[0xb] = submixIndex; // store at offset +0x2C

    // Get ID for "Submix1" (maybe a hash name)
    FUN_005e9ba0("Submix1");

    // Create a send slot name hash: 0x53756230 -> "Sub0" (big-endian)
    sendSlotHandle = FUN_00c9cd50(0x53756230); // creates a named hash
    tempIndex = submixData[6]; // current free slot index? (offset +0x18)
    // Write hash into array of slot definitions (each slot is 0xC bytes)
    *(int*)(sendSlotArray[0] + tempIndex * 0xC - 8) = sendSlotHandle;

    // Attach "GlobalReverb" as a receive bus for this slot
    sendSlotHandle = FUN_00c9cd50(0x53756230); // same hash "Sub0"
    FUN_00c9cba0(*(void**)((int)audioEngine + 0x580), sendSlotHandle, local_10); // set reverb bus

    local_10[0] = "GlobalReverb";
    // Store the name pointer in the slot array
    *(char***)(sendSlotArray[0] - 0xC + submixData[6] * 0xC) = local_10;
    // Set slot type byte: 6 = send type?
    *(char*)(sendSlotArray[0] - 4 + submixData[6] * 0xC) = 6;

    // Now set up the wet send (SendWetToMaster)
    FUN_005e9ba0("SendWetToMaster");
    tempIndex = submixData[6];
    sendSlotHandle = FUN_00c9cd50(0x53656e30); // hash: "Sen0" (0x53656e30 bytes "Sen0")
    *(int*)(sendSlotArray[0] + tempIndex * 0xC - 8) = sendSlotHandle;
    // Clear the name pointer for this slot (null)
    *(char***)(sendSlotArray[0] - 0xC + submixData[6] * 0xC) = 0;
    // Set slot type byte: 6 again
    *(char*)(sendSlotArray[0] - 4 + submixData[6] * 0xC) = 6;

    // Create the actual submix slot via audio engine
    // Parameters: audioEngine+0x580 (sound engine handle), 0xfe (254? bus id),
    // submixData[6] (slot index), sendSlotArray[0] (slot data), flags=0
    tempIndex = FUN_00ca55a0(*(void**)((int)audioEngine + 0x580), 0xfe, submixData[6], sendSlotArray[0], 0);
    submixData[0] = tempIndex;      // store created slot handle
    submixData[1] = tempIndex + 0x50; // store another handle (offset +0x50)

    // Now check if parameter "SendWetToMaster" exists and configure
    void** paramArray = &audioEngine; // reuse local array (in original code it's &param_1)
    int wetSendId = FUN_004dafd0("SendWetToMaster", paramArray);
    int wetSendConfig = FUN_005e9d90(wetSendId, paramArray);
    if (wetSendConfig != 0) {
        // Get the wet send value from a specific field at offset +0x10 in the config
        int* configPtr = *(int**)((int)audioEngine + 0x42c);
        // Set the wet send parameter to the current submix slot value
        FUN_00c9cbe0(*(void**)((int)audioEngine + 0x580), *(void**)(wetSendConfig + 0x10), 0, local_8);
        local_8[0] = *configPtr; // copy value from audioEngine+0x42c dereferenced
        FUN_00c9cd40(0, local_8); // apply the parameter
        return 1;
    }
    return 0;
}