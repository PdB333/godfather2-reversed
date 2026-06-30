// FUNC_NAME: SomeManager::processExpiredEntries
// Function address: 0x006bba40
// Role: Iterates through an array of 0x18-byte entries, removing entries based on conditions (null/expired/marked) 
//       and managing flags on associated objects. Triggered by a global timer threshold.

void __fastcall SomeManager::processExpiredEntries(void)
{
    bool timerTriggered;
    int entryIndex;
    int *entryPtr;
    int *lastEntryPtr;
    int ownerOrHandle;
    int ownerMinus48;
    char someGlobalResult;
    
    // Check global timer threshold at _DAT_00d5e6ec (likely a timestamp or frame counter)
    timerTriggered = false;
    if ((this->entries != 0) && (_DAT_00d5e6ec <= this->timerFloat)) {
        timerTriggered = true;
        this->timerFloat = 0.0f;   // reset timer
    }
    
    entryIndex = this->entryCount - 1;
    if (entryIndex >= 0) {
        int arrayOffset = entryIndex * 0x18;   // each entry is 0x18 bytes
        do {
            // Read first field of the entry (may be a pointer or handle)
            entryPtr = (int *)(this->entryArray);
            ownerOrHandle = entryPtr[arrayOffset / 4];   // actually: *(int *)(*(int *)(this + 0xa0) + arrayOffset)
            // Simplified: ownerOrHandle = *(int *)((char*)this->entryArray + arrayOffset);
            
            if (ownerOrHandle == 0) {
                ownerMinus48 = 0;   // for null, set to indicate no owner
                goto removeEntry;
            }
            else {
                ownerMinus48 = ownerOrHandle - 0x48;   // check if owner is exactly 0x48 (sentinel?)
                if (ownerMinus48 == 0) goto removeEntry;
                
                if (timerTriggered) {
                    // Mark owner with flag 0x800000 at offset 0x14
                    *(uint *)(ownerOrHandle + 0x14) |= 0x800000;
                    goto removeEntry;
                }
                
                someGlobalResult = FUN_00791230();   // likely checks a system condition
                if (someGlobalResult == 0) goto removeEntry;
            }
            
            // Move to previous entry
            entryIndex--;
            arrayOffset -= 0x18;
        } while (entryIndex >= 0);
    }
    
    if (!timerTriggered) {
        return;
    }
    FUN_006badb0();   // called after timer-triggered processing
    return;
    
removeEntry:
    // If the current entry is not the last one, swap/move last entry to current position
    if (entryIndex != this->entryCount - 1) {
        // FUN_006baf90 likely copies last entry to current slot
        FUN_006baf90((int)((char*)this->entryArray + (this->entryCount * 0x18) - 0x18));  // base + (count-1)*0x18
    }
    
    // Decrement count
    this->entryCount--;
    
    // Get pointer to the (now) last entry (which may have been moved here)
    lastEntryPtr = (int *)((char*)this->entryArray + this->entryCount * 0x18);
    if (*lastEntryPtr != 0) {
        FUN_004daf90(lastEntryPtr);   // likely cleanup/free of the entry's data
    }
    
    // If there was a non-sentinel owner, clear a flag at offset 0x5c
    if (ownerMinus48 != 0) {
        // ownerMinus48 = ownerOrHandle - 0x48, so ownerMinus48 + 0x5c = ownerOrHandle + 0x14
        *(uint *)(ownerMinus48 + 0x5c) &= 0xfbffffff;   // clear bit 0x4000000? Actually mask clears bit 0x4000000 (bit 26)
    }
}