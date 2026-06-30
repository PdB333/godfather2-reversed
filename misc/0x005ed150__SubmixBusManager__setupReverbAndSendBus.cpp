// FUNC_NAME: SubmixBusManager::setupReverbAndSendBus
int SubmixBusManager::setupReverbAndSendBus(AudioSystem* audioSystem) {
    int* slotBase;
    int slotIndex;
    int currentSlot;
    int* thisPtr = this; // in_EAX
    int result;
    char* paramName;
    int paramHash;

    // Initialize local submix structures
    SubmixBusManager::reset(); // FUN_005ef9a0
    SubmixBusManager::prepareSlots(); // FUN_005ef890

    // Get handle for SUBMIX2 bus
    int submix2Handle = audioSystem->getSubmixHandle("SUBMIX2"); // FUN_004dafd0
    thisPtr[0xB] = submix2Handle; // offset 0x2C

    // Select current submix to "Submix1"
    SubmixBusManager::selectSubmix("Submix1"); // FUN_005e9ba0

    // Configure first parameter: "Sub0" -> "GlobalReverb" with value 6
    currentSlot = thisPtr[6]; // offset 0x18 (slot index)
    slotBase = thisPtr[5]; // offset 0x14 (pointer to slot array)
    paramHash = Utils::hashString(0x53756230); // "Sub0"
    slotBase[currentSlot * 3 - 2] = paramHash; // write hash at offset -8 from slot base
    // Set parameter name string
    audioSystem->setSubmixParameter(*(int*)(audioSystem + 0x580), paramHash, &paramName); // FUN_00c9cba0
    paramName = "GlobalReverb";
    slotBase[currentSlot * 3 - 3] = (int)¶mName; // offset -0xC
    *(char*)(slotBase[currentSlot * 3 - 1]) = 6; // offset -4, value 6

    // Configure second parameter: "Sen0" -> value 0 (no name)
    SubmixBusManager::selectSubmix("SendWetToMaster");
    currentSlot = thisPtr[6];
    slotBase = thisPtr[5];
    paramHash = Utils::hashString(0x53656e30); // "Sen0"
    slotBase[currentSlot * 3 - 2] = paramHash;
    slotBase[currentSlot * 3 - 3] = 0; // no name
    *(char*)(slotBase[currentSlot * 3 - 1]) = 6; // type? still 6

    // Finalize bus creation at slot currentSlot
    int busHandle = audioSystem->finalizeBus(*(int*)(audioSystem + 0x580), 0xFE, currentSlot, slotBase, 0); // FUN_00ca55a0
    thisPtr[0] = busHandle; // start of slot range
    thisPtr[1] = busHandle + 0x50; // end (80 slots)

    // Try to set "SendWetToMaster" parameter explicitly
    int sendWetHandle = audioSystem->getSubmixHandle("SendWetToMaster"); // FUN_004dafd0
    int* paramPtr = SubmixBusManager::findParameter(sendWetHandle, &sendWetHandle); // FUN_005e9d90 (unusual param reuse)
    if (paramPtr != 0) {
        // Copy value from audio system into local buffer
        audioSystem->getParameterValue(*(int*)(audioSystem + 0x580), *(int*)(paramPtr + 0x10), 0, &result); // FUN_00c9cbe0
        result = **(int**)(audioSystem + 0x42c); // pointer to some value
        audioSystem->setBusParameterValue(0, &result); // FUN_00c9cd40
        return 1;
    }
    return 0;
}