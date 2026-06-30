// FUNC_NAME: GodfatherGameManager::tryPlayEventSound
bool __thiscall GodfatherGameManager::tryPlayEventSound(int this, int eventId)
{
    int i;
    int eventIndex;
    int *pEventId;
    bool result;
    float volume;
    float unusedFloat;

    result = false;
    i = 0;
    pEventId = (int *)(this + 0x82b0); // Array of 10 event IDs at offset 0x82b0
    do {
        if ((-1 < *pEventId) && (*pEventId == eventId)) goto FOUND;
        i = i + 1;
        pEventId = pEventId + 0x5c; // Each entry is 0x5c bytes
    } while (i < 10);
    i = -1; // Not found
FOUND:
    if ((*(int *)(this + 0x580) != 0) && (i >= 0)) {
        eventIndex = i * 0x170 + 0x8210 + this; // pointer to event detail entry (0x170 bytes each)
        if (*(int *)(*(int *)(eventIndex + 0x9c) * 0x10 + 0x81c4 + this) != 0) {
            int soundMgr = FUN_005e9d10(); // Get sound manager
            FUN_00c9cbe0(*(int *)(this + 0x580), *(int *)(soundMgr + 0x10), 2, &volume);
            FUN_00ab4db0(&DAT_00e2aea0); // lock
            volume = *(float *)(eventIndex + 0x134); // event volume?
            if ((*(int *)(eventIndex + 0xf8) == 0) && (DAT_00e2b05c <= volume)) {
                FUN_00c9eac0(); // begin sound play?
                FUN_00c9cd40(2, &volume); // Play sound with volume
                FUN_00c9eae0(); // end sound play?
                result = true;
                if (unusedFloat != DAT_00e2b05c) {
                    result = false;
                }
            }
            FUN_00ab4e70(); // unlock
            return result;
        }
        return false;
    }
    return false;
}