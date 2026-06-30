// FUNC_NAME: StreamSlotManager::setSlotTime
int __thiscall StreamSlotManager::setSlotTime(int this, int slotID, int timeValue) {
    int index;
    int *idPtr;
    double resultTime;
    double tempDouble;
    float someFloat; // from +0x134

    index = 0;
    idPtr = (int *)(this + 0x82b0); // pointer to first ID in mapping array (10 entries, each 0x5c bytes)
    // Search for slotID in the mapping array
    while (*idPtr < 0 || *idPtr != slotID) {
        index = index + 1;
        idPtr = (int *)((char *)idPtr + 0x5c); // stride of 0x5c bytes per mapping entry
        if (9 < index) {
            return 0; // not found
        }
    }
    // index valid (0-9)
    if (index >= 0) {
        SlotData *slotData = (SlotData *)(this + 0x8210 + index * 0x170);
        audio_enterLock(&DAT_00e2aea0); // likely enter critical section
        // Check if the referenced entry (via slotData->field_0x9c) is valid
        if (*(int *)(this + 0x81c4 + *(int *)(slotData + 0x9c) * 0x10) != 0) {
            int audioSys = audio_getAudioSystem(); // FUN_005e9d10
            audio_getStreamTime(*(int *)(this + 0x580), *(int *)(audioSys + 0x10), 4, &tempDouble); // FUN_00c9cbe0
            someFloat = *(float *)(slotData + 0x134); // local_10
            audio_doSomething(); // FUN_00c9eac0
            resultTime = DAT_00e2af58; // default fallback time
            if (timeValue >= 0) {
                if (DAT_00e2af60 <= (double)timeValue * DAT_00e446c8) {
                    resultTime = *(double *)(*(int *)(this + 0x580) + 8) + (double)timeValue * DAT_00e446c8;
                } else {
                    resultTime = 0.0;
                }
            }
            // Check if special flag or float condition
            if ((*(int *)(slotData + 0xa4) != 0) ||
                (*(float *)(slotData + 0x134) <= 0.0 && *(float *)(slotData + 0x134) != 0.0)) {
                *(double *)(slotData + 0x80) = resultTime;
            } else {
                *(double *)(slotData + 0x80) = resultTime;
                tempDouble = resultTime;
                audio_applyStreamTime(4, &tempDouble); // FUN_00c9cd40
            }
            audio_doOtherThing(); // FUN_00c9eae0
            audio_leaveLock(); // FUN_00ab4e70
            return 1;
        }
        audio_leaveLock(); // FUN_00ab4e70
    }
    return 0;
}