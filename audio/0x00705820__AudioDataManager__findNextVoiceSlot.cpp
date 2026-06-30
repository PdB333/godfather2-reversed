// FUNC_NAME: AudioDataManager::findNextVoiceSlot
// Function address: 0x00705820
// Purpose: Iterates over audio voice slots, validates and cleans up invalid ones, returns a valid pointer to an active voice object.
// The class holds an array of 11 slots (each 0x14 bytes) starting at this+0x00.
// Slot fields: unknown[5] at offsets 0x00-0x13; a pointer to a voice object is stored at offset 0x18 from each slot base (i.e., in the next slot's region).
// this+0xF8: current index (cycling 0-10)
// this+0x114: bitmask of blocked slots (bits 0-10 set to skip)
// Callees:
//   FUN_00704150 - returns status (-1 = invalid, else valid handle)
//   FUN_004daf90 - frees/deallocates pointer
//   FUN_00704110 - returns pointer to voice object from handle
//   FUN_00701830 - probably triggers a sound or play event

int __fastcall AudioDataManager::findNextVoiceSlot(AudioDataManager* this)
{
    int currentIdx = *(int*)((char*)this + 0xF8);
    int blockedMask = *(int*)((char*)this + 0x114);
    int localCounter = 0;

    do {
        // Cycle to next slot, wrap 0-10
        currentIdx = currentIdx + 1;
        if (currentIdx < 0 || currentIdx > 10) {
            currentIdx = 0;
        }

        // Base of the slot data (0x14 bytes each)
        int slotBase = (int)((char*)this + currentIdx * 0x14);
        // Voice object pointer is stored at offset 0x18 from slot base (i.e., in the following slot's data)
        int* voicePtrAddr = (int*)(slotBase + 0x18);
        int voicePtr = *voicePtrAddr;

        if (voicePtr != 0) {
            int voiceHandle = voicePtr - 0x48; // Adjust to get internal handle
            if (voiceHandle != 0 && !(blockedMask & (1 << currentIdx))) {
                *(int*)((char*)this + 0xF8) = currentIdx;
                int status = FUN_00704150(voiceHandle);
                if (status == -1) {
                    // Voice is invalid, free the pointer and clear slot
                    if (voicePtr != 0 && voicePtr != 0x48 && *voicePtrAddr != 0) {
                        FUN_004daf90(voicePtrAddr);
                        *voicePtrAddr = 0;
                    }
                    *(int*)((char*)this + 0xF8) = 0;
                } else {
                    int voiceObj = FUN_00704110(voiceHandle);
                    if (voiceObj != 0) {
                        // Check if voice is active (byte at +0x1A8)
                        if (*(char*)(voiceObj + 0x1A8) == 1) {
                            FUN_00701830(0);
                        }
                        return voiceObj;
                    }
                }
            }
        }
        localCounter++;
    } while (localCounter < 0xB); // 11 slots

    return 0;
}